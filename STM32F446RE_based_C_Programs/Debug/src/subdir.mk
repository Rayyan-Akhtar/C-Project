################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/functions.c \
../src/gpio.c \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/timer.c \
../src/uart.c 

OBJS += \
./src/functions.o \
./src/gpio.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/timer.o \
./src/uart.o 

C_DEPS += \
./src/functions.d \
./src/gpio.d \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/timer.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_UART/StdPeriph_Driver/inc" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_UART/inc" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_UART/CMSIS/device" -I"C:/Users/Rayyan/OneDrive/Documents/RTOS_workspace/STM32_UART/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


