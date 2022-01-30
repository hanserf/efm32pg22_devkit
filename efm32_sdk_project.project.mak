####################################################################
# Automatically-generated file. Do not edit!                       #
# Makefile Version 7                                               #
####################################################################

BASE_SDK_PATH = /home/s3rf/workarea-qfree/SimplicityStudio_v5/developer/sdks/gecko_sdk_suite/v3.2
UNAME:=$(shell uname -s | sed -e 's/^\(CYGWIN\).*/\1/' | sed -e 's/^\(MINGW\).*/\1/')
ifeq ($(UNAME),MINGW)
# Translate "C:/super" into "/C/super" for MinGW make.
SDK_PATH := /$(shell echo $(BASE_SDK_PATH) | sed s/://)
endif
SDK_PATH ?= $(BASE_SDK_PATH)
COPIED_SDK_PATH ?= gecko_sdk_3.2.2

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
 '-DEFM32PG22C200F512IM40=1' \
 '-DSL_COMPONENT_CATALOG_PRESENT=1'

ASM_DEFS += \
 '-DDEBUG_EFM=1' \
 '-DEFM32PG22C200F512IM40=1' \
 '-DSL_COMPONENT_CATALOG_PRESENT=1'

INCLUDES += \
 -Iconfig \
 -Iautogen \
 -I. \
 -I$(COPIED_SDK_PATH)/platform/Device/SiliconLabs/EFM32PG22/Include \
 -I$(COPIED_SDK_PATH)/hardware/board/inc \
 -I$(COPIED_SDK_PATH)/platform/CMSIS/Include \
 -I$(COPIED_SDK_PATH)/platform/service/device_init/inc \
 -I$(COPIED_SDK_PATH)/platform/emlib/inc \
 -I$(COPIED_SDK_PATH)/platform/common/inc \
 -I$(COPIED_SDK_PATH)/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart \
 -I$(COPIED_SDK_PATH)/platform/common/toolchain/inc \
 -I$(COPIED_SDK_PATH)/platform/service/system/inc \
 -I$(COPIED_SDK_PATH)/platform/service/udelay/inc

GROUP_START =-Wl,--start-group
GROUP_END =-Wl,--end-group

PROJECT_LIBS = \
 -lgcc \
 -lc \
 -lm \
 -lnosys

LIBS += $(GROUP_START) $(PROJECT_LIBS) $(GROUP_END)

LIB_FILES += $(filter %.a, $(PROJECT_LIBS))

C_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -std=c99 \
 -Wall \
 -Wextra \
 -Os \
 -fdata-sections \
 -ffunction-sections \
 -fomit-frame-pointer \
 -fno-builtin \
 -imacros sl_gcc_preinclude.h \
 --specs=nano.specs \
 -g

CXX_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -std=c++11 \
 -fno-rtti \
 -fno-exceptions \
 -Wall \
 -Wextra \
 -Os \
 -fdata-sections \
 -ffunction-sections \
 -fomit-frame-pointer \
 -fno-builtin \
 -imacros sl_gcc_preinclude.h \
 --specs=nano.specs \
 -g

ASM_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -imacros sl_gcc_preinclude.h \
 -x assembler-with-cpp

LD_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -T"autogen/linkerfile.ld" \
 --specs=nano.specs \
 -Xlinker -Map=$(OUTPUT_DIR)/$(PROJECTNAME).map \
 -Wl,--gc-sections


####################################################################
# SDK Build Rules                                                  #
####################################################################
$(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.o: $(COPIED_SDK_PATH)/hardware/board/src/sl_board_control_gpio.c
	@echo 'Building $(COPIED_SDK_PATH)/hardware/board/src/sl_board_control_gpio.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/hardware/board/src/sl_board_control_gpio.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.o

$(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.o: $(COPIED_SDK_PATH)/hardware/board/src/sl_board_init.c
	@echo 'Building $(COPIED_SDK_PATH)/hardware/board/src/sl_board_init.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/hardware/board/src/sl_board_init.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.o

$(OUTPUT_DIR)/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.o: $(COPIED_SDK_PATH)/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c
	@echo 'Building $(COPIED_SDK_PATH)/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.o

$(OUTPUT_DIR)/sdk/platform/common/toolchain/src/sl_memory.o: $(COPIED_SDK_PATH)/platform/common/toolchain/src/sl_memory.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/common/toolchain/src/sl_memory.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/common/toolchain/src/sl_memory.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/toolchain/src/sl_memory.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/toolchain/src/sl_memory.o

$(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFM32PG22/Source/GCC/startup_efm32pg22.o: $(COPIED_SDK_PATH)/platform/Device/SiliconLabs/EFM32PG22/Source/GCC/startup_efm32pg22.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/Device/SiliconLabs/EFM32PG22/Source/GCC/startup_efm32pg22.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/Device/SiliconLabs/EFM32PG22/Source/GCC/startup_efm32pg22.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFM32PG22/Source/GCC/startup_efm32pg22.d
OBJS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFM32PG22/Source/GCC/startup_efm32pg22.o

$(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFM32PG22/Source/system_efm32pg22.o: $(COPIED_SDK_PATH)/platform/Device/SiliconLabs/EFM32PG22/Source/system_efm32pg22.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/Device/SiliconLabs/EFM32PG22/Source/system_efm32pg22.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/Device/SiliconLabs/EFM32PG22/Source/system_efm32pg22.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFM32PG22/Source/system_efm32pg22.d
OBJS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFM32PG22/Source/system_efm32pg22.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_assert.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_assert.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_assert.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_assert.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_assert.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_assert.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_cmu.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_cmu.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_cmu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_core.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_core.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_core.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_emu.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_emu.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_emu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_gpcrc.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_gpcrc.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_gpcrc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_gpio.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_gpio.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_gpio.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_ldma.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_ldma.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_ldma.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_pdm.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_pdm.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_pdm.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_pdm.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_pdm.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_pdm.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_prs.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_prs.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_prs.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_system.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_system.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_system.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_timer.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_timer.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.o: $(COPIED_SDK_PATH)/platform/emlib/src/em_usart.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/emlib/src/em_usart.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/emlib/src/em_usart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s2.o: $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s2.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s2.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_emu_s2.o: $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_emu_s2.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_emu_s2.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_emu_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_emu_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_emu_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_hfxo_s2.o: $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_hfxo_s2.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_hfxo_s2.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_hfxo_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_hfxo_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_hfxo_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfxo_s2.o: $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_lfxo_s2.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_lfxo_s2.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_lfxo_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfxo_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfxo_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_nvic.o: $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_nvic.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_nvic.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/service/device_init/src/sl_device_init_nvic.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_nvic.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_nvic.o

$(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.o: $(COPIED_SDK_PATH)/platform/service/system/src/sl_system_init.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/service/system/src/sl_system_init.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/service/system/src/sl_system_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.o

$(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_process_action.o: $(COPIED_SDK_PATH)/platform/service/system/src/sl_system_process_action.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/service/system/src/sl_system_process_action.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/service/system/src/sl_system_process_action.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_process_action.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_process_action.o

$(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.o: $(COPIED_SDK_PATH)/platform/service/udelay/src/sl_udelay.c
	@echo 'Building $(COPIED_SDK_PATH)/platform/service/udelay/src/sl_udelay.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/service/udelay/src/sl_udelay.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.o

$(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.o: $(COPIED_SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S
	@echo 'Building $(COPIED_SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S'
	$(ECHO)$(CC) $(ASMFLAGS) -c -o $@ $(COPIED_SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S
ASMDEPS_S += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.o

$(OUTPUT_DIR)/project/app.o: app.c
	@echo 'Building app.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ app.c
CDEPS += $(OUTPUT_DIR)/project/app.d
OBJS += $(OUTPUT_DIR)/project/app.o

$(OUTPUT_DIR)/project/autogen/sl_board_default_init.o: autogen/sl_board_default_init.c
	@echo 'Building autogen/sl_board_default_init.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_board_default_init.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_board_default_init.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_board_default_init.o

$(OUTPUT_DIR)/project/autogen/sl_device_init_clocks.o: autogen/sl_device_init_clocks.c
	@echo 'Building autogen/sl_device_init_clocks.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_device_init_clocks.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_device_init_clocks.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_device_init_clocks.o

$(OUTPUT_DIR)/project/autogen/sl_event_handler.o: autogen/sl_event_handler.c
	@echo 'Building autogen/sl_event_handler.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_event_handler.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_event_handler.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_event_handler.o

$(OUTPUT_DIR)/project/main.o: main.c
	@echo 'Building main.c'
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ main.c
CDEPS += $(OUTPUT_DIR)/project/main.d
OBJS += $(OUTPUT_DIR)/project/main.o

# Automatically-generated Simplicity Studio Metadata
# Please do not edit or delete these lines!
# SIMPLICITY_STUDIO_METADATA=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=END_SIMPLICITY_STUDIO_METADATA
# END OF METADATA