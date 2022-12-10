/***
  ******************************************************************************
  * @file    usart.c
  * @author  magic.liu
  * @version V0.1
  * @date    01-Dec-2022
  * @brief   This file provides the functions for usart port.
  ******************************************************************************
  * @attention
**/

#include "usart.h"
#include "stdio.h"

void USART_COM_Init(uint32_t bandrate){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // Tx side to output push&pull mode
	GPIO_Init(USART1_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	//GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // Rx side floating input
	GPIO_Init(USART1_Port, &GPIO_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = bandrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ClearFlag(USART1, USART_FLAG_RXNE);
	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
	USART_Cmd(USART1, ENABLE);

}

struct __FILE{
    int handle; 
};
FILE __stdout;
 
_sys_exit(int x)
{
    x = x;
}

int fputc(int ch, FILE *p){
 USART_SendData(USART1, (u8)ch);
 while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
 return ch;
}

void Serial_SendByte(uint8_t Byte){
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void USART1_IRQHandler(void)
{
	uint8_t data;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		data = (uint8_t)USART_ReceiveData(USART1);
		printf("%c", data);
	}
	//printf("%c", data);
}
