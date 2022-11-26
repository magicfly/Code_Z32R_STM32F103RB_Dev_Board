/***
  ******************************************************************************
  * @file    delay.h
  * @author  magic.liu
  * @version V0.1
  * @date    26-Nvo-2022
  * @brief   This file provides the head info for delay.c.
  ******************************************************************************
  * @attention
**/
#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void delay_us(uint32_t time_us);
void delay_ms(uint32_t time_ms);
void delay_s(uint32_t time_s);

#endif
