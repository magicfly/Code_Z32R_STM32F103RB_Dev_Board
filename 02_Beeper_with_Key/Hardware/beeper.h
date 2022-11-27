/***
  ******************************************************************************
  * @file    beeper.h
  * @author  magic.liu
  * @version V0.1
  * @date    26-Nov-2022
  * @brief   This file provides the head file for beeper.c.
  ******************************************************************************
  * @attention
**/
#ifndef _BEEPER_H
#define _BEEPER_H

#include "stm32f10x.h"

#define BEEPER_PORT GPIOB
#define BEEPER_RCC RCC_APB2Periph_GPIOB
#define BEEPER_Pin GPIO_Pin_0

void Beeper_Init(void);
void Beeper_Hz(uint32_t count, uint32_t freq_hz);

#endif
