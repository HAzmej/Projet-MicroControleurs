#include "Driver_ADC.h"



void MyADC_Init ( ADC_TypeDef * ADC , int channel) 
{	//CONFIG
	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
			
	} else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN ; 
	}
	//ADC Prescaler PCLK2 /prescaler
	RCC->CFGR |=~(3<<13);
	RCC->CFGR|=RCC_CFGR_ADCPRE_DIV6;
	
	//ADC ON/OFF juste activation
	ADC->CR2|=ADC_CR2_ADON;  
	
	//fixer le nombre de conversion : 1 
	ADC->SQR1&= ADC_SQR1_L;
	//Liaison channel
	ADC->SQR3|= channel;
	//CaLibrer
	ADC->CR2|=ADC_CR2_CAL;
	
	while (ADC->CR2 & ADC_CR2_CAL) {}
	
} 

float MyADC_Read ( ADC_TypeDef * ADC )
{ 
	ADC->CR2|=ADC_CR2_ADON; //ADC_CR2_EXTSEL|= ; ADC->CR2|=ADC_CR2_SWSTART
	
	return ADC->DR;

}
