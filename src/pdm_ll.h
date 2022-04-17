#include <stdbool.h>
#include <stdint.h>
#define PDM_BUFFERSIZE 256
void initPdm(void);
void pdm_ll_enable(bool enable);
bool pdm_ll_handler(void);
void pdm_ll_calc_rms(float *rms_r, float *rms_l);
