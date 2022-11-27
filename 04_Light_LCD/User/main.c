#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "lcd.h"

#define DEBOUNCE_MS 20

int main(void){
	/***@brief main function***/
	LED_Init();
	Key_PB3_Init();
	LCD_PWM_Init(100, 0, 50);

  while (1)
  {
		if(!GPIO_ReadInputDataBit(KEY_PB3_PORT, KEY_PB3_Pin)){
			delay_ms(DEBOUNCE_MS);
			if(!GPIO_ReadInputDataBit(KEY_PB3_PORT, KEY_PB3_Pin)){
				GPIO_SetBits(LED1_PORT, LED1_PIN);
				while(!GPIO_ReadInputDataBit(KEY_PB3_PORT, KEY_PB3_Pin));
				GPIO_ResetBits(LED1_PORT, LED1_PIN);
			}
		}
  }
}
