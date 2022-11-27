/***
  ******************************************************************************
  * @file    beeper.c
  * @author  magic.liu
  * @version V0.1
  * @date    26-Nov-2022
  * @brief   This file provides function for beeper operation.
  ******************************************************************************
  * @attention
**/

#include "beeper.h"
#include "delay.h"

void Beeper_Init(void){
	/***@brief initial beeper port and beeper pin***/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(BEEPER_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = BEEPER_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(BEEPER_PORT, &GPIO_InitStructure);	
}

void Beeper_Hz(uint32_t count, uint32_t freq_hz){
	float half_period_us = 0.5 * (1.0 / freq_hz) * 1000 * 1000;
	while(count--){
		GPIO_SetBits(BEEPER_PORT, BEEPER_Pin);
		delay_us((uint32_t) half_period_us);
		GPIO_ResetBits(BEEPER_PORT, BEEPER_Pin);
		delay_us((uint32_t) half_period_us);
	}
	GPIO_ResetBits(BEEPER_PORT, BEEPER_Pin);
}
