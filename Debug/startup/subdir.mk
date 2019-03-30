################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"C:/Users/123iv/workspace/test_led2/HAL_Driver/Inc/Legacy" -I"C:/Users/123iv/workspace/test_led2/inc" -I"C:/Users/123iv/workspace/test_led2/CMSIS/device" -I"C:/Users/123iv/workspace/test_led2/CMSIS/core" -I"C:/Users/123iv/workspace/test_led2/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


