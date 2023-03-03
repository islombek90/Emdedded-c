/*
 * 007spi_tx_arduino.c
 *
 *  Created on: 26 мая 2021 г.
 *      Author: Im
 */

#include "STM32F0xxx.h"


void delay(void){

	for(uint32_t i = 0; i < 500000/4; i++);


}





/*
 * PB12    SPI2_NSS    AF0
 * PB13    SPI2_SCK    AF0
 * PB14    SPI2_MISO   AF0
 * PB15    SPI2_MOSI   AF0
 *
 *
 *
 * */




void SPI2_GPIOInits(void){

	GPIO_handler_t  SPIPins;
	SPIPins.pGPOIx = GPIOB;

	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 0;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_PUSHPULL;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_NO ;
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
	GPIO_Init(&SPIPins);


}


void SPI2_inits(void){

	SPI_handler_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;

	SPI2Handle.SPI_Config.SPI_BusConfig = SPI_MODE_FD;
	SPI2Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MASTER;
	SPI2Handle.SPI_Config.SPI_SclkSpeed = SPI_CLKSPEED_DIV8;
	SPI2Handle.SPI_Config.SPI_DFF = SPI_DATA_SIZE8;
	SPI2Handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPI_Config.SPI_SSM = SPI_SMM_DI;  //hardware selection ennabled

	SPI_Init(&SPI2Handle);




}


void GPIO_ButtonInit(void){

	GPIO_handler_t  GPIOBntPres;



			GPIOBntPres.pGPOIx = GPIOC;
			GPIOBntPres.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
			GPIOBntPres.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
			GPIOBntPres.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;

			GPIOBntPres.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_NO;


			GPIO_Init(&GPIOBntPres);



}


int main(void)
{



	SPI2_GPIOInits();
	GPIO_ButtonInit();
	SPI2_inits();

	//SPI_SSIConfig(SPI2,ENABLE);
	/*
	 * making SSOE does NSS output enable.
	 * The NSS pin is automatically managed by the hardware
	 * i.e when SPE = 1, NSS will be pulled to low,
	 * and when SPE = 0, NSS will be high,
	 * */
	SPI_SSOEConfig(SPI2,ENABLE);
while(1){

	char USER_DATA[] = "hello world";


	//wait untill butten gets pressed, when pressed
	while(!GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13)){

		delay();

		//enable SPI peripheral
		SPI_PeripheralControl(SPI2,ENABLE);

		//first send dagta length
		uint8_t dataLen = strlen(USER_DATA);
		SPI_SendData(SPI2, &dataLen, 1);


		SPI_SendData(SPI2, (uint8_t*)USER_DATA, strlen(USER_DATA));
		//check if SPI is not busy
		while(SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG));
		//disable SPI peripheral
		SPI_PeripheralControl(SPI2,DISABLE);


	}


	return 0;



}
}
