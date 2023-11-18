#define MYADC_H
#include "stm32f10x.h"

void MyADC_Init ( ADC_TypeDef * ADC , int channel);
float MyADC_Read ( ADC_TypeDef * ADC );
