#include "stm32f10x.h"
#include "led.h"

#define APB2_IOPBEN 0x00000008
#define LED_PORT GPIOB
#define LED_CR_MASK 0xff0fffff
#define LED1_Pin 5
#define LED1_Setting 0x01

void delay(int count){
	//@brief dealy some time via counting
	int i = count;
	while(i>0)
	{
		i--;
	}
}

int main(void){
	//@brief main function
	RCC->APB2ENR = RCC->APB2ENR | APB2_IOPBEN; //endbale clock of GPIOB in APB2
	LED_PORT->CRL = (GPIOB->CRL & LED_CR_MASK) | (LED1_Setting<<(4 * LED1_Pin));
  while (1){
		LED_PORT->ODR = LED_PORT->ODR | (1<<LED1_Pin);
		delay(6000000);
		LED_PORT->ODR = LED_PORT->ODR & (~ (1<<LED1_Pin));
		delay(6000000);
  }
}
