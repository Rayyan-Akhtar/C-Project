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

char usr_msg[100]={0};
char usart2_buffer[200]= {0};
uint8_t blink_flag = 0;

char *commands[] = {
		"LED_ON\r\n",
		"LED_OFF\r\n",
		"LED_BLINK_ON\r\n",
		"LED_BLINK_OFF\r\n"
};

int main(void)
{
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	SystemCoreClockUpdate();

	setupHardware();

	init_msg();

	//uint32_t counter_value=0;
	while(1)
	{
		//while(!TIM_GetFlagStatus(TIM2, TIM_FLAG_Update));
		//TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		//uart2_send_msg("Hello World-1\r\n");
		//counter_value = TIM_GetCounter(TIM2);
		//sprintf(usr_msg, "Counter: %ld\r\n", counter_value);
		//uart2_send_msg(usr_msg);
	}


}


void setupHardware(void)
{
	setupUart();
	setupTimer();
	gpio_config();
}

void init_msg(void)
{
	uart2_send_msg("System Initialized\r\n");
}
