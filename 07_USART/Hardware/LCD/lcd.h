/***
  ******************************************************************************
  * @file    lcd.h
  * @author  magic.liu
  * @version V0.1
  * @date    26-Oct-2022
  * @brief   This file provides the head file for lcd.c.
  ******************************************************************************
  * @attention
**/
#ifndef _LCD_H
#define _LCD_H

#include "stm32f10x.h"

#define LCD_PORT GPIOA
#define LCD_Pin GPIO_Pin_2 //PA2- TIM2 CH3

void LCD_PWM_Init(uint16_t period, uint16_t prescaler, uint8_t duty_circle);

#endif
