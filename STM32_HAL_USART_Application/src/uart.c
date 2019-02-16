/*
 * uart.c
 *
 *  Created on: Feb 16, 2019
 *      Author: Rayyan
 */

#include "main.h"
uint8_t command_pointer = 0;

void setup_uart(void)
{
	huart.Instance = USART2;
	huart.Init.BaudRate = 115200;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	HAL_UART_Init(&huart);
}

void HAL_UART_MspInit(UART_HandleTypeDef * huart)
{
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_UART_ENABLE_IT(huart, UART_IT_TC);

	GPIO_InitTypeDef gpio_init = {0};
	gpio_init.Alternate = GPIO_AF7_USART2;
	gpio_init.Mode = GPIO_MODE_AF_PP;
	gpio_init.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	gpio_init.Pull = GPIO_PULLUP;
	gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &gpio_init);

	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(rec_buffer[0] == '\n')
	{
		command_pointer=0;
		command_buffer[command_pointer] = 0;
	}
	else
	{
		command_buffer[command_pointer++] = rec_buffer[0];
	}


	if(rec_buffer[0] == '\r')
	{
		command_buffer[command_pointer++] = '\n';
		command_buffer[command_pointer] = 0;
		command_pointer=0;
		//HAL_UART_Transmit(huart, (uint8_t *)command_buffer, strlen(command_buffer), 100);
		uint8_t default_case = 0;
		for(uint8_t i=0; i<6; i++)
		{
			if(!strcmp(command_buffer, commands[i]))
			{
				default_case = 1;
				execute_command(i);
			}
		}

		if(!default_case)
		{
			execute_command(0);
			default_case = 0;
		}
	}

	HAL_UART_Receive_IT(huart, (uint8_t *)rec_buffer, 1);

}


