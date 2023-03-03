/*
 * 006SPI_TX_testing.c
 *
 *  Created on: 17 мая 2021 г.
 *      Author: Im
 */


/*
 * PB12    SPI2_NSS    AF0
 * PB13    SPI2_SCK    AF0
 * PB14    SPI2_MISO   AF0
 * PB15    SPI2_MOSI   AF0
 *
 *
 *
 * */

#include "STM32F0xxx.h"
#include "string.h"


void SPI2_GPIOInits(void){

	GPIO_handler_t  SPIPins;
	SPIPins.pGPOIx = GPIOB;

	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 0;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_PUSHPULL;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PUSHPULL_NO ;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_HI;

	//configure NSS
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	//GPIO_Init(&SPIPins);

	//configure SCK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//configure MISO
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//GPIO_Init(&SPIPins);

	//configure mosi
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);


}


void SPI2_inits(void){

	SPI_handler_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;

	SPI2Handle.SPI_Config.SPI_BusConfig = SPI_MODE_FD;
	SPI2Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MASTER;
	SPI2Handle.SPI_Config.SPI_SclkSpeed = SPI_CLKSPEED_DIV2;
	SPI2Handle.SPI_Config.SPI_DFF = SPI_DATA_SIZE8;
	SPI2Handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPI_Config.SPI_SSM = SPI_SMM_EN;

	SPI_Init(&SPI2Handle);




}


int main(void)
{

	SPI2_GPIOInits();
	SPI2_inits();
	SPI_SSIConfig(SPI2,ENABLE);
	SPI_PeripheralControl(SPI2,ENABLE);

	char USER_DATA[] = "hello world";
	SPI_SendData(SPI2, (uint8_t*)USER_DATA, strlen(USER_DATA));
	SPI_PeripheralControl(SPI2,DISABLE);
	while(1);


	return 0;



}
