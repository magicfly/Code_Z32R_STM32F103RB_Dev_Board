#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

void delay(int count){
	/***@brief delay function based on a count number
	@param [in] count a number to count down
	***/
	int i = count;
	while(i>0)
	{
		i--;
	}
}

int main(void){
	/***@brief main function***/
	LED_Init();
	
  while (1)
  {
		GPIO_ResetBits(LED1_PORT, LED1_PIN);
		delay_s(1);
		GPIO_SetBits(LED1_PORT, LED1_PIN);
		delay_s(1);
  }
}
