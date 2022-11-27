#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "beeper.h"

#define DEBOUNCE_MS 20

int main(void){
	/***@brief main function***/
	LED_Init();
	Key_PB3_Init();
	Key_PB2_Init();
	Beeper_Init();
	
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
		
		if(!GPIO_ReadInputDataBit(KEY_PB2_PORT, KEY_PB2_Pin)){
			delay_ms(DEBOUNCE_MS);
			if(!GPIO_ReadInputDataBit(KEY_PB2_PORT, KEY_PB2_Pin)){
				Beeper_Hz(200, 1000);
				while(!GPIO_ReadInputDataBit(KEY_PB2_PORT, KEY_PB2_Pin));
				Beeper_Hz(500, 5000);
			}
		}
  }
}
