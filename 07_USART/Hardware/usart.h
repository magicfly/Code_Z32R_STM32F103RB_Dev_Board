/***
  ******************************************************************************
  * @file    usart.h
  * @author  magic.liu
  * @version V0.1
  * @date    01-Dec-2022
  * @brief   This file provides the head file for usart.c.
  ******************************************************************************
  * @attention
**/
#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"

#define USART1_Port GPIOA
#define USART1_TX_Pin GPIO_Pin_9
#define USART1_RX_Pin GPIO_Pin_10

void USART_COM_Init(uint32_t bandrate);
void Serial_SendByte(uint8_t Byte);

#endif
