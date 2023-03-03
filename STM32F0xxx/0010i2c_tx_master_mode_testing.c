/*
 * 0010i2c_tx_master_mode_testing.c
 *
 *  Created on: 29 июн. 2021 г.
 *      Author: Im
 */


#include "STM32F0xxx.h"


#define MY_ADDR 0x61

#define SLAVE_ADDR  0x68

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

I2C_Handle_t I2C1Handle;


/*
 * PB6-> SCL
 * PB9 or PB7 -> SDA
 */


void I2C1_GPIOInits(void){

	GPIO_handler_t I2C1Pins;
	I2C1Pins.pGPOIx =GPIOB;

	I2C1Pins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN;
	I2C1Pins.GPIO_PinConfig.GPIO_PinAltFunMode = 1;
	I2C1Pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_PIN_OUT_OPDRN;
	I2C1Pins.GPIO_PinConfig.GPIO_PinPuPdControl =GPIO_PIN_PUSHPULL_NO;
	I2C1Pins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_PIN_SPEED_MED;

	//SCL
	I2C1Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&I2C1Pins);


	//SDA
	I2C1Pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&I2C1Pins);

}


void I2C1_inits(void){


	I2C1Handle.pI2Cx = I2C1;

	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	//I2C1Handle.I2C_Config.I2C_SlaveDeviceAddress = SLAVE_ADDR;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);





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


int main(void){
	//some data
	uint8_t some_data[] = "hello\n";
	I2C1_GPIOInits();
	I2C1_inits();
	GPIO_ButtonInit();
	while(1){

		//while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13));

		delay();

		I2C_MasterSendData(&I2C1Handle,some_data, strlen((char*)some_data));
	}



}
