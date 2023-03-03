/*
 * 008spi_cmd_handling.c
 *
 *  Created on: 13 июн. 2021 г.
 *      Author: Im
 */



#include  <stdio.h>
#include "STM32F0xxx.h"
#include <string.h>







/*
 * PB12    SPI2_NSS    AF0
 * PB13    SPI2_SCK    AF0
 * PB14    SPI2_MISO   AF0
 * PB15    SPI2_MOSI   AF0
 *
 *
 *
 * */

//command codes
#define COMMAND_LED_CTRL          0x50
#define COMMAND_SENSOR_READ       0x51
#define COMMAND_LED_READ          0x52
#define COMMAND_PRINT           0x53
#define COMMAND_ID_READ         0x54

#define LED_ON     1
#define LED_OFF    0

//arduino analog pins
#define ANALOG_PIN0   0
#define ANALOG_PIN1   1
#define ANALOG_PIN2   2
#define ANALOG_PIN3   3
#define ANALOG_PIN4   4

//Arduino led pin
#define LED_PIN 9

//for semihosting debuggin mode only, system.c should be excluded as well.
extern void initialise_monitor_handles(void);


void delay(void){

	for(uint32_t i = 0; i < 500000/2; i++);  //200ms delay, how?


}


void One_Second_delay(void){

	delay();
	delay();
	delay();
	delay();

}
void SPI1_GPIOInits(void){

	//SPI2 button configurations
	/*GPIO_handler_t  SPIPins;
	SPIPins.pGPOIx = GPIOB;

	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 0;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_PUSHPULL;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_PU ;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;

	//configure NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);

	//configure SCK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//configure MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

	//configure mosi
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);*/

	//SPI 1 configurtaion

		GPIO_handler_t  SPIPins;
		SPIPins.pGPOIx = GPIOA;

		SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
		SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 0;
		SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_PUSHPULL;
		SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_NO ;
		SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;



		//configure SLCK
		SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
		GPIO_Init(&SPIPins);

		//configure MISO
		SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
		GPIO_Init(&SPIPins);

		//configure MOSI
		SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
		GPIO_Init(&SPIPins);

		//configure NSS
		SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;

		GPIO_Init(&SPIPins);


}


void SPI1_inits(void){

	SPI_handler_t SPI1Handle;
	SPI1Handle.pSPIx = SPI1;

	SPI1Handle.SPI_Config.SPI_BusConfig = SPI_MODE_FD;
	SPI1Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MASTER;
	SPI1Handle.SPI_Config.SPI_SclkSpeed = SPI_CLKSPEED_DIV8;
	SPI1Handle.SPI_Config.SPI_DFF = SPI_DATA_SIZE8;
	SPI1Handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI1Handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI1Handle.SPI_Config.SPI_SSM = SPI_SMM_DI;  //hardware selection ennabled

	SPI_Init(&SPI1Handle);




}


void GPIO_ButtonInit(void){

	GPIO_handler_t  GPIOBntPres, GPIOLed;


	// this is btn gpio configurations
	GPIOBntPres.pGPOIx = GPIOC;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBntPres.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;

	GPIOBntPres.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_NO;

		//GPIO_PeriClkControl(GPIOC, ENABLE);

	GPIO_Init(&GPIOBntPres);

	// this is led gpio configurations
	GPIOLed.pGPOIx = GPIOA;
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;
	GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_PUSHPULL;
	GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_NO;

	//GPIO_PeriClkControl(GPIOA, ENABLE);
	GPIO_Init(&GPIOLed);




}

uint8_t SPI_VerifyResponse(uint8_t ackbyte){

	if (ackbyte == (uint8_t)0XF5 ){
		//ack
		return 1;
	}

		//nack
	return 0;



}

int main(void)
{


	uint8_t dymmy_write = 0xff;
	uint8_t dymmy_read ;
	initialise_monitor_handles();
	printf("application is running\n");

	GPIO_ButtonInit();

	//this function ints the GPIO pins as SPI functions
	SPI1_GPIOInits();

	//this funtcion inits the SPI perihperals
	SPI1_inits();

	printf("SPI1 Init. done\n");

	//SPI_SSIConfig(SPI2,ENABLE);
	/*
	 * making SSOE does NSS output enable.
	 * The NSS pin is automatically managed by the hardware
	 * i.e when SPE = 1, NSS will be pulled to low,
	 * and when SPE = 0, NSS will be high,
	 * */
	SPI_SSOEConfig(SPI1,ENABLE);

while(1){




	//wait untill butten gets pressed, when pressed
	//while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));
	delay();
	/*delay();
	ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);*/
	delay();

	//enable SPI peripheral
	SPI_PeripheralControl(SPI1,ENABLE);

	//1. CMD_LED_CTRL <pin no(1)>  <value(1)>

	uint8_t commcncode = COMMAND_LED_CTRL;
	uint8_t ackbyte;
	uint8_t args[2];

	SPI_SendData(SPI1, &commcncode, 1);
	//do dymmy read to clear RXNE
	SPI_RecveiveData(SPI1, &dymmy_read,1);

	// send some dummy bits(1 byte) to fetch the response from the slvae
	SPI_SendData(SPI1, &dymmy_write, 1);

	SPI_RecveiveData(SPI1, &ackbyte,1);

	//if received data is ack  or 1 , if it is true
	if(SPI_VerifyResponse(ackbyte))
	{

		//send arguments
		args[0] = LED_PIN;
		args[1] = LED_ON;

		//send arguments
		SPI_SendData(SPI1, args, 2);

		//dummy read
		SPI_RecveiveData(SPI1, args,2);

		printf("COMMAND_LED_CTRL executed\n");

	}
	//end of COMMAND_LED_CTRL

	//2. CMD_SENSOR READ <analog pin number(1)>

	//wait till button get pressed
	//while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));
	delay();

	//to avoid button debouncing related issues 200ms of delay;
	delay();

	commcncode = COMMAND_SENSOR_READ;


	SPI_SendData(SPI1, &commcncode, 1);
	//do dymmy read to clear RXNE
	SPI_RecveiveData(SPI1, &dymmy_read,1);

	// send some dummy bits(1 byte) to fetch the response from the slvae
	SPI_SendData(SPI1, &dymmy_write, 1);

	//read the ackbyte recieved
	SPI_RecveiveData(SPI1, &ackbyte,1);

	//if received data is ack  or 1 , if it is true
	if(SPI_VerifyResponse(ackbyte))
	{

		//send arguments
		args[0] = ANALOG_PIN0;

		//send arguments
		SPI_SendData(SPI1, args, 2);





		// do dummy read to clear RXNE
		SPI_RecveiveData(SPI1, &ackbyte,1);

		// inser delay for adc of slave be ready with data
		delay();

		// send dummy to fetch analog pin values
		SPI_SendData(SPI1, &dymmy_write, 1);

		// fetch the analog value from arduino
		uint8_t analog_read;
		SPI_RecveiveData(SPI1, &analog_read,1);
		printf("COMMAND_SENSOR_READ %d\n", analog_read);

	}

	//3. COMMAND_LED_READ <pin no> this command returns the led status from slave

	//wait till button get pressed
	//while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));
	delay();

	//to avoid button debouncing related issues 200ms of delay;
	delay();

	commcncode = COMMAND_LED_READ;


	SPI_SendData(SPI1, &commcncode, 1);
	//do dymmy read to clear RXNE
	SPI_RecveiveData(SPI1, &dymmy_read,1);

	// send some dummy bits(1 byte) to fetch the response from the slvae
	SPI_SendData(SPI1, &dymmy_write, 1);

	SPI_RecveiveData(SPI1, &ackbyte,1);

	//if received data is ack  or 1 , if it is true
	if(SPI_VerifyResponse(ackbyte))
	{

		//send arguments
		args[0] = LED_PIN;

		SPI_SendData(SPI1, args, 2);




	// do dummy read to clear RXNE
		SPI_RecveiveData(SPI1, &ackbyte,1);

	// inser delay for adc of slave be ready with data
		delay();

	// send dummy to fetch analog pin values
		SPI_SendData(SPI1, &dymmy_write, 1);

	// fetch the analog value from arduino
		uint8_t pin_status;
		SPI_RecveiveData(SPI1, &pin_status,1);
		printf("COMMAND_READ_LED %d\n", pin_status);

	}

		//4. COMMAND_PRINT   <len > <message>  this command print message on serial port of Arduino slave
		//wait untill butten gets pressed, when pressed

	//while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));
	delay();
	//delay();

	delay();

	//send command
	commcncode = COMMAND_PRINT;

	SPI_SendData(SPI1, &commcncode, 1);
	//do dymmy read to clear RXNE
	SPI_RecveiveData(SPI1, &dymmy_read,1);

	// send some dummy bits(1 byte) to fetch the response from the slvae
	SPI_SendData(SPI1, &dymmy_write, 1);

	SPI_RecveiveData(SPI1, &ackbyte,1);

	uint8_t message[] = "Hello! How are you?";

	//if received data is ack  or 1 , if it is true
	if(SPI_VerifyResponse(ackbyte))
	{

		args[0] = strlen((char*)message);

		SPI_SendData(SPI1, args, 1); //sending the length

		//do dymmy read to clear RXNE
		SPI_RecveiveData(SPI1, &dymmy_read,1);
		delay();

		//send message
		for(int i = 0; i< args[0]; i++){
			SPI_SendData(SPI1,&message[i],1);
			SPI_RecveiveData(SPI1, &dymmy_read,1);


		}

		printf("COMMAND_PRINT Executed \n");
	}



	//5. COMMAND_ID_READ    this returns the ID of Arduino slave which is predefined in Arduino code

	//while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));
	delay();
	delay();

	//send command
	commcncode = COMMAND_ID_READ;

	SPI_SendData(SPI1, &commcncode, 1);
	//do dymmy read to clear RXNE
	SPI_RecveiveData(SPI1, &dymmy_read,1);

	// send some dummy bits(1 byte) to fetch the response from the slvae
	SPI_SendData(SPI1, &dymmy_write, 1);

	SPI_RecveiveData(SPI1, &ackbyte,1);

	uint8_t id[11];
	uint32_t i =0;

	//if received data is ack  or 1 , if it is true
	if(SPI_VerifyResponse(ackbyte))
	{
		for( i= 0; i< 10; i++){
			SPI_SendData(SPI1, &dymmy_write, 1);

			SPI_RecveiveData(SPI1, &id[i],1);

		}

		id[10] = '\0';
		printf("COMMAND_ID: %s\n", id);



	}





		//check if SPI is not busy
	while(SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG));
		//disable SPI peripheral
	SPI_PeripheralControl(SPI2,DISABLE);




}
	return 0;




}
