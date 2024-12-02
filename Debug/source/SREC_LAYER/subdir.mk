################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/SREC_LAYER/srec.c 

C_DEPS += \
./source/SREC_LAYER/srec.d 

OBJS += \
./source/SREC_LAYER/srec.o 


# Each subdirectory must supply rules for building sources it contributes
source/SREC_LAYER/%.o: ../source/SREC_LAYER/%.c source/SREC_LAYER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\board" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\source" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\drivers" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\component\lists" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\source\UART" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\source\SREC_LAYER" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\source\FLASH" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\source\QUEUE" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\source\BOOT_LOADER" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\source\APPLICATION" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\component\uart" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\component\serial_manager" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\utilities" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\device" -I"C:\Users\phamd\Documents\MCUXpressoIDE_24.9.25\workspace\DatPV18_MOOC_BOOT_LOADER\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-SREC_LAYER

clean-source-2f-SREC_LAYER:
	-$(RM) ./source/SREC_LAYER/srec.d ./source/SREC_LAYER/srec.o

.PHONY: clean-source-2f-SREC_LAYER
