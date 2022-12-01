#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "external_int.h"
#include "key.h"

#define DEBOUNCE_MS 20
int main(void){
	/***@brief main function***/
	LED_Init();
	Key_PB3_Init();
	Key_PB2_Init();
	ExtInt_Init();
  while (1)
  {
		if(!GPIO_ReadInputDataBit(KEY_PB2_PORT, KEY_PB2_Pin)){
			delay_ms(DEBOUNCE_MS);
			if(!GPIO_ReadInputDataBit(KEY_PB2_PORT, KEY_PB2_Pin)){
				GPIO_SetBits(LED1_PORT, LED1_PIN);
				while(!GPIO_ReadInputDataBit(KEY_PB2_PORT, KEY_PB2_Pin));
				GPIO_ResetBits(LED1_PORT, LED1_PIN);
			}
		}
  }
}
