/*
 * uart.h
 *
 *  Created on: Feb 5, 2019
 *      Author: Rayyan
 */


void setupUart(void);
void uart2_send_msg(char * buffer);

// Interrupt Handler prototype
void USART2_IRQHandler(void);
