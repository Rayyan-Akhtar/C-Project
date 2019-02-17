/*
 * i2c.c
 *
 *  Created on: Feb 17, 2019
 *      Author: Rayyan
 */

#include "main.h"

I2C_HandleTypeDef hi2c1;


void setup_i2c(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  HAL_I2C_Init(&hi2c1);
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }

}

void set_rtc_time(rtc_time * time)
{
	i2c_buffer[0] = 0x00;
	i2c_buffer[1] = RTC_ByteToBcd2(time->second);
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0, (uint8_t *)i2c_buffer, 2, 10);

	i2c_buffer[0] = 0x01;
	i2c_buffer[1] = RTC_ByteToBcd2(time->minute);
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0, (uint8_t *)i2c_buffer, 2, 10);

	// Hour foramtting
	if(time->AMPM == AM && time->rtc_hour_format == RTC_HOUR_FORMAT_12)
	{
		i2c_buffer[1] = RTC_ByteToBcd2(time->hour);
		i2c_buffer[1] &= 0b01011111;
	}
	else if (time->AMPM == PM && time->rtc_hour_format == RTC_HOUR_FORMAT_12)
	{
		i2c_buffer[1] = RTC_ByteToBcd2(time->hour);
		i2c_buffer[1] &= 0b01111111;
	}
	else if (time->rtc_hour_format == RTC_HOUR_FORMAT_24)
	{
		i2c_buffer[1] = RTC_ByteToBcd2(time->hour);
	}

	i2c_buffer[0] = 0x02;
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0, (uint8_t *)i2c_buffer, 2, 10);
}

void get_rtc_time(rtc_time * time)
{
	uint8_t val = 0;

	i2c_buffer[0] = 0x00;
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0, (uint8_t *)i2c_buffer, 1, 10);
	HAL_I2C_Master_Receive(&hi2c1, 0xD0, (uint8_t *)&i2c_buffer[1], 1, 10);
	val = RTC_Bcd2ToByte(i2c_buffer[1]);
	time->second = val;

	i2c_buffer[0] = 0x01;
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0, (uint8_t *)i2c_buffer, 1, 10);
	HAL_I2C_Master_Receive(&hi2c1, 0xD0, (uint8_t *)&i2c_buffer[1], 1, 10);
	val = RTC_Bcd2ToByte(i2c_buffer[1]);
	time->minute = val;

	// Hour formatting
	i2c_buffer[0] = 0x02;
	HAL_I2C_Master_Transmit(&hi2c1, 0xD0, (uint8_t *)i2c_buffer, 1, 10);
	HAL_I2C_Master_Receive(&hi2c1, 0xD0, (uint8_t *)&i2c_buffer[1], 1, 10);

	if((i2c_buffer[1] & 0b01000000) == 1)
	{
		time->rtc_hour_format = RTC_HOUR_FORMAT_12;
		time->AMPM = AM;
	}
	else if ((i2c_buffer[1] & 0b01000000) == 1 && (i2c_buffer[1] & 0b00100000) == 1)
	{
		time->rtc_hour_format = RTC_HOUR_FORMAT_12;
		time->AMPM = PM;
	}
	else if ((i2c_buffer[1] & 0b01000000) == 0)
	{
		time->rtc_hour_format = RTC_HOUR_FORMAT_24;
	}

	val = RTC_Bcd2ToByte(i2c_buffer[1]);
	time->hour = val;
}
