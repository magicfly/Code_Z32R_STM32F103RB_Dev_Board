#include "stm32f10x.h"
#include "led.h"

void delay(int count)
{
	int i = count;
	while(i>0)
	{
		i--;
	}
}

int main(void)
{
	LED_Init();
	
  while (1)
  {
		GPIO_ResetBits(LED1_PORT, LED1_PIN);
		delay(6000000);
		GPIO_SetBits(LED1_PORT, LED1_PIN);
		delay(6000000);
  }
}
