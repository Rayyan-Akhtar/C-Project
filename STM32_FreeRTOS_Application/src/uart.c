/*
 * uart.c
 *
 *  Created on: Feb 7, 2019
 *      Author: Rayyan
 */

#include "main.h"

char usart2_buffer[200] = {0};
uint32_t usart2_buffer_pointer = 0;

void setupUart(void)
{
	// configure clock for uart
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	// configure clock for GPIOA for uart
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// configure USART parameters
	USART_InitTypeDef usart2_init;
	memset(&usart2_init, 0, sizeof(usart2_init));
	usart2_init.USART_BaudRate = 115200;
	usart2_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart2_init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart2_init.USART_Parity = USART_Parity_No;
	usart2_init.USART_StopBits = USART_StopBits_1;
	usart2_init.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, & usart2_init);

	// configure GPIO parameters
	GPIO_InitTypeDef gpio_init;
	memset(&gpio_init, 0, sizeof(gpio_init));
	gpio_init.GPIO_Mode = GPIO_Mode_AF;
	gpio_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA, &gpio_init);

	// configure GPIO alternate functions
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	// configure interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	// set the priority of UART interrupt in NVIC
	NVIC_SetPriority(USART2_IRQn, 5);

	// configure NVIC interrupt
	NVIC_EnableIRQ(USART2_IRQn);

	USART_Cmd(USART2, ENABLE);
}

void usart2_send_msg(char * buffer)
{
	uint32_t i=0;
	while(*(buffer + i)!=0)
	{
		while(!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
		USART_SendData(USART2, *(buffer + i++));
	}
}

void USART2_IRQHandler(void)
{
	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE))
	{
		usart2_buffer[usart2_buffer_pointer] = (char) USART_ReceiveData(USART2);
		usart2_buffer_pointer++;
	}

	if(usart2_buffer[usart2_buffer_pointer-1]=='\r')
	{
		usart2_buffer[usart2_buffer_pointer] = '\n';
		usart2_buffer_pointer++;
		usart2_buffer[usart2_buffer_pointer] = 0;
		usart2_buffer_pointer=0;
		//usart2_send_msg(usart2_buffer);
		// Notify task 1 in order to print the options again on the screen
		xTaskNotifyFromISR(task1_handle,0,eNoAction, &pxHigherPriorityTaskWoken);

		// notify to the task 3 to read the data from uart_queue and send it to command queue
		xTaskNotifyFromISR(task3_handle,0,eNoAction, &pxHigherPriorityTaskWoken);
		//usart2_send_msg("Exiting ISR\r\n");
	}

	if(pxHigherPriorityTaskWoken)
	{
		taskYIELD();
	}
}
