/***
  ******************************************************************************
  * @file    led.c
  * @author  magic.liu
  * @version V0.1
  * @date    26-Oct-2022
  * @brief   This file provides the LED initial functions.
  ******************************************************************************
  * @attention
**/
#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LED1_PORT_RCC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);
	GPIO_SetBits(LED1_PORT, LED1_PIN);
}
