/***
  ******************************************************************************
  * @file    delay.c
  * @author  magic.liu
  * @version V0.1
  * @date    26-Nvo-2022
  * @brief   This file provides function to delay a time.
  ******************************************************************************
  * @attention
**/

#include "delay.h"

#define CLOCKSOURCE_DIVIDED


void Config_SysTick_Clock_Divided(FunctionalState State){
	/***@brief set clock source type of SysTick
	@param [in] State the state if divide the HCLK by 8
	***/
	if (State == ENABLE){
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	}else{
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	}
}

#ifdef CLOCKSOURCE_DIVIDED
	#define CLOCKSOURCE_MUL 9

	void delay_us(uint32_t time_us){
		/***@brief using SysTick to delay times in us
		@param [in] time_us time to be delay in us
		***/
		SysTick->LOAD = CLOCKSOURCE_MUL * time_us;
		SysTick->VAL = 0x00;
		SysTick->CTRL = 0x01;
		uint32_t temp;
		do{
			 temp = SysTick->CTRL;
		}while((temp & 0x01) && !(temp & (1 << 16)));
		SysTick->CTRL = 0x00;
		SysTick->VAL = 0x00;
	}

#else
	#define CLOCKSOURCE_MUL 72
	
		void delay_us(uint32_t time_us){
		/***@brief using SysTick to delay times in us
		@param [in] time_us time to be delay in us
		***/
		SysTick->LOAD = CLOCKSOURCE_MUL * time_us;
		SysTick->VAL = 0x00;
		SysTick->CTRL = 0x05;
		uint32_t temp;
		do{
			 temp = SysTick->CTRL;
		}while((temp & 0x01) && !(temp & (1 << 16)));
		SysTick->CTRL = 0x04;
		SysTick->VAL = 0x00;
	}
#endif


void delay_ms(uint32_t time_ms){
	/***@brief using SysTick to delay times in ms
	@param [in] time_ms ime to be delay in ms
	***/
	while(time_ms--) delay_us(1000);
}

void delay_s(uint32_t time_s){
	/***@brief using SysTick to delay times in s
	@param [in] time_s ime to be delay in s
	***/
	while(time_s--) delay_ms(1000);
}
/***
STK_CSR      0xE000E010  --
STK_LOAD     0xE000E014  --
STK_VAL      0xE000E018  --
STK_CALRB    0xE000E01C  --

STK_CSR - control register
	bit 0 - ENABLE, enable systick (0-disable systick; 1-enable systick)
	bit 1 - TICKINT, enable systick interupt (0-disable int; 1-enable int)
	bit 2 - CLKSOURCE, clock source of systick (0-HCLK/8 as clock source; 1-HCLK as clock source)
	bit 16 - COUNTFLAG, systick flag for count (1-indict alreay count to 0, clear after read)
STK_LOAD - reload register
	after systick count to 0 it will reload the value, then count down again
STK_VAL - current value register
	it will return current value of counter while reading, write it will reset the counter and clear the COUNTFLAG
STK_CALRB - clibration value register
	bit 31 - NOREF (1-no external clock 0-with external clock)
	bit 30 - SKEW (1-calibration vlaue is not acurate 1ms, 0- calibration vlaue is acurate 1ms)
***/
