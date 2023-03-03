#include<string.h>
#include "STM32F0xxx.h"



void delay(void){

	for(uint32_t i = 0; i < 500000/4; i++);


}

#define LOW 0
#define ButtonPressed  LOW


int main(void){

	GPIO_handler_t GPIOLed, GPIOBntPres;
	memset(&GPIOLed, 0, sizeof(GPIOLed));
	memset(&GPIOBntPres, 0, sizeof(GPIOBntPres));


	GPIOLed.pGPOIx = GPIOA;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;
	GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_PUSHPULL;
	GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_NO;

	GPIO_PeriClkControl(GPIOA, ENABLE);
	GPIO_Init(&GPIOLed);


	GPIOBntPres.pGPOIx = GPIOC;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;

	GPIOBntPres.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_PU;

	GPIO_PeriClkControl(GPIOC, ENABLE);

	GPIO_Init(&GPIOBntPres);
	GPIO_IRQPriorityConfig(EXTI4_15, NVIC_PRI13);
	GPIO_IRQInterruptConfig(EXTI4_15,ENABLE);


	while(1){



	}








}


void EXTI4_15_IRQHandler(void){

	delay();
	GPIO_IRQHandler(GPIO_PIN_NO_13);
	ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);


}
