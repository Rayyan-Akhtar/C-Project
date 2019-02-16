/*
 * timer.c
 *
 *  Created on: Feb 16, 2019
 *      Author: Rayyan
 */

#include "main.h"

TIM_HandleTypeDef htim2 = {0};

void setup_timer(void)
{
	htim2.Instance = TIM2;
	htim2.Channel = HAL_TIM_ACTIVE_CHANNEL_1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Prescaler = 40000; // 5 ms
	htim2.Init.Period = 400;
	HAL_TIM_Base_Init(&htim2);

	//HAL_TIM_Base_Start_IT(&htim2);

	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);

	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	__HAL_RCC_TIM2_CLK_ENABLE();

	TIM_ClockConfigTypeDef tim2_cfg = {0};
	tim2_cfg.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	tim2_cfg.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
	tim2_cfg.ClockPolarity = TIM_CLOCKPOLARITY_RISING;
	tim2_cfg.ClockFilter = 0;
	HAL_TIM_ConfigClockSource(htim, &tim2_cfg);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
