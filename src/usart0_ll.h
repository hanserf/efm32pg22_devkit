#pragma once
#include <stdbool.h>

void uart0_ll_handler(void);
void eprintf(char *str, ...);
void initUSART0(void);
