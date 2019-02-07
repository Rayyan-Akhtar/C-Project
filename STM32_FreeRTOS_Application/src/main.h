/*
 * main.h
 *
 *  Created on: Feb 7, 2019
 *      Author: Rayyan
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "uart.h"

extern TaskHandle_t task1_handle;
extern TaskHandle_t task2_handle;
extern TaskHandle_t task3_handle;
extern TaskHandle_t task4_handle;
extern xQueueHandle uart_write_queue;
extern xQueueHandle command_queue;

typedef struct CMD{
	uint32_t command_num;
	char command_name[20];
}CMD_DATA;

void vTask1_handler(void *params);
void vTask2_handler(void *params);
void vTask3_handler(void *params);
void vTask4_handler(void *params);

void setupHardware(void);
void setupGpio(void);

void command1_handler(void);
void command2_handler(void);
void command3_handler(void);
void command4_handler(void);
void command5_handler(void);
void command6_handler(void);

void execute_command(uint32_t cmd);
void toggle_led_start(TimerHandle_t xTimer);
