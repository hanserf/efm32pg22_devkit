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
 '-DDEBUG_EFM=1' \
 '-DEFM32PG22C200F512IM40=1'

ASM_DEFS += \
 '-DDEBUG_EFM=1' \
 '-DEFM32PG22C200F512IM40=1' \

INCLUDES += \
 -I$(MY_SRC_PATH)
 
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


