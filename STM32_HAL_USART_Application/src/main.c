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

UART_HandleTypeDef huart = {0};
char usr_buffer[USR_BUFFER_LEN] = "************ Peripherals Initialized ************\r\n";
char rec_buffer[REC_BUFFER_LEN] = {0};
char command_buffer[COMMAND_BUFFER_LEN] = {0};
char rtc_buffer[RTC_BUFFER_LEN] = {0};

char *commands[] = {"NULL\r\n", "LED_ON\r\n", "LED_OFF\r\n", "TOGGLE_ON\r\n", "TOGGLE_OFF\r\n", "RTC_STATUS\r\n"};

RTC_TimeTypeDef rtc_time = {0};
RTC_DateTypeDef rtc_date = {0};

// Implement void HAL_MspInit(void) in stm32f4xx_hal_msp_template.c
// call HAL_UART_IRQHandler(&huart); in void USART2_IRQHandler(void) in stm32f4xx_it.c

int main(void)
{

	HAL_Init();

	setup_hardware();

	HAL_UART_Transmit_IT(&huart, (uint8_t *)usr_buffer, strlen(usr_buffer));

	HAL_UART_Receive_IT(&huart, (uint8_t *)rec_buffer, 1);

	for(;;)
	{
		//HAL_Delay(1000);
		//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	}
}


void setup_hardware(void)
{
	setup_sys_clock();
	setup_gpio();
	setup_uart();
	setup_timer();
	setup_rtc();
}

void setup_sys_clock(void)
{
	RCC_OscInitTypeDef osc_init = {0};
	RCC_ClkInitTypeDef clk_init = {0};
	RCC_PeriphCLKInitTypeDef pClk = {0};

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSEState = RCC_HSE_OFF;
	osc_init.LSEState = RCC_LSE_OFF;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.LSIState = RCC_LSI_ON;
	osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	osc_init.PLL.PLLSource = RCC_PLL_NONE;
	HAL_RCC_OscConfig(&osc_init);

	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	clk_init.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider = RCC_SYSCLK_DIV1;
	clk_init.APB2CLKDivider = RCC_SYSCLK_DIV1;
	HAL_RCC_ClockConfig(&clk_init, FLASH_LATENCY_5);

	pClk.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	pClk.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;

	HAL_RCCEx_PeriphCLKConfig(&pClk);
}

void setup_gpio(void)
{
	// configure GPIOA
	// Enable clock for GPIOA
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef gpio_init = {0};
	gpio_init.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init.Pin = GPIO_PIN_5;
	gpio_init.Pull = GPIO_NOPULL;
	gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &gpio_init);
}

void execute_command(uint8_t cmd)
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

	default:
		default_handler();
		break;
	}
}

void command1_handler(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

void command2_handler(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void command3_handler(void)
{
	HAL_TIM_Base_Start_IT(&htim2);
}

void command4_handler(void)
{
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void command5_handler(void)
{
	HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);
	sprintf(rtc_buffer, "Time: %02d:%02d:%02d\r\n", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds);
	HAL_UART_Transmit_IT(&huart, (uint8_t *)rtc_buffer, strlen(rtc_buffer));
}

void default_handler(void)
{
	HAL_UART_Transmit_IT(&huart, (uint8_t *)"Invalid Command\r\n", strlen("Invalid Command\r\n"));
}
