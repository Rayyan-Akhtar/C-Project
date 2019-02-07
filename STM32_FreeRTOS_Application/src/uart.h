/*
 * uart.h
 *
 *  Created on: Feb 7, 2019
 *      Author: Rayyan
 */

extern char usart2_buffer[200];

void setupUart(void);
void usart2_send_msg(char * buffer);
void USART2_IRQHandler(void);
