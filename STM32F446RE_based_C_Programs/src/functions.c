/*
 * functions.c
 *
 *  Created on: Feb 6, 2019
 *      Author: Rayyan
 */

#include "main.h"

void command1_handler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, 1);
	uart2_send_msg("LED IS ON\r\n");
}

void command2_handler(void)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, 0);
	uart2_send_msg("LED IS OFF\r\n");
	blink_flag = 0;
}

void command3_handler(void)
{
	blink_flag = 1;
}

void command4_handler(void)
{
	blink_flag = 0;
}

void command5_handler(void)
{

}

uint8_t str_cmp(char * s1, const char * s2)
{
	uint16_t len = str_len(s2);
	int i=0;
	while(*(s1 + i) != *(s2 + i) && i<=len)
	{
		i++;
	}

	if(i<len)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

uint16_t str_len(const char * str)
{
	uint16_t len = 0;
	while(*(str+len)!=0)
	{
		len++;
	}

	return len;
}
