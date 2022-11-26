#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"

#define DEBOUNCE_MS 20
int main(void){
	/***@brief main function***/
	LED_Init();
	Key_PB3_Init();
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
