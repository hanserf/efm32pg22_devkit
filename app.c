/***************************************************************************/ /**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "refresh_timer_ll.h"
#include "src/audio_dsp.h"
#include "src/bsp.h"
#include "src/pdm_ll.h"
#include "src/usart0_ll.h"
#include "src/ws2812_timer_ll.h"
#include <em_usart.h>
#include <stdint.h>
#define DEBUG_APP (1)
static volatile uint32_t num_samples = PDM_BUFFERSIZE;
uint32_t run_cntr = 0;
/***************************************************************************/ /**
 * Initialize application.
 ******************************************************************************/
void app_init(void) {
    CHIP_Init();
#if (DEBUG_APP == 1)
    run_cntr = 0;
    CMU_ClockEnable(cmuClock_GPIO, true);
    GPIO_PinModeSet(DEBUG1_PORT, DEBUG1_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(DEBUG1_PORT, DEBUG1_PIN, gpioModePushPull, 0);
#endif
    initUSART0();
    initPdm();
    refresh_timer_ll_init();
    ws2812_ll_init_timer();
    eprintf("Starting Main loop\r\n");
    eprintf("|RUN\t||CH\t||L_RMS\t||R_RMS\t|\n");
}

/***************************************************************************/ /**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void) {
    float r_rms = 0.0;
    float l_rms = 0.0;
    if (refresh_timer_ll_handler()) {
        pdm_ll_enable(true);
    }
    if (pdm_ll_handler()) {
        for (int i = 0; i < BP_CHANNELS; i++) {
            r_rms = audio_dsp_r_get_rms_value(i);
            l_rms = audio_dsp_l_get_rms_value(i);
            eprintf("|%lu\t|| %d\t|| %d\t|| %d\t|\n", run_cntr, i, (uint32_t)(l_rms * 100), (uint32_t)(r_rms * 100));
        }
        run_cntr++;
    }
    uart0_ll_handler();
}
