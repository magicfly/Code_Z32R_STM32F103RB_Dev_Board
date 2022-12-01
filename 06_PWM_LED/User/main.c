#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "pwm.h"
#include "key.h"

#define DEBOUNCE_MS 20
int main(void){
	/***@brief main function***/
	PWM_Init();
	uint8_t DIR_FLAG = 1;
	uint16_t count = 0;
  while (1)
  {
		if(DIR_FLAG == 1){
			count += 1;
			
			if (count >= 899){
				DIR_FLAG = 0;
			}
		} else {
			count -= 1;
			if(count <= 0){
				DIR_FLAG = 1;
			}
		}
		TIM_SetCompare2(TIM3, count);
		delay_ms(5);
  }
}
