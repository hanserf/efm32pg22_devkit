/***************************************************************************/ /**
 * @file main_s2.c
 *
 * @brief This project demonstrates asynchronous mode use of the USART
 * with interrupts.
 *
 * After initialization, the MCU goes into EM1 where the receive interrupt
 * handler buffers incoming data until the reception of 80 characters or a
 * CR (carriage return, ASCII 0x0D).
 *
 * Once the CR or 80 characters is hit, the receive data valid interrupt is
 * disabled, and the transmit buffer level interrupt, which, by default, is set
 * after power-on, is is enabled.  Each entry into the transmit interrupt
 * handler causes a character to be sent until all the characters originally
 * received have been echoed.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "src/usart0_ll.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "src/bsp.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Size of the buffer for received data
#define BUFLEN 80
#define TX_BUFSIZE 256
// Receive data buffer
uint8_t buffer[BUFLEN];

// Current position ins buffer
uint32_t inpos = 0;
// True while receiving data (waiting for CR or BUFLEN characters)
bool receive = true;

/**************************************************************************/ /**
 * @brief
 *    USART0 initialization
 *****************************************************************************/
void initUSART0(void) {
    // Enable clock to GPIO and USART0
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_USART0, true);
    // Configure the USART TX pin to the board controller as an output
    GPIO_PinModeSet(USART_TX_PORT, USART_TX_PIN, gpioModePushPull, 0);
    // Configure the USART RX pin to the board controller as an input
    GPIO_PinModeSet(USART_RX_PORT, USART_RX_PIN, gpioModeInput, 0);
    // Zero out buffer
    for (int i = 0; i < BUFLEN; i++) {
        buffer[i] = 0;
    }

    // Default asynchronous initializer (115.2 Kbps, 8N1, no flow control)
    USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;

    // Route USART0 TX and RX to the board controller TX and RX pins
    GPIO->USARTROUTE[0].TXROUTE = (USART_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (USART_TX_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
    GPIO->USARTROUTE[0].RXROUTE = (USART_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT) | (USART_RX_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);

    // Enable RX and TX signals now that they have been routed
    GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_TXPEN;

    // Configure and enable USART0
    USART_InitAsync(USART0, &init);

    // Enable NVIC USART sources
    NVIC_ClearPendingIRQ(USART0_RX_IRQn);
    NVIC_EnableIRQ(USART0_RX_IRQn);
}

/****************************************************************************
 * @brief
 *    The USART0 receive interrupt saves incoming characters.
 *****************************************************************************/
void USART0_RX_IRQHandler(void) {
    if (receive) {
        // Get the character just received
        buffer[inpos] = USART0->RXDATA;

        // Exit loop on new line or buffer full
        if ((buffer[inpos] == '\n') && (inpos < BUFLEN)) {
            receive = false; // Stop receiving on CR
        } else {
            inpos = (inpos + 1) % BUFLEN;
        }
    }
}

/****************************************************************************
 * @brief
 *    Handler function
 *****************************************************************************/
void uart0_ll_handler(void) {
    if (!receive) {
        /* Parse input command..*/
        // #TODO SOMETHING USEFUL
        eprintf("rx\r\n");
        /* Enable receive again */
        inpos = 0;
        receive = true;
    }
}

static void my_putchar(unsigned char sdbyte) {
    USART_Tx(USART0, sdbyte);
}

void eprintf(char *str, ...) {
    char buf[TX_BUFSIZE];
    uint16_t i = 0;
    int rc = 0;
    va_list ptr;
    va_start(ptr, str);
    rc = vsnprintf(buf, TX_BUFSIZE, str, ptr);
    va_end(ptr);
    if (rc > 0) {
        while (buf[i]) {
            my_putchar(buf[i]);
            i++;
        }
    }
}
