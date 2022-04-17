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
#include "src/audio_dsp.h"
#include "src/bsp.h"
#include "src/ldma_ll.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
// Left/right buffer size
// Buffers for left/right PCM data
#define PCM_BIT_PRECISION (15)
static q31_t l_raw[BLOCKSIZE];
static q31_t r_raw[BLOCKSIZE];
static q31_t r_temp[BLOCKSIZE];
static q31_t l_temp[BLOCKSIZE];
static q31_t left[PDM_BUFFERSIZE];
static q31_t right[PDM_BUFFERSIZE];

static volatile uint32_t pdm_cntr = 0;
static volatile uint32_t pdm_block_cntr = 0;

bool pdm_done = false;
static int32_t sign_extend_bits(uint16_t x, uint16_t sign_bit_pos);

/***************************************************************************/ /**
 * @brief
 *   Sets up PDM microphones
 ******************************************************************************/
void initPdm(void) {
    pdm_done = false;
    pdm_cntr = 0;
    pdm_block_cntr = 0;

    PDM_Init_TypeDef pdmInit = PDM_INIT_DEFAULT;

    // Set up clocks
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_PDM, true);
    CMU_ClockSelectSet(cmuClock_PDMREF, cmuSelect_HFRCODPLL); // 19 MHz
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
    // Config GPIO and pin routing
    GPIO_PinModeSet(PDM_ENABLE_PORT, PDM_ENABLE_PIN, gpioModePushPull, 1); // MIC_EN
    GPIO_PinModeSet(PDM_CLK_PORT, PDM_CLK_PIN, gpioModePushPull, 0);       // PDM_CLK
    GPIO_PinModeSet(PDM_DATA_PORT, PDM_DATA_PIN, gpioModeInput, 0);        // PDM_DATA
    /* Set slew rate of port outputting PDM CLK from DPLL */
    GPIO_SlewrateSet(PDM_CLK_PORT, 7, 7);
    GPIO->PDMROUTE.ROUTEEN = GPIO_PDM_ROUTEEN_CLKPEN;
    GPIO->PDMROUTE.CLKROUTE = (PDM_CLK_PORT << _GPIO_PDM_CLKROUTE_PORT_SHIFT) | (PDM_CLK_PIN << _GPIO_PDM_CLKROUTE_PIN_SHIFT);
    GPIO->PDMROUTE.DAT0ROUTE = (PDM_DATA_PORT << _GPIO_PDM_DAT0ROUTE_PORT_SHIFT) | (PDM_DATA_PIN << _GPIO_PDM_DAT0ROUTE_PIN_SHIFT);
    GPIO->PDMROUTE.DAT1ROUTE = (PDM_DATA_PORT << _GPIO_PDM_DAT1ROUTE_PORT_SHIFT) | (PDM_DATA_PIN << _GPIO_PDM_DAT1ROUTE_PIN_SHIFT);
    // Configure PDM
    // Initialize PDM registers with reset values
    PDM_Reset(PDM);

    // Configure PDM
    pdmInit.start = true;

    // Initialize PDM peripheral
    PDM_Init(PDM, &pdmInit);
}

/***************************************************************************/ /**
 * @brief
 *   PDM Interrupt Handler
 ******************************************************************************/
void PDM_IRQHandler(void) {
    //https://stackoverflow.com/questions/24515505/assignment-discards-volatile-qualifier-from-pointer-target-type
    uint32_t interruptFlags = PDM->IF;
    uint32_t tmp = 0;
    // Read data from FIFO
    if (!pdm_done) {
        if (interruptFlags & PDM_IF_DVL) {
            PDM->IF_CLR = PDM_IF_DVL;
            /*The PCM Stereo word is read from PDM->RXData 32B Word. One stereo channel is 16-bit wide.
                L is LSW and R is MSW. W is 16-bit nibble of 32B RXData*/
            while ((PDM->STATUS & PDM_STATUS_EMPTY)) {
            }
            tmp = PDM->RXDATA;
            l_raw[(pdm_cntr % BLOCKSIZE)] = sign_extend_bits((tmp & 0x0000FFFF), PCM_BIT_PRECISION);
            r_raw[(pdm_cntr % BLOCKSIZE)] = sign_extend_bits(((tmp >> 16) & 0x0000FFFF), PCM_BIT_PRECISION);
            pdm_cntr++;
            if (pdm_cntr > 0 && ((pdm_cntr % BLOCKSIZE) == 0)) {
                arm_q15_to_q31((int16_t *)l_raw, l_temp, BLOCKSIZE);
                arm_q15_to_q31((int16_t *)r_raw, r_temp, BLOCKSIZE);
                for (int i = 0; i < BLOCKSIZE; i++) {
                    left[pdm_block_cntr * BLOCKSIZE + i] = l_temp[i];
                    right[pdm_block_cntr * BLOCKSIZE + i] = r_temp[i];
                }
                pdm_block_cntr++;
            }
            if (pdm_cntr == PDM_BUFFERSIZE) {
                GPIO_PinOutSet(DEBUG2_PORT, DEBUG2_PIN);
                PDM->IEN_CLR = PDM_IEN_DVL;
                pdm_done = true;
                pdm_block_cntr = 0;
                NVIC_ClearPendingIRQ(PDM_IRQn);
                NVIC_DisableIRQ(PDM_IRQn);
                GPIO_PinOutClear(DEBUG2_PORT, DEBUG2_PIN);
            }
        }
    }
}

// uint32_t sign_bit_pos;       // number of bits representing the number in x
// int x;                       // sign extend this b-bit number to r
// Return :int r;                       // resulting sign-extended number
static int32_t sign_extend_bits(uint16_t x, uint16_t sign_bit_pos) {
    int const m = 1U << (sign_bit_pos - 1); // mask can be pre-computed if b is fixed
    x = x & ((1U << sign_bit_pos) - 1);     // (Skip this if bits in x above position b are already zero.)
    return (int16_t)(x ^ m) - m;
}
void pdm_ll_enable(bool enable) {
    if (enable) {
        GPIO_PinOutSet(DEBUG1_PORT, DEBUG1_PIN);
        pdm_cntr = 0;
        pdm_block_cntr = 0;
        pdm_done = false;
        NVIC_ClearPendingIRQ(PDM_IRQn);
        NVIC_EnableIRQ(PDM_IRQn);
        PDM->IEN = PDM_IEN_DVL;
    } else {
        //CMU_OscillatorEnable(cmuOsc_LFXO, false, true);
        //PDM->IEN_CLR = PDM_IEN_DVL;
        //NVIC_DisableIRQ(PDM_IRQn);
        GPIO_PinOutClear(DEBUG1_PORT, DEBUG1_PIN);
    }
}

/***************************************************************************/ /**
 * @brief
 *   Main function
 ******************************************************************************/
bool pdm_ll_handler(void) {
    bool rc = false;
    int dsp_rc = -1;
    if (pdm_done) {
        pdm_done = false;
        pdm_ll_enable(false);
        dsp_rc = audio_dsp_band_pass_filter_bank((q31_t *)left, PDM_BUFFERSIZE, false);
        if (dsp_rc > 0) {
            dsp_rc = audio_dsp_band_pass_filter_bank((q31_t *)right, PDM_BUFFERSIZE, true);
            if (dsp_rc > 0) {
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
