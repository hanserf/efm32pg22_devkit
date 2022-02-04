#pragma once
#include <stdbool.h>

bool uart0_ll_handler(void);
void eprintf(char *str, ...);
void initUSART0(void);
