################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f446xx.s 

OBJS += \
./startup/startup_stm32f446xx.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_HAL_I2C/HAL_Driver/Inc/Legacy" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_HAL_I2C/Utilities/STM32F4xx-Nucleo" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_HAL_I2C/inc" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_HAL_I2C/CMSIS/device" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_HAL_I2C/CMSIS/core" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_HAL_I2C/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

