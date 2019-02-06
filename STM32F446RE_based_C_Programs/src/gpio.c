/*
 * gpio.c
 *
 *  Created on: Feb 6, 2019
 *      Author: Rayyan
 */

#include "main.h"

void gpio_config(void)
{
	//  configure clock for PORT A
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// configure PORTA
	GPIO_InitTypeDef gpio_portA;
	memset(&gpio_portA, 0, sizeof(gpio_portA));
	gpio_portA.GPIO_Mode = GPIO_Mode_OUT;
	gpio_portA.GPIO_Pin = GPIO_Pin_5;
	gpio_portA.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_portA.GPIO_Speed = GPIO_Low_Speed;

	GPIO_Init(GPIOA, &gpio_portA);
}
