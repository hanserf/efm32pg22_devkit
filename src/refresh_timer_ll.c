/***************************************************************************/ /**
 * @file main.c
 * @brief This project demonstrates pulse width modulation using the TIMER
 * module. The GPIO pin specified in the readme.txt is configured for output and
 * outputs a 1kHz, 30% duty cycle signal. The duty cycle can be adjusted by
 * writing to the CCVB or changing the global dutyCycle variable.
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

#include "em_chip.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "src/bsp.h"
#include <stdbool.h>

// Global variables used to set top value and duty cycle of the timer
#define PWM_FREQ 1
#define PWM_TIMER TIMER1
#define PWM_TIMER_CMU cmuClock_TIMER1
static uint32_t topValue = 0;
static volatile float dutyCycle = 0.5;
bool do_refresh = false;
/**************************************************************************/ /**
 * @brief
 *    Interrupt handler for TIMER0 that changes the duty cycle
 *
 * @note
 *    This handler doesn't actually dynamically change the duty cycle. Instead,
 *    it acts as a template for doing so. Simply change the dutyCycle
 *    global variable here to dynamically change the duty cycle.
 *****************************************************************************/
void TIMER1_IRQHandler(void) {
    // Acknowledge the interrupt
    uint32_t flags = TIMER_IntGet(PWM_TIMER);
    TIMER_IntClear(PWM_TIMER, flags);
    GPIO_PinOutToggle(BSP_LED_PORT, BSP_LED_PIN);
    do_refresh = true;
}

/**************************************************************************/ /**
 * @brief
 *    TIMER initialization
 *****************************************************************************/
void refresh_timer_ll_init(void) {
    // Enable clock to GPIO and TIMER0
    CMU_ClockEnable(PWM_TIMER_CMU, true);
    CMU_ClockEnable(cmuClock_GPIO, true);
    GPIO_PinModeSet(BSP_LED_PORT, BSP_LED_PIN, gpioModePushPull, 0);

    uint32_t timerFreq = 0;
    // Initialize the timer
    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
    // Configure TIMER0 Compare/Capture for output compare
    TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;

    // Use PWM mode, which sets output on overflow and clears on compare events
    timerInit.prescale = timerPrescale1024;
    timerInit.enable = false;
    timerCCInit.mode = timerCCModePWM;
    timerCCInit.cofoa = timerOutputActionToggle;
    timerCCInit.cmoa = timerOutputActionToggle;

    // Configure but do not start the timer
    TIMER_Init(PWM_TIMER, &timerInit);

    // Route Timer0 CC0 output to PA6
    GPIO->TIMERROUTE[0].ROUTEEN = GPIO_TIMER_ROUTEEN_CC0PEN;
    GPIO->TIMERROUTE[0].CC0ROUTE = (BSP_LED_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (BSP_LED_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);

    // Configure CC Channel 0
    TIMER_InitCC(PWM_TIMER, 0, &timerCCInit);
    dutyCycle = 0.5;
    // set PWM period
    timerFreq = CMU_ClockFreqGet(PWM_TIMER_CMU) / (timerInit.prescale + 1);
    topValue = (timerFreq / PWM_FREQ);
    // Set top value to overflow at the desired PWM_FREQ frequency
    TIMER_TopSet(PWM_TIMER, topValue);

    // Set compare value for initial duty cycle
    TIMER_CompareSet(PWM_TIMER, 0, (uint32_t)(topValue * dutyCycle));

    // Start the timer
    TIMER_Enable(PWM_TIMER, true);

    // Enable TIMER0 compare event interrupts to update the duty cycle
    TIMER_IntEnable(PWM_TIMER, TIMER_IEN_CC0);
    NVIC_EnableIRQ(TIMER1_IRQn);
}

bool refresh_timer_ll_handler(void) {
    bool rc = do_refresh;
    if (rc) {
        do_refresh = false;
    }
    return rc;
}