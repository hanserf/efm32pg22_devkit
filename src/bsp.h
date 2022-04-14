#pragma once
#include "src/bsp.h"
#include <em_gpio.h>
/* I2C sensors, HALL effect and Ambient light */
#define SENSOR_ENABLE_PORT gpioPortC
#define SENSOR_ENABLE_PIN 6
#define SENSOR_I2C_SCL_PORT gpioPortD
#define SENSOR_I2C_SCL_PIN 3
#define SENSOR_I2C_SDA_PORT gpioPortD
#define SENSOR_I2C_SDA_PIN 2

#define PDM_ENABLE_PORT gpioPortC
#define PDM_ENABLE_PIN 7
#define PDM_CLK_PORT gpioPortB
#define PDM_CLK_PIN 0
#define PDM_DATA_PORT gpioPortB
#define PDM_DATA_PIN 1

#define BSP_BUTTON_PORT gpioPortB
#define BSP_BUTTON_PIN 3

#define BSP_LED_PORT gpioPortA
#define BSP_LED_PIN 4

#define USART_RX_PORT gpioPortA
#define USART_RX_PIN 6
#define USART_TX_PORT gpioPortA
#define USART_TX_PIN 5

#define WS2812_PWM_OUT_PORT gpioPortA
#define WS2812_PWM_OUT_PIN 3

#define DEBUG1_PORT (gpioPortA)
#define DEBUG1_PIN (8)
#define DEBUG2_PORT (gpioPortA)
#define DEBUG2_PIN (7)

#define WS2812_PWM_FREQ (800000)        // 1.25us period
#define WS2812_HIGH_BIT0_FREQ (1428572) // 0.7 us period
#define WS2812_HIGH_BIT1_FREQ (2857143) // 0.35 us period

// DMA channel Setup
#define LDMA_PDM_CHANNEL LDMA_IRQ_PDM
#define LDMA_PDM_CH_MASK (1 << LDMA_PDM_CHANNEL)
#define LDMA_WS2812_CH LDMA_IRQ_WS2812
#define LDMA_WS2812_CH_MASK (1 << LDMA_WS2812_CH)
