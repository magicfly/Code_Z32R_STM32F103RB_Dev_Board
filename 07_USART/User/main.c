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
	//USART_COM_Init(115200);
	//LCD_PWM_Init(100, 0 ,80);
	//LCD_GPIO_Init();
	//LCD_Init();
	//LCD_Clear_Screen(Black);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Rx side floating input
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_WriteBit(GPIOA, GPIO_Pin_10, (BitAction) 1);
//	GPIO_WriteBit(GPIOA, GPIO_Pin_9, (BitAction) 1);
	
  while (1)
  {
		
		uint8_t data;
		if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET){
			data = USART_ReceiveData(USART1);
			Serial_SendByte(data);
			LCD_PutChar(0, 0, data, Red, Black);
		}
  }
}
