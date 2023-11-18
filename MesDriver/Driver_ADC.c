#include "Driver_ADC.h"



void MyADC_Init ( ADC_TypeDef * ADC , int channel) 
{	//CONFIG
	if (ADC == ADC1) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
			
	} else if (ADC == ADC2) {
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN ; 
	}
	RCC->CFGR=RCC_CFGR_ADCPRE_ ;
	
	//ADC ON/OFF
	ADC->CR2|=ADC_CR2_ADON ;
	
}

float MyADC_Read ( ADC_TypeDef * ADC )
{
	ADC->DR;

}