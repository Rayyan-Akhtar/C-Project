/*
 * i2c.h
 *
 *  Created on: Feb 17, 2019
 *      Author: Rayyan
 */


#define AM 0
#define PM 1
#define RTC_HOUR_FORMAT_12 1
#define RTC_HOUR_FORMAT_24 0

typedef struct rtc{
	uint8_t second; // 0-59
	uint8_t minute; // 0-59
	uint8_t hour;	// 0-23 or 0-12
	uint8_t AMPM;
	uint8_t rtc_hour_format;
}rtc_time;

extern I2C_HandleTypeDef hi2c1;
//extern rtc_time DS3231;


void setup_i2c(void);
void set_rtc_time(rtc_time * time);
void get_rtc_time(rtc_time * time);
