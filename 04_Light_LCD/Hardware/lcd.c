/***
  ******************************************************************************
  * @file    lcd.c
  * @author  magic.liu
  * @version V0.1
  * @date    26-Oct-2022
  * @brief   This file provides the LCD functions.
  ******************************************************************************
  * @attention
**/
#include "lcd.h"

void LCD_PWM_Init(uint16_t period, uint16_t prescaler, uint8_t duty_circle){
	/***@brief inital PWM of back LED in LCD and TIM2
	@param [in] period Timer period
	@param [in] prescalwer Timer prescaler
	@param [in] duty_circle duty circle of PWM output
	***/
	//init system clock for TIM2 and GPIOA
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//init PWM output pin to AF_PP
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = LCD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_PORT, &GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 /*CH3*/
	float pulse = duty_circle / 100.0 * period;
  TIM_OCInitStructure.TIM_Pulse = (uint16_t) pulse;
	
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	//TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}
