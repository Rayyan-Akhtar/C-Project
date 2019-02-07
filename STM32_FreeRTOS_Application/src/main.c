/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "main.h"

// Global variables
TaskHandle_t task1_handle=NULL;
TaskHandle_t task2_handle=NULL;
TaskHandle_t task3_handle=NULL;
TaskHandle_t task4_handle=NULL;

// Queue handler
xQueueHandle uart_write_queue = NULL;
xQueueHandle command_queue = NULL;

// Timer handle
TimerHandle_t timer=NULL;

// Press the key for required action

char commands[] = {"\
\r\nLED_ON              ------> 1 \
\r\nLED_OFF             ------> 2 \
\r\nLED_TOGGLE          ------> 3 \
\r\nLED_TOGGLE_OFF      ------> 4 \
\r\nLED_READ_STATUS     ------> 5 \
\r\nEXIT_APP            ------> 0 \
\r\nEnter your option here:  "};

char usr_buffer[100]={0};

int main(void)
{
	// configure system clock
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	SystemCoreClockUpdate();

	setupHardware();

	// create queue
	uart_write_queue = xQueueCreate(10, sizeof(char *));
	command_queue = xQueueCreate(10, sizeof(CMD_DATA *));

	if(uart_write_queue!=NULL && command_queue!=NULL)
	{
		// create tasks
		xTaskCreate(vTask1_handler, "Task-1", configMINIMAL_STACK_SIZE, NULL, 1, &task1_handle);
		xTaskCreate(vTask2_handler, "Task-2", configMINIMAL_STACK_SIZE, NULL, 2, &task2_handle);
		xTaskCreate(vTask3_handler, "Task-3", configMINIMAL_STACK_SIZE, NULL, 2, &task3_handle);
		xTaskCreate(vTask4_handler, "Task-2", configMINIMAL_STACK_SIZE, NULL, 2, &task4_handle);
		vTaskStartScheduler();
	}

	else
	{
		usart2_send_msg("Queue not created\r\n");
	}

}

void vTask1_handler(void *params) // Display menu
{
	char * pData=NULL;
	pData = commands;
	while(1)
	{
		xQueueSend(uart_write_queue, &pData, portMAX_DELAY);
		// Wait until it notified
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
	}

}

void vTask2_handler(void *params)	// send data to uart
{
	char *pData = NULL;
	while(1)
	{
		xQueueReceive(uart_write_queue, &pData, portMAX_DELAY);
		usart2_send_msg(pData);
	}
}

void vTask3_handler(void *params)
{

	CMD_DATA *pData=NULL;

	//uint32_t command=0;
	while(1)
	{
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
		pData = (CMD_DATA *)pvPortMalloc(sizeof(CMD_DATA *));
		taskENTER_CRITICAL();
		//usart2_send_msg(usart2_buffer);
		pData->command_num = usart2_buffer[0]-48;
		//pData->command_num = command;
		taskEXIT_CRITICAL();
		xQueueSend(command_queue, &pData, portMAX_DELAY);
	}



}

void vTask4_handler(void *params)
{
	CMD_DATA *pData=NULL;
	//pData = (CMD_DATA *)pvPortMalloc(sizeof(CMD_DATA *));
	uint32_t command=0;
	while(1)
	{
		xQueueReceive(command_queue, &pData, portMAX_DELAY);
		command = pData->command_num;
		execute_command(command);
		vPortFree(pData);
	}
}

void setupHardware(void)
{
	setupUart();
	setupGpio();
}

void setupGpio(void)
{
	GPIO_InitTypeDef gpio_init;
	memset(&gpio_init, 0, sizeof(gpio_init));
	gpio_init.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init.GPIO_Pin = GPIO_Pin_5;
	gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_init.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA, &gpio_init);
}

void command1_handler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, SET);
}

void command2_handler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, RESET);
}

void command3_handler(void)
{
	if(timer==NULL)
	{
		timer = xTimerCreate("LED_TIMER", pdMS_TO_TICKS(500), pdTRUE, NULL, toggle_led_start);

		xTimerStart(timer, portMAX_DELAY);
	}
	else
	{
		xTimerStart(timer, portMAX_DELAY);
	}

}

void command4_handler(void)
{
	xTimerStop(timer, portMAX_DELAY);
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, RESET);
}

void command5_handler(void)
{
	char *pData=NULL;
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
	{
		pData = "\r\nLED is ON\r\n";
		xQueueSend(uart_write_queue, &pData, portMAX_DELAY);
	}
	else
	{
		pData = "\r\nLED is OFF\r\n";
		xQueueSend(uart_write_queue, &pData, portMAX_DELAY);
	}
}

void command6_handler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, RESET);
	vTaskDelete(task1_handle);
	vTaskDelete(task2_handle);
	vTaskDelete(task3_handle);
	vTaskDelete(task4_handle);

}

void execute_command(uint32_t cmd)
{
	switch(cmd)
	{
	case 1:
		command1_handler();
		break;
	case 2:
		command2_handler();
		break;
	case 3:
		command3_handler();
		break;
	case 4:
		command4_handler();
		break;
	case 5:
		command5_handler();
		break;
	case 0:
		command6_handler();
		break;
	}
}

void toggle_led_start(TimerHandle_t xTimer)
{
	GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
}
