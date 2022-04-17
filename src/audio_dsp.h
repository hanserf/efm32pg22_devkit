#include <arm_math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#define BP_CHANNELS 5
/* Block size for the underlying processing */
#define BLOCKSIZE 32

int32_t audio_dsp_band_pass_filter_bank(q31_t *bufferSrc, size_t size, bool l_or_r);
float32_t audio_dsp_r_get_rms_value(size_t pos);
float32_t audio_dsp_l_get_rms_value(size_t pos);
