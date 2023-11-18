#include "stm32f10x.h"
#include "Driver_TIMER.h"
#include "Driver_GPIO.h"
#include "Driver_ADC.h"


void Callback(void) {
	MyGPIO_Toggle(GPIOA, 5);
}

int main() {
	//MyGPIO_Struct_TypeDef GPIOA5_Struct = { GPIOA , 5 , Out_Ppull}; //Led
	
	MyTimer_Base_Init(TIM2, 1000-1, 36000-1);
	MyTimer_ActiveIT( TIM2 ,0,Callback);
	MyTimer_Base_Start(TIM2);	
	MyGPIO_Init(GPIOA,5,Out_Ppull);
	MyTimer_PWM(TIM2, 2);
	MyTimer_PWM_Cycle(TIM2,2, 5);
	
	MyADC_Init(ADC1,2);
	
	while(1);
}
