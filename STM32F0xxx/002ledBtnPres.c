#include "STM32F0xxx.h"
#include "stm32F0xxx_GPIO_Driver.h"


void delay(void){

	for(uint32_t i = 0; i < 500000/4; i++);


}

#define LOW 0
#define ButtonPressed  LOW


int main(void){

	GPIO_handler_t GPIOLed, GPIOBntPres;

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
	GPIOBntPres.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;

	GPIOBntPres.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_NO;

		GPIO_PeriClkControl(GPIOC, ENABLE);
		GPIO_Init(&GPIOBntPres);

	while(1){

		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));

		ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
		delay();


	}








}
