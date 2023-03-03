/*
 * 016uart_case.c
 *
 *  Created on: 19 сент. 2021 г.
 *      Author: Im
 */


/*
 * uart_tx.c
 *
 *  Created on: Jan 22, 2019
 *      Author: admin
 */

#include<stdio.h>
#include<string.h>
#include "STM32F0xxx.h"



//we have 3 different messages that we transmit to arduino
//you can by all means add more messages
char *msg[3] = {"hihihihihihi123", "Hello How are you ?" , "Today is Monday !"};

//reply from arduino will be stored here
char rx_buf[1024] ;

USART_handler_t usart1_handle;


//This flag indicates reception completion
uint8_t rxCmplt = RESET;

uint8_t g_data = 0;

extern void initialise_monitor_handles();

void USART1_Init(void)
{
	usart1_handle.pUSARTx = USART1;
	usart1_handle.USART_Config.USART_BaudRate = USART_STD_BAUD_115200;
	usart1_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart1_handle.USART_Config.USART_Mode = USART_MODE_TXRX;
	usart1_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	usart1_handle.USART_Config.USART_StopBitMode = USART_STOPBITS_1;
	usart1_handle.USART_Config.USART_WordLength = USART_WORD_LENGTH_8;
	USART_Init(&usart1_handle);
}

void USART1_GPIOInit(void)
{
	GPIO_handler_t UART1;
	UART1.pGPOIx = GPIOA;
	UART1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
	UART1.GPIO_PinConfig.GPIO_PinAltFunMode = 1;
	UART1.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_PUSHPULL;
	UART1.GPIO_PinConfig.GPIO_PinPuPdControl =GPIO_PIN_PUSHPULL_PU;
	UART1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_MED;

		//TX  PA9 UART1TX
	UART1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&UART1);


		//RX PA10 UART1RX
	UART1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	GPIO_Init(&UART1);


}

void GPIO_ButtonInit(void)
{
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

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}
int main(void)
{
	uint32_t cnt = 0;


	initialise_monitor_handles();
	GPIO_ButtonInit();
	USART1_GPIOInit();
    USART1_Init();

    USART_IRQInterruptConfig(IRQ_NO_USART1,ENABLE);

    USART_PeripheralControl(USART1,ENABLE);

    printf("Application is running\n");

    //do forever
    while(1)
    {
		//wait till button is pressed
    		while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){}

		//to avoid button de-bouncing related issues 200ms of delay
    		delay();

		// Next message index ; make sure that cnt value doesn't cross 2
    		cnt = cnt % 3;

		//First lets enable the reception in interrupt mode
		//this code enables the receive interrupt
    		while (USART_ReceiveDataIT(&usart1_handle,(uint8_t*)rx_buf,strlen(msg[cnt])) != USART_READY );
    		delay();
		//Send the msg indexed by cnt in blocking mode
		USART_SendData(&usart1_handle,(uint8_t*)msg[cnt],strlen(msg[cnt]));
		delay();

		printf("Transmitted : %s\n",msg[cnt]);


    	//Now lets wait until all the bytes are received from the arduino .
    	//When all the bytes are received rxCmplt will be SET in application callback
		//while(rxCmplt != SET);

    	//just make sure that last byte should be null otherwise %s fails while printing
		rx_buf[strlen(msg[cnt])+ 1] = '\0';

    	//Print what we received from the arduino
		printf("Received    : %s\n",rx_buf);

    	//invalidate the flag
		rxCmplt = RESET;

    	//move on to next message indexed in msg[]
		cnt ++;
    }


	return 0;
}


void USART2_IRQHandler(void)
{
	USART_IRQHandling(&usart1_handle);
}





void USART_ApplicationEventCallback( USART_handler_t *pUSARTHandle,uint8_t ApEv)
{
   if(ApEv == USART_EVENT_RX_CMPLT)
   {
			rxCmplt = SET;

   }else if (ApEv == USART_EVENT_TX_CMPLT)
   {
	   ;
   }
}
