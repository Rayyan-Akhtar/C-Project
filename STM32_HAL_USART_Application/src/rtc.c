/*
 * rtc.c
 *
 *  Created on: Feb 16, 2019
 *      Author: Rayyan
 */

#include "main.h"

RTC_HandleTypeDef hrtc = {0};

void setup_rtc(void)
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 255;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	HAL_RTC_Init(&hrtc);

	sTime.Hours = 18;
	sTime.Minutes = 30;
	sTime.Seconds = 25;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month = RTC_MONTH_JANUARY;
	sDate.Date = 1;
	sDate.Year = 19;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
	//__HAL_RCC_PWR_CLK_ENABLE();
	//HAL_PWR_EnableBkUpAccess();

	//__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	//__HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSI);

	__HAL_RCC_RTC_ENABLE();
}
