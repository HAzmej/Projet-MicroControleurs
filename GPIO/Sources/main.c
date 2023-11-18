#include "stm32f10x.h"
#include "Driver_GPIO.h"




int main() {	
	MyGPIO_Init(GPIOA, 5, Out_Ppull);
	MyGPIO_Init(GPIOC, 13, In_Floating);
	
	do {
		if (MyGPIO_Read(GPIOC, 13))
			MyGPIO_Reset(GPIOA, 5);
		else
			MyGPIO_Set(GPIOA, 5);
	} while(1);
}
