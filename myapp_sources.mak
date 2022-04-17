####################################################################
# Makefile Version 7                                               #
####################################################################

MY_SRC_PATH ?= src

# This uses the explicit build rules below
PROJECT_SOURCE_FILES =

C_SOURCE_FILES   += $(filter %.c, $(PROJECT_SOURCE_FILES))
CXX_SOURCE_FILES += $(filter %.cpp, $(PROJECT_SOURCE_FILES))
CXX_SOURCE_FILES += $(filter %.cc, $(PROJECT_SOURCE_FILES))
ASM_SOURCE_FILES += $(filter %.s, $(PROJECT_SOURCE_FILES))
ASM_SOURCE_FILES += $(filter %.S, $(PROJECT_SOURCE_FILES))
LIB_FILES        += $(filter %.a, $(PROJECT_SOURCE_FILES))

C_DEFS += \
 -DDEBUG_EFM=1 \
 -DEFM32PG22C200F512IM40=1 \
 -DARM_MATH_CM33=1 \
 -D__STATIC_INLINE='static inline'

ASM_DEFS += \
 -DDEBUG_EFM=1 \
 -DEFM32PG22C200F512IM40=1 \
 -DARM_MATH_CM33 \
 -D__STATIC_INLINE='static inline'

INCLUDES += \
 -I$(MY_SRC_PATH) \
 -I$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Examples/ARM/arm_graphic_equalizer_example

GROUP_START =-Wl,--start-group
GROUP_END =-Wl,--end-group


####################################################################
# App SRC Build Rules                                                  #
####################################################################

$(OUTPUT_DIR)/$(MY_SRC_PATH)/pdm_ll.o: $(MY_SRC_PATH)/pdm_ll.c
	@echo 'Building pdm_ll.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(MY_SRC_PATH)/pdm_ll.c
CDEPS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/pdm_ll.d
OBJS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/pdm_ll.o

$(OUTPUT_DIR)/$(MY_SRC_PATH)/usart0_ll.o: $(MY_SRC_PATH)/usart0_ll.c
	@echo 'Building usart0_ll.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(MY_SRC_PATH)/usart0_ll.c
CDEPS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/usart0_ll.d
OBJS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/usart0_ll.o

$(OUTPUT_DIR)/$(MY_SRC_PATH)/ws2812_timer_ll.o: $(MY_SRC_PATH)/ws2812_timer_ll.c
	@echo 'Building ws2812_timer_ll.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(MY_SRC_PATH)/ws2812_timer_ll.c
CDEPS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/ws2812_timer_ll.d
OBJS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/ws2812_timer_ll.o

$(OUTPUT_DIR)/$(MY_SRC_PATH)/ldma_ll.o: $(MY_SRC_PATH)/ldma_ll.c
	@echo 'Building ldma_ll.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(MY_SRC_PATH)/ldma_ll.c
CDEPS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/ldma_ll.d
OBJS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/ldma_ll.o


$(OUTPUT_DIR)/$(MY_SRC_PATH)/refresh_timer_ll.o: $(MY_SRC_PATH)/refresh_timer_ll.c
	@echo 'Building refresh_timer_ll.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(MY_SRC_PATH)/refresh_timer_ll.c
CDEPS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/refresh_timer_ll.d
OBJS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/refresh_timer_ll.o


$(OUTPUT_DIR)/$(MY_SRC_PATH)/audio_dsp.o: $(MY_SRC_PATH)/audio_dsp.c
	@echo 'Building audio_dsp.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(MY_SRC_PATH)/audio_dsp.c
CDEPS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/audio_dsp.d
OBJS += $(OUTPUT_DIR)/$(MY_SRC_PATH)/audio_dsp.o

$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Examples/ARM/arm_graphic_equalizer_example/math_helper.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Examples/ARM/arm_graphic_equalizer_example/math_helper.c
	@echo 'Building DSP math_helper.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Examples/ARM/arm_graphic_equalizer_example/math_helper.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Examples/ARM/arm_graphic_equalizer_example/math_helper.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Examples/ARM/arm_graphic_equalizer_example/math_helper.o

$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_rms_q31.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_rms_q31.c
	@echo 'Building DSP arm_rms_q31.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_rms_q31.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_rms_q31.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_rms_q31.o

$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_q31.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_rms_q31.c
	@echo 'Building DSP arm_biquad_cascade_df1_32x64_q31.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_q31.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_q31.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_q31.o

$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_init_q31.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/StatisticsFunctions/arm_biquad_cascade_df1_init_q31.c
	@echo 'Building DSP arm_biquad_cascade_df1_init_q31.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_init_q31.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_init_q31.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_init_q31.o

$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_init_q31.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_init_q31.c
	@echo 'Building DSP arm_biquad_cascade_df1_32x64_init_q31.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_init_q31.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_init_q31.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_init_q31.o


$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_float.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_float.c
	@echo 'Building DSP arm_q31_to_float.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_float.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_float.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q31_to_float.o


$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.c
	@echo 'Building DSP arm_sqrt_q31.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FastMathFunctions/arm_sqrt_q31.o

$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q31.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q31.c
	@echo 'Building DSP arm_float_to_q31.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q31.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q31.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_float_to_q31.o


$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.c
	@echo 'Building DSP arm_scale_q31.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_q31.o


$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_q31.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_q31.c
	@echo 'Building DSP arm_biquad_cascade_df1_q31.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_q31.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_q31.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/arm_biquad_cascade_df1_q31.o


$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.c
	@echo 'Building DSP arm_scale_f32.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_scale_f32.o


$(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q31.c: $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q31.c
	@echo 'Building DSP arm_q15_to_q31.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q31.c
CDEPS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q31.d
OBJS += $(OUTPUT_DIR)/$(COPIED_SDK_PATH)/platform/CMSIS/DSP_Lib/Source/SupportFunctions/arm_q15_to_q31.o
