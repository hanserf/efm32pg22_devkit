/***************************************************************************/ /**
 * @file main.c
 * @brief This project demonstrates DMA driven pulse width modulation using the
 * TIMER module. The GPIO pin specified in the readme.txt is configured to
 * output a 1kHz signal. The DMA continuously updates the CCVB register to vary
 * the duty cycle.
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

#include "src/ws2812_timer_ll.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_ldma.h"
#include "em_timer.h"
#include "src/bsp.h"
#include "src/ldma_ll.h"

// Global variables used to set top value and duty cycle of the timer
#define NUM_LEDS 60
#define PWM_PRESCALE (timerPrescale1)
#define BITS_PR_WORD 24

static volatile struct {
    uint32_t buf[NUM_LEDS];
    uint32_t r_index;
    bool done;
    bool finished;
} WS2812_SR;

static volatile uint32_t pwm_buf[BITS_PR_WORD];
static void populate_ldma_buffer();
static void WS2812_LDMA_IRQHandler(void);

/**************************************************************************/ /**
 * @brief
 *    Interrupt handler for TIMER0 that changes the duty cycle
 *
 * @note
 *    This handler doesn't actually dynamically change the duty cycle. Instead,
 *    it acts as a template for doing so. Simply change the dutyCycle
 *    global variable here to dynamically change the duty cycle.
 *****************************************************************************/
static void WS2812_LDMA_IRQHandler(void) {
    if (WS2812_SR.done) {
        WS2812_SR.finished = true;
    } else {
        populate_ldma_buffer();
    }
}
static void populate_ldma_buffer() {
    if (WS2812_SR.r_index + 1 < NUM_LEDS) {
        uint32_t timerFreq = CMU_ClockFreqGet(cmuClock_TIMER0) / (PWM_PRESCALE + 1);
        uint32_t high_bit = (timerFreq / WS2812_HIGH_BIT1_FREQ);
        uint32_t low_bit = (timerFreq / WS2812_HIGH_BIT0_FREQ);
        uint32_t word = WS2812_SR.buf[WS2812_SR.r_index];

        for (int i = BITS_PR_WORD - 1; i >= 0; i--) {
            (word & (1 << i)) ? (pwm_buf[i] = high_bit) : (pwm_buf[i] = low_bit);
        }
        WS2812_SR.r_index++;
    } else {
        WS2812_SR.done = true;
    }
}

/**************************************************************************/ /**
 * @brief
 *    TIMER initialization
 *****************************************************************************/
void ws2812_ll_init_timer(void) {
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_TIMER0, true);

    GPIO_PinModeSet(WS2812_PWM_OUT_PORT, WS2812_PWM_OUT_PIN, gpioModePushPull, 0);
    ldma_ll_register_irq(LDMA_IRQ_WS2812, WS2812_LDMA_IRQHandler);
    // Initialize the timer
    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
    // Configure TIMER0 Compare/Capture for output compare
    TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;

    // Use PWM mode, which sets output on overflow and clears on compare events
    timerInit.prescale = PWM_PRESCALE;
    timerInit.enable = false;
    timerCCInit.mode = timerCCModePWM;

    // Configure but do not start the timer
    TIMER_Init(TIMER0, &timerInit);

    // Route Timer0 CC0 output to PA6
    GPIO->TIMERROUTE[0].ROUTEEN = GPIO_TIMER_ROUTEEN_CC0PEN;
    // Route Timer0 CC0 output to PA6
    GPIO->TIMERROUTE[0].ROUTEEN = GPIO_TIMER_ROUTEEN_CC0PEN;
    GPIO->TIMERROUTE[0].CC0ROUTE = (WS2812_PWM_OUT_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (WS2812_PWM_OUT_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);

    // Configure CC Channel 0
    TIMER_InitCC(TIMER0, 0, &timerCCInit);

    // set PWM period
    uint32_t timerFreq = CMU_ClockFreqGet(cmuClock_TIMER0) / (PWM_PRESCALE + 1);
    uint32_t topValue = (timerFreq / WS2812_PWM_FREQ);
    // Set top value to overflow at the desired PWM_FREQ frequency
    TIMER_TopSet(TIMER0, topValue);
}

void ws2812_dma_enable(bool enable) {
    WS2812_SR.done = false;
    WS2812_SR.r_index = 0;
    if (enable) {
        // LDMA initialization
        LDMA_Init_t init = LDMA_INIT_DEFAULT;
        LDMA_Init(&init);
        populate_ldma_buffer();
        // Transfer configuration and trigger selection
        LDMA_TransferCfg_t transferConfig =
            LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_TIMER0_CC0);

        // Channel descriptor configuration
        static LDMA_Descriptor_t descriptor =
            LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(&pwm_buf,           // Memory source address
                                             &TIMER0->CC[0].OCB, // Peripheral destination address
                                             BITS_PR_WORD,       // Number of bytes per transfer
                                             0);                 // Link to same descriptor
        descriptor.xfer.size = ldmaCtrlSizeHalf;                 // Unit transfer size
        descriptor.xfer.doneIfs = 1;                             // Trigger interrupt when done

        LDMA_StartTransfer(LDMA_WS2812_CH, &transferConfig, &descriptor);
        // Start the timer
        TIMER_Enable(TIMER0, true);
        // Enable TIMER0 compare event interrupts to update the duty cycle
        TIMER_IntEnable(TIMER0, TIMER_IEN_CC0);
    } else {
        LDMA_StopTransfer(LDMA_WS2812_CH);
        // Sop the timer
        TIMER_Enable(TIMER0, false);
        // Disable TIMER0 compare event interrupts
        TIMER_IntDisable(TIMER0, TIMER_IEN_CC0);
    }
}

void ws2812_set_led(uint32_t led, uint32_t value) {
    if (led < NUM_LEDS) {
        WS2812_SR.buf[led] = value;
    }
}