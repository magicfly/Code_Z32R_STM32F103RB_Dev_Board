/***
  ******************************************************************************
  * @file    led.c
  * @author  magic.liu
  * @version V0.1
  * @date    26-Oct-2022
  * @brief   This file provides the head file for led.c.
  ******************************************************************************
  * @attention
**/
#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

/*@brief */
#define LED1_PORT      GPIOB
#define LED1_PIN       GPIO_Pin_5
#define LED1_PORT_RCC  RCC_APB2Periph_GPIOB

void LED_Init(void);

#endif
