#include <stdbool.h>
#include <stdint.h>

void pdm_ll_enable(bool enable);
bool pdm_ll_handler(uint32_t *rms_r, uint32_t *rms_l);