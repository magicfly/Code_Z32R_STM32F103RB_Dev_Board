#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "pwm.h"
#include "key.h"
#include "usart.h"
#include "TFT018.h"
#include "lcd.h"

#define DEBOUNCE_MS 20
int main(void){
	/***@brief main function***/
	USART_COM_Init(115200);
	LCD_PWM_Init(100, 0 ,80);
	LCD_GPIO_Init();
	LCD_Init();
	LCD_Clear_Screen(Black);
	char *data = "Hello word!";
	LCD_PutString(0, 0, data, Red, Black);
	
  while (1)
  {
		
  }
}
