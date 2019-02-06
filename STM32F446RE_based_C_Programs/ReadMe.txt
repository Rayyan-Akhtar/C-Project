This project is based on STM32F446RE ARM microcontroller.
This a simple project in which some commands are send through the UART2 to the microcontroller 
and the microcontroller process the commands and take the desired actions.
There are four command handlers which are exexuted when the user enters the correct commands
from the terminal.

For example: LED_ON
	     LED_OFF
	     LED_BLINK_ON
	     LED_BLINK_OFF

these handler can be changed according to the application.
