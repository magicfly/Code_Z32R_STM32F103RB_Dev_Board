/***
  ******************************************************************************
  * @file    pwm.c
  * @author  magic.liu
  * @version V0.1
  * @date    01-Dec-2022
  * @brief   This file provides the PWM initial functions.
  ******************************************************************************
  * @attention
**/
#include "pwm.h"

void PWM_Init(void){
	//initial GPIO
	RCC_APB2PeriphClockCmd(PWM_PORT_RCC | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(PWM_PORT, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_Base_InitStructure;
	TIM_Base_InitStructure.TIM_ClockDivision = 0;
	TIM_Base_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Base_InitStructure.TIM_Period = 900 - 1;
	TIM_Base_InitStructure.TIM_Prescaler = 0;
	
	TIM_TimeBaseInit(TIM3, &TIM_Base_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); // remap PB5 to TIM3_CH2 
	
	TIM_OCInitTypeDef TIM_OC_InitStructure;
	TIM_OC_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC_InitStructure.TIM_OutputState = TIM_OutputState_Enable;

	TIM_OC2Init(TIM3, &TIM_OC_InitStructure);
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE);
}
