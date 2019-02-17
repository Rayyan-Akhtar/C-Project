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
char i2c_buffer[I2C_BUFFER_LEN] = {0};

char *commands[] = {"NULL\r\n", "LED_ON\r\n", "LED_OFF\r\n", "TOGGLE_ON\r\n", "TOGGLE_OFF\r\n", "RTC_STATUS\r\n", "LED_STATUS\r\n"};
rtc_time DS3231 = {0};
// Implement void HAL_MspInit(void) in stm32f4xx_hal_msp_template.c
// call HAL_UART_IRQHandler(&huart); in void USART2_IRQHandler(void) in stm32f4xx_it.c

int main(void)
{

	HAL_Init();

	setup_hardware();

	HAL_UART_Transmit_IT(&huart, (uint8_t *)usr_buffer, strlen(usr_buffer));

	HAL_UART_Receive_IT(&huart, (uint8_t *)rec_buffer, 1);

	if(HAL_I2C_IsDeviceReady(&hi2c1, 0xD0, 2, 10) == HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	}

	i2c_buffer[0] = 0x0E;
	i2c_buffer[1] = 0x00;
	if(HAL_I2C_Master_Transmit(&hi2c1, 0xD0, (uint8_t *)i2c_buffer, 2, 10)==HAL_OK)
	{
		blink_led();
	}

	// Start the RTC
	i2c_buffer[0] = 0x00;
	i2c_buffer[1] = 0x01;
	if(HAL_I2C_Master_Transmit(&hi2c1, 0xD0, (uint8_t *)i2c_buffer, 2, 10)==HAL_OK)
	{
		blink_led();
	}

	// Initializing the RTC time
	DS3231.second = 0;
	DS3231.minute = 24;
	DS3231.hour = 9;
	DS3231.AMPM = AM;

	set_rtc_time(&DS3231);

	//uint8_t val=0;
	for(;;)
	{

	}
}


void setup_hardware(void)
{
	setup_sys_clock();
	setup_gpio();
	setup_uart();
	setup_timer();
	setup_i2c();
}

void setup_sys_clock(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/**Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 180;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);
	/**Activate the Over-Drive mode
	 */
	HAL_PWREx_EnableOverDrive();

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
								|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
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

	case 6:
		command6_handler();
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
	get_rtc_time(&DS3231);
	if(DS3231.AMPM == PM && DS3231.rtc_hour_format == RTC_HOUR_FORMAT_24)
	{
		sprintf(usr_buffer, "Time: %02d:%02d:%02d PM\r\n", DS3231.hour, DS3231.minute, DS3231.second);
	}

	else if (DS3231.AMPM == AM && DS3231.rtc_hour_format == RTC_HOUR_FORMAT_24)
	{
		sprintf(usr_buffer, "Time: %02d:%02d:%02d AM\r\n", DS3231.hour, DS3231.minute, DS3231.second);
	}

	else if (DS3231.rtc_hour_format == RTC_HOUR_FORMAT_24)
	{
		sprintf(usr_buffer, "Time: %02d:%02d:%02d\r\n", DS3231.hour, DS3231.minute, DS3231.second);
	}
	HAL_UART_Transmit_IT(&huart, (uint8_t *)usr_buffer, strlen(usr_buffer));

}

void command6_handler(void)
{
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET)
	{
		HAL_UART_Transmit_IT(&huart, (uint8_t *)"LED STATUS: ON\r\n", strlen("LED STATUS: ON\r\n"));
	}
	else
	{
		HAL_UART_Transmit_IT(&huart, (uint8_t *)"LED STATUS: OFF\r\n", strlen("LED STATUS: OFF\r\n"));
	}

}

void default_handler(void)
{
	HAL_UART_Transmit_IT(&huart, (uint8_t *)"Invalid Command\r\n", strlen("Invalid Command\r\n"));
}

void blink_led(void)
{
	for(int i=0; i<2; i++)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
}
