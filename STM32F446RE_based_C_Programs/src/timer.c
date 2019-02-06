/*
 * timer.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Rayyan
 */

#include "main.h"

uint32_t counter_value=0;

void setupTimer(void)
{
	// Enable TIM clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Fill the TIM_TimeBaseInitStruct with the desired parameters
	TIM_TimeBaseInitTypeDef timer_base_init;
	memset(&timer_base_init, 0, sizeof(timer_base_init));
	timer_base_init.TIM_ClockDivision = TIM_CKD_DIV4;
	timer_base_init.TIM_CounterMode = TIM_CounterMode_Up;
	timer_base_init.TIM_Period = 752;
	timer_base_init.TIM_Prescaler = 60000;
	TIM_TimeBaseInit(TIM2, & timer_base_init);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	NVIC_EnableIRQ(TIM2_IRQn);

	TIM_Cmd(TIM2, ENABLE);

}

void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2, TIM_FLAG_Update))
	{
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		//uart2_send_msg("Hello World-1\r\n");
		if(blink_flag)
		{
			GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
		}
		//GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
	}
}
