################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/uart.c 

OBJS += \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/uart.o 

C_DEPS += \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_FreeRTOS_Application/StdPeriph_Driver/inc" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_FreeRTOS_Application/Config" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_FreeRTOS_Application/Third-Party/FreeRTOS/org/Source/include" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_FreeRTOS_Application/Third-Party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_FreeRTOS_Application/Third-Party/FreeRTOS/org/Source/portable/MemMang" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_FreeRTOS_Application/inc" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_FreeRTOS_Application/CMSIS/device" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_FreeRTOS_Application/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


