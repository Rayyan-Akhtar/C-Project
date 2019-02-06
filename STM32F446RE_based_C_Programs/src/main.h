/*
 * main.h
 *
 *  Created on: Feb 5, 2019
 *      Author: Rayyan
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "functions.h"

extern char usr_msg[100];
extern char usart2_buffer[200];
extern uint8_t blink_flag;

// Function prototypes
void setupHardware(void);
void init_msg(void);
