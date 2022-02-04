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