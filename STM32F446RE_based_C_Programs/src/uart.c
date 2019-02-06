/*
 * uart.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Rayyan
 */

#include "main.h"

uint32_t command_len = 0;

extern char *commands[];

void setupUart(void)
{
	USART_InitTypeDef uart;
	GPIO_InitTypeDef gpio_uart;
	// Enable clock sources for uart
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	// Enable clock source for GPIO
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// configure GPIOA for UART
	memset(&gpio_uart, 0, sizeof(gpio_uart));
	gpio_uart.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio_uart.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_uart.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(GPIOA, &gpio_uart);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	// Configure UART2
	memset(&uart, 0, sizeof(uart));
	uart.USART_BaudRate = 115200;
	uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	uart.USART_Parity = USART_Parity_No;
	uart.USART_StopBits = USART_StopBits_1;
	uart.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &uart);

	// Set up USART receive interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	// Set up NVIC USART interrupt
	NVIC_EnableIRQ(USART2_IRQn);

	// Enable UART
	USART_Cmd(USART2, ENABLE);
}

void uart2_send_msg(char * buffer)
{
	int i=0;
	while(*(buffer + i) != 0)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);
		USART_SendData(USART2, *(buffer + i++));
	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE))
	{
		usart2_buffer[command_len++] = (char)USART_ReceiveData(USART2);
	}
	if(usart2_buffer[command_len-1] == '\r')
	{
		usart2_buffer[command_len] = '\n';
		command_len++;
		usart2_buffer[command_len] = 0;
		command_len=0;

		if(!strcmp(usart2_buffer,commands[0]))
		{
			command1_handler();
		}

		else if(!strcmp(usart2_buffer,commands[1]))
		{
			command2_handler();
		}

		else if(!strcmp(usart2_buffer,commands[2]))
		{
			command3_handler();
		}

		else if(!strcmp(usart2_buffer,commands[3]))
		{
			command4_handler();
		}
		else
		{
			uart2_send_msg("Invalid Command\r\n");
		}

	}
}
