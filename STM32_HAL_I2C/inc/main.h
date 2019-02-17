/*
 * main.h
 *
 *  Created on: Feb 16, 2019
 *      Author: Rayyan
 */


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"
#include "stm32f4xx_hal.h"
#include "uart.h"
#include "timer.h"
#include "i2c.h"

#define USR_BUFFER_LEN 100
#define REC_BUFFER_LEN 10
#define COMMAND_BUFFER_LEN 100
#define RTC_BUFFER_LEN 50
#define I2C_BUFFER_LEN 2


void setup_hardware(void);
void setup_sys_clock(void);
void setup_gpio(void);
void setup_uart(void);
void execute_command(uint8_t cmd);
void command1_handler(void);
void command2_handler(void);
void command3_handler(void);
void command4_handler(void);
void command5_handler(void);
void command6_handler(void);
void default_handler(void);
void blink_led(void);

extern char usr_buffer[USR_BUFFER_LEN];
extern char rec_buffer[REC_BUFFER_LEN];
extern char command_buffer[COMMAND_BUFFER_LEN];
extern char rtc_buffer[RTC_BUFFER_LEN];
extern char i2c_buffer[I2C_BUFFER_LEN];

extern UART_HandleTypeDef huart;
extern char *commands[];
