/***
  ******************************************************************************
  * @file    pwm.h
  * @author  magic.liu
  * @version V0.1
  * @date    01-Dec-2022
  * @brief   This file provides the head file for led.c.
  ******************************************************************************
  * @attention
**/
#ifndef _PWM_H
#define _PWM_H

#include "stm32f10x.h"

#define PWM_PORT      GPIOB
#define PWM_PIN       GPIO_Pin_5
#define PWM_PORT_RCC  RCC_APB2Periph_GPIOB

void PWM_Init(void);

#endif
