/*
 * 0015_uart_tx_mode_testing.c
 *
 *  Created on: Aug 17, 2021
 *      Author: Im
 */



#include "STM32F0xxx.h"


void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}



void GPIO_ButtonInit(void){

	GPIO_handler_t  GPIOBntPres, GPIOLed;



	GPIOBntPres.pGPOIx = GPIOC;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_PU;
	GPIO_Init(&GPIOBntPres);




	GPIOLed.pGPOIx = GPIOA;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;
	GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_PUSHPULL;
	GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_NO;


	GPIO_Init(&GPIOLed);
}

USART_handler_t UART1Inits;

void UART_Init(void){



	UART1Inits.pUSARTx = USART1;
	UART1Inits.USART_Config.USART_BaudRate = USART_STD_BAUD_115200;
	UART1Inits.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	UART1Inits.USART_Config.USART_Mode = USART_MODE_TXRX;
	UART1Inits.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	UART1Inits.USART_Config.USART_StopBitMode = USART_STOPBITS_1;
	UART1Inits.USART_Config.USART_WordLength = USART_WORD_LENGTH_8;

	USART_Init(&UART1Inits);
}

void UART_GPIOInits(void){

	GPIO_handler_t UART1;
	UART1.pGPOIx = GPIOA;

	UART1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
	UART1.GPIO_PinConfig.GPIO_PinAltFunMode = 1;
	UART1.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_PUSHPULL;
	UART1.GPIO_PinConfig.GPIO_PinPuPdControl =GPIO_PIN_PUSHPULL_NO;
	UART1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_MED;

	//TX  PA9 UART1TX
	UART1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&UART1);


	//RX PA10 UART1RX
	UART1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	GPIO_Init(&UART1);

}

int main(void){


	char msg[1024] = "UART Tx testing...\n\r";
	GPIO_ButtonInit();
	UART_GPIOInits();
	UART_Init();
	USART_PeripheralControl(USART1,ENABLE);
	while(1){

		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));

		delay();

		ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
		delay();

		USART_SendData(&UART1Inits, (uint8_t*)msg, strlen(msg));

	}

	return 0;



}



