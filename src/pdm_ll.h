#include <stdbool.h>
#include <stdint.h>
#define PDM_BUFFERSIZE 1024

void pdm_ll_enable(bool enable);
bool pdm_ll_handler(uint32_t num_samples);
void pdm_ll_calc_rms(float *rms_r, float *rms_l);
