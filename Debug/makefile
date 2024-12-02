################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/UART/subdir.mk
-include source/SREC_LAYER/subdir.mk
-include source/QUEUE/subdir.mk
-include source/FLASH/subdir.mk
-include source/BOOT_LOADER/subdir.mk
-include source/APPLICATION/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := DatPV18_MOOC_BOOT_LOADER
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: DatPV18_MOOC_BOOT_LOADER.axf

# Tool invocations
DatPV18_MOOC_BOOT_LOADER.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="DatPV18_MOOC_BOOT_LOADER.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m0plus -mthumb -T DatPV18_MOOC_BOOT_LOADER_Debug.ld -o "DatPV18_MOOC_BOOT_LOADER.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) DatPV18_MOOC_BOOT_LOADER.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "DatPV18_MOOC_BOOT_LOADER.axf"; # arm-none-eabi-objcopy -v -O binary "DatPV18_MOOC_BOOT_LOADER.axf" "DatPV18_MOOC_BOOT_LOADER.bin" ; # checksum -p MKE16Z64xxx4 -d "DatPV18_MOOC_BOOT_LOADER.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
