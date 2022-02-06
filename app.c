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
#include "em_emu.h"
#include "src/pdm_ll.h"
#include "src/usart0_ll.h"
#include <em_usart.h>
#include <stdint.h>
/***************************************************************************/ /**
 * Initialize application.
 ******************************************************************************/
void app_init(void) {
    CHIP_Init();
    pdm_ll_init();
    initUSART0();
    eprintf("Starting Main loop\r\n");
    USART_IntEnable(USART0, USART_IEN_RXDATAV);
}

/***************************************************************************/ /**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void) {
    uint32_t r_rms = 0;
    uint32_t l_rms = 0;
    if (pdm_ll_handler(&r_rms, &l_rms)) {
        if (l_rms) {
            eprintf("L_RMS\r\n");
        }
        if (r_rms) {
            eprintf("R_RMS\r\n");
        }
    }
    if (uart0_ll_handler()) {
            //parse rx uart;
        eprintf("rx\r\n");
    }
    EMU_EnterEM1();
}
