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
#include "src/bsp.h"
#include "src/pdm_ll.h"
#include "src/usart0_ll.h"
#include "src/ws2812_timer_ll.h"
#include <em_usart.h>
#include <stdint.h>
#define DEBUG_APP (1)
uint32_t num_samples = PDM_BUFFERSIZE;
/***************************************************************************/ /**
 * Initialize application.
 ******************************************************************************/
void app_init(void) {
    CHIP_Init();
#if (DEBUG_APP == 1)
    CMU_ClockEnable(cmuClock_GPIO, true);
    GPIO_PinModeSet(DEBUG1_PORT, DEBUG1_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(DEBUG1_PORT, DEBUG1_PIN, gpioModePushPull, 0);
#endif
    initUSART0();
    refresh_timer_ll_init();
    ws2812_ll_init_timer();
    eprintf("Starting Main loop\r\n");
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
    if (pdm_ll_handler(num_samples)) {
        pdm_ll_calc_rms(&r_rms, &l_rms);
        if (l_rms) {
            eprintf("L_RMS %.2f\r\n", l_rms);
        }
        if (r_rms) {
            eprintf("R_RMS %.2f\r\n", r_rms);
        }
        EMU_EnterEM1();
    }
    uart0_ll_handler();
}
