#ifndef __TIMER_H
#define __TIMER_H
#include <sys.h>	 

void Timer1_Init(u16 arr,u16 psc);  
void TIM2_Cap_Init(u16 arr,u16 psc)	;
void Read_Distane(void);
void TIM2_IRQHandler(void);

  
#endif
