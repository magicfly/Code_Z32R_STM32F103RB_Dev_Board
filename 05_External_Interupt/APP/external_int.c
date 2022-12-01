/***
  ******************************************************************************
  * @file    external_int.c
  * @author  magic.liu
  * @version V0.1
  * @date    28-Nov-2022
  * @brief   This file provides the external interupt functions.
  ******************************************************************************
  * @attention
**/

#include "external_int.h"

void ExtInt_Init(void){
	/***@brief inital the Pin of PB3 as external interrupt source***/
	//Initial GPIO Pin
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(KEY_PB3_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = KEY_PB3_Pin;
	GPIO_Init(KEY_PB3_PORT, &GPIO_InitStructure);
	//initial external interrupt line
	GPIO_EXTILineConfig(KEY_EXTI_PortSource, KEY_EXTI_PinSource);
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	//initial external interrupt request channel and priprity
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
