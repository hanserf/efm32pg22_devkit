/***************************************************************************/ /**
 * @file main_pdm_stereo_ldma.c
 * @brief This project demonstrates how to get stereo audio using PDM module and
 * LDMA.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *******************************************************************************
 * # Evaluation Quality
 * This code has been minimally tested to ensure that it builds and is suitable 
 * as a demonstration for evaluation purposes only. This code will be maintained
 * at the sole discretion of Silicon Labs.
 ******************************************************************************/

#include "src/pdm_ll.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_ldma.h"
#include "em_pdm.h"
#include "src/bsp.h"
#include "src/ldma_ll.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

// Left/right buffer size
// Buffers for left/right PCM data
float left[PDM_BUFFERSIZE];
float right[PDM_BUFFERSIZE];
uint32_t pdm_cntr = 0;
bool pdm_enable = false;
static void initPdm(void);

/***************************************************************************/ /**
 * @brief
 *   Sets up PDM microphones
 ******************************************************************************/
static void initPdm(void) {
    PDM_Init_TypeDef pdmInit = PDM_INIT_DEFAULT;
    CMU_DPLLInit_TypeDef pllInit = CMU_DPLL_LFXO_TO_40MHZ;
    CMU_OscillatorEnable(cmuOsc_LFXO, true, true);
    // Lock PLL to 1,411,209 Hz to achive 44,100 kHz PCM sampling rate
    // when using 32x PDM oversampling
    pllInit.frequency = 1411209;
    pllInit.m = 14;
    pllInit.n = 645;
    while (!CMU_DPLLLock(&pllInit)) {
        /* Wait for lock */
    };
    // Set up clocks
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_PDM, true);

    // Config GPIO and pin routing
    GPIO_PinModeSet(PDM_ENABLE_PORT, PDM_ENABLE_PIN, gpioModePushPull, 1); // MIC_EN
    GPIO_PinModeSet(PDM_CLK_PORT, PDM_CLK_PIN, gpioModePushPull, 0);       // PDM_CLK
    GPIO_PinModeSet(PDM_DATA_PORT, PDM_DATA_PIN, gpioModeInput, 0);        // PDM_DATA
    /* Set slew rate of port outputting PDM CLK from DPLL */
    GPIO_SlewrateSet(gpioPortB, 7, 7);

    GPIO->PDMROUTE.ROUTEEN = GPIO_PDM_ROUTEEN_CLKPEN;
    GPIO->PDMROUTE.CLKROUTE = (PDM_CLK_PORT << _GPIO_PDM_CLKROUTE_PORT_SHIFT) | (PDM_CLK_PIN << _GPIO_PDM_CLKROUTE_PIN_SHIFT);
    GPIO->PDMROUTE.DAT0ROUTE = (PDM_DATA_PORT << _GPIO_PDM_DAT0ROUTE_PORT_SHIFT) | (PDM_DATA_PIN << _GPIO_PDM_DAT0ROUTE_PIN_SHIFT);
    GPIO->PDMROUTE.DAT1ROUTE = (PDM_DATA_PORT << _GPIO_PDM_DAT1ROUTE_PORT_SHIFT) | (PDM_DATA_PIN << _GPIO_PDM_DAT1ROUTE_PIN_SHIFT);
    // Initialize PDM peripheral
    PDM_Init(PDM, &pdmInit);
}

void pdm_ll_enable(bool enable) {
    pdm_enable = enable;
    pdm_cntr = 0;
    if (enable) {
        GPIO_PinOutSet(DEBUG1_PORT, DEBUG1_PIN);
        initPdm();
    } else {
        CMU_OscillatorEnable(cmuOsc_LFXO, false, true);
        PDM_Reset(PDM);
        GPIO->PDMROUTE.ROUTEEN = 0;
        GPIO_PinOutClear(DEBUG1_PORT, DEBUG1_PIN);
    }
}

/***************************************************************************/ /**
 * @brief
 *   Main function
 ******************************************************************************/
bool pdm_ll_handler(uint32_t num_samples) {
    bool rc = false;
    uint32_t tmp;
    if (pdm_enable) {
        GPIO_PinOutSet(DEBUG2_PORT, DEBUG2_PIN);
        /* Blocking Read*/
        if (PDM_BUFFERSIZE >= num_samples) {
            tmp = PDM_Rx(PDM);
            left[pdm_cntr] = (float)((tmp & 0x0000FFFF) - (32767.0)) / 32768.0;
            right[pdm_cntr] = (float)(((tmp >> 16) & 0x0000FFFF) - (32767.0)) / 32768.0;
            pdm_cntr++;
            if (pdm_cntr >= num_samples) {
                pdm_ll_enable(false);
                GPIO_PinOutClear(DEBUG2_PORT, DEBUG2_PIN);
                rc = true;
            }
        }
    }
    return rc;
}

void pdm_ll_calc_rms(float *rms_r, float *rms_l) {

    double l_rms = 0;
    double r_rms = 0;
    int i = 0;
    for (i = 0; i < PDM_BUFFERSIZE; i++) {
        l_rms += pow((double)left[i], 2);
        r_rms += pow((double)right[i], 2);
    }
    /*calculate the mean*/
    l_rms = l_rms / PDM_BUFFERSIZE;
    r_rms = r_rms / PDM_BUFFERSIZE;
    *rms_l = (float)sqrt(l_rms);
    *rms_r = (float)sqrt(r_rms);
}