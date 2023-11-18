#include "stm32f10x.h"
#include "Driver_TIMER.h"
#include "Driver_GPIO.h"

void ( * callback1)(void);
void ( * callback2)(void);
void ( * callback3)(void);
void ( * callback4)(void);

void MyTimer_Base_Init (TIM_TypeDef * TIM, uint16_t ARR, uint16_t PSC){
	if (TIM == TIM2)
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	else if (TIM == TIM3)
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	else if (TIM == TIM4)
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	TIM->ARR = ARR;
	TIM->PSC = PSC;
}


void TIM1_UP_IRQHandler(void) {
	//on met à 0 le flag d'interruption
	TIM1->SR &= ~1;
	(* callback1) ();
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~1;
	(* callback2) ();
}

void TIM3_IRQHandler(void) {
	TIM3->SR &= ~1;
	(* callback3) ();
}

void TIM4_IRQHandler(void) {
	TIM4->SR &= ~1;
	(* callback4) ();
}

void MyTimer_ActiveIT(TIM_TypeDef * TIM , char Prio , void (*IT_function )(void) ){
	// IRQn_Type TIM_IRQn;
	
	// On met en 1 le bit0 (UIE) du registre DIER
	TIM->DIER |= TIM_DIER_UIE; 
	
	// Configuration du Timer correspondant sur le coeur
	if (TIM == TIM1) {
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		NVIC_SetPriority(TIM1_UP_IRQn,Prio);
		callback1=IT_function; 
	}
	
	else if (TIM == TIM2) {
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, Prio);
		callback2=IT_function; 
	}
	
	else if (TIM == TIM3) {
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, Prio);
		callback3=IT_function; 
	}
	
	else if (TIM == TIM4) {
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, Prio);
		callback4=IT_function; 
	}
	
 
	
	
	
}

void MyTimer_PWM(TIM_TypeDef*TIM ,char Channel ) {
	if (TIM==TIM1) {
			TIM1->BDTR|=1<<15; 
	}		
	switch (Channel) {
		case 1: 
		//on écrit  '110' dans le registre OC1M de TIM_CCMR1
		TIM->CCMR1 &= ~(0x7<<4) ; // TIM->CCMR1 &= ~TIM_CCMR1_OC1M_0; TIM->CCMR1 |= TIM_CCMR1_OC1M_1| TIM_CCMR1_OC1M_2;
		TIM->CCMR1 |= ~(0x6<<4) ; 
		
	
		//Active Preload
		TIM->CCMR1 |= TIM_CCMR1_OC1PE;
		
		TIM->CCER = TIM_CCER_CC1E;
		
		case 2:
		TIM->CCMR1 &= ~(0x7<<4) ;  
		TIM->CCMR1 |= ~(0x6<<4) ; 
		
		//Active Preload
		TIM->CCMR1 |= TIM_CCMR1_OC2PE;
		
		TIM->CCER = TIM_CCER_CC1E;
			break;
		case 3:
		TIM->CCMR2 &= ~(0x7<<4) ; 
		TIM->CCMR2 |= ~(0x6<<4) ; 
		
		//Active Preload
		TIM->CCMR2 |= TIM_CCMR2_OC3PE;
		
		TIM->CCER = TIM_CCER_CC1E;
			break;
		case 4:
		TIM->CCMR2 &= ~(0x7<<4) ; // TIM->CCMR2 &= ~TIM_CCMR2_OC4M_0; TIM->CCMR2 |= TIM_CCMR2_OC4M_1| TIM_CCMR2_OC4M_2;
		TIM->CCMR2 |= ~(0x6<<4) ; 
		
		//Active Preload
		TIM->CCMR2 |= TIM_CCMR2_OC4PE;
		
		TIM->CCER = TIM_CCER_CC1E;
			break;
		
		
		
		
	}
	//on autorise le registre de auto-reload preload en ecrivant 1 dans le registre ARPE de CR1
	TIM -> CR1 |= TIM_CR1_ARPE ;

}
void MyTimer_PWM_Cycle(TIM_TypeDef * TIM, char channel , float percent ){
	switch (channel) {
		case 1 : 
			TIM->CCR1= (int) ((float)(TIM->ARR)*(percent/100.0));
		break;
		case 2 : 
			TIM->CCR2= (int) ((float)(TIM->ARR)*(percent/100.0));
		break;
		case 3 : 
			TIM->CCR3= (int) ((float)(TIM->ARR)*(percent/100.0));
		break;
		case 4 : 
			TIM->CCR4= (int) ((float)(TIM->ARR)*(percent/100.0));
		break;
		
		
	}
}
