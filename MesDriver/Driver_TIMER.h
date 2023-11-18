#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

//TIM2_IRQHandler
typedef struct{
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;


void MyTimer_Base_Init (TIM_TypeDef * TIM, uint16_t ARR, uint16_t PSC);
void MyTimer_ActiveIT(TIM_TypeDef * TIM , char Prio, void (*IT_function) (void));
void MyTimer_PWM( TIM_TypeDef * TIM, char Channel) ;
void MyTimer_PWM_Cycle(TIM_TypeDef * Timer, char channel ,float percent);

#define MyTimer_Base_Start(TIM) TIM->CR1 |= TIM_CR1_CEN
#define MyTimer_Base_Stop(TIM) TIM->CR1 &= ~TIM_CR1_CEN

#endif
