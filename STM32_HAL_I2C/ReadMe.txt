It is based on Nucleo-STM32F446RE development board from ST.

This includes USART, I2C, Timer.

External RTC device DS3231 is connected to the I2C peripheral of the microcontroller.

User can input the commands through the terminal for example tera term and the controller will perform the task accordingly.

The source files are in src folder.

Timer interrupt is used to toggle the LED.

Basic commands are given below.
"LED_ON\r\n", "LED_OFF\r\n", "TOGGLE_ON\r\n", "TOGGLE_OFF\r\n", "RTC_STATUS\r\n", "LED_STATUS\r\n"
The commands are self explanatory.

HAL library is used to programe the microcontroller.