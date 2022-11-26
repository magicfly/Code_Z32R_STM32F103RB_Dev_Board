/***
  ******************************************************************************
  * @file    key.c
  * @author  magic.liu
  * @version V0.1
  * @date    26-Nvo-2022
  * @brief   This file provides function to intial key button.
  ******************************************************************************
  * @attention
**/

#include "key.h"

void Key_PB3_Init(void){
	/***@brief inital the port which is connected to key PB3***/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(KEY_PB3_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY_PB3_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(KEY_PB3_PORT, &GPIO_InitStructure);
}

void Key_PB2_Init(void){
	/***@brief inital the port which is connected to key PB2***/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(KEY_PB2_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = KEY_PB2_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(KEY_PB2_PORT, &GPIO_InitStructure);
}
