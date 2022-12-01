/***
  ******************************************************************************
  * @file    external_int.h
  * @author  magic.liu
  * @version V0.1
  * @date    26-Oct-2022
  * @brief   This file provides the head file for external_int.c.
  ******************************************************************************
  * @attention
**/
#ifndef _EXTERNAL_INT_H
#define _EXTERNAL_INT_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define KEY_PB3_PORT GPIOA
#define KEY_EXTI_PortSource GPIO_PortSourceGPIOA
#define KEY_PB3_RCC RCC_APB2Periph_GPIOA
#define KEY_PB3_Pin GPIO_Pin_0
#define KEY_EXTI_PinSource GPIO_PinSource0


void ExtInt_Init(void);

#endif
