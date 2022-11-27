/***
  ******************************************************************************
  * @file    key.h
  * @author  magic.liu
  * @version V0.1
  * @date    26-Oct-2022
  * @brief   This file provides the head file for key.c.
  ******************************************************************************
  * @attention
**/
#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"

#define KEY_PB3_PORT GPIOA
#define KEY_PB3_RCC RCC_APB2Periph_GPIOA
#define KEY_PB3_Pin GPIO_Pin_0
#define KEY_PB2_PORT GPIOC
#define KEY_PB2_RCC RCC_APB2Periph_GPIOC
#define KEY_PB2_Pin GPIO_Pin_13

void Key_PB3_Init(void);
void Key_PB2_Init(void);

#endif
