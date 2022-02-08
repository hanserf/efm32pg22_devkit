#pragma once
#include <stdbool.h>
#include <stdint.h>
void ws2812_ll_init_timer(void);
void ws2812_dma_enable(bool enable);
void ws2812_set_led(uint32_t led, uint32_t value);