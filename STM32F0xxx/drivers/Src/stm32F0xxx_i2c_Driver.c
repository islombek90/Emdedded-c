/*
 * stm32F0xxx_i2c_Driver.c
 *
 *  Created on: 24 июн. 2021 г.
 *      Author: Im
 */
#include "stm32F0xxx_i2c_Driver.h"








/*****************************************************************
 * @fn             -  I2C _PeriClkControl
 *
 * @brief          - This function enables or disables the I2C  clock
 *
 * @parama[in]     - the base address of GPIO port peripheral
 * @parama[in]     - The macros of Enable or Disable
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/




void I2C_PeriClkControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDI)
{
	if (EnorDI == ENABLE)
	{
		if( pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}
		else if ( pI2Cx == I2C2)
		{
			I2C2_PCLK_EN();
		}


	}
	else
		if( pI2Cx == I2C1)
				{
					I2C1_PCLK_DI();
				}
				else if ( pI2Cx == I2C2)
				{
					I2C2_PCLK_DI();
				}
}//end of I2C PeriCLKControl funtion


/*****************************************************************
 * @fn             -  I2C_PeripheralControl
 *
 * @brief          - This function enables or disables the I2C  peripheral
 *
 * @parama[in]     - the base address of GPIO port peripheral
 * @parama[in]     - The macros of Enable or Disable
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/


//enable and disable I2C peripheral
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDI)
{

	if(EnorDI == ENABLE)
			{
		pI2Cx->I2C_CR1 |= (1 << I2C_CR1_PE);



			}
	else{

		pI2Cx->I2C_CR1 &=~ (1 << I2C_CR1_PE);
	}

}//end of function


/*****************************************************************
 * @fn             -  I2C_Init
 *
 * @brief          - This function inits I2C  peripheral
 *
 * @parama[in]     - the base address of GPIO port peripheral
 * @parama[in]     - The macros of Enable or Disable
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/
void I2C_Init(I2C_Handle_t *pI2CHandler)
{
	I2C_PeriClkControl(pI2CHandler->pI2Cx, ENABLE);
	//uint32_t tempreg;
	/* (1) Timing register value is computed with the AN4235 xls file,
	fast Mode @400kHz with I2CCLK = 48MHz, rise time = 140ns,
	fall time = 40ns */
	/* (2) Periph enable */
	/* (3) Slave address = 0x5A, write transfer, 1 byte to transmit, autoend */
	//I2C2->TIMINGR = (uint32_t)0x00B01A4B; /* (1) */
	//I2C2->CR1 = I2C_CR1_PE; /* (2) */
	//I2C2->CR2 = I2C_CR2_AUTOEND | (1 << 16) | (I2C1_OWN_ADDRESS << 1); /* (3) */


	if(pI2CHandler->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_FM4k){
	pI2CHandler->pI2Cx->I2C_TIMINGR = (uint32_t)0x0010020A; //Fastmode 400 khz 8MHZ clck src, 140ns rise time 40 ns fall time
	}
	else if(pI2CHandler->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_FM2k) {
	pI2CHandler->pI2Cx->I2C_TIMINGR = (uint32_t)0x0010031D; // fastmode 200khz 8MHZ clck src, 140ns rise time 40 ns fall time
	}
	else if(pI2CHandler->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_SM) {
	pI2CHandler->pI2Cx->I2C_TIMINGR = (uint32_t)0x00901D23; //standard mode 100khz 8MHZ clck src, 140ns rise time 40 ns fall time
	}

	//Peri eneble
	//I2C2->CR1 = I2C_CR1_PE;



	//program the device own address
		//tempreg = 0;
		//tempreg |= pI2CHandler->I2C_Config.I2C_SlaveDeviceAddress << 1;

		//pI2CHandler->pI2Cx->I2C_CR2 = tempreg;


		pI2CHandler->pI2Cx->I2C_CR2 |=(0x68 << 1);


}//end of function

/*****************************************************************
 * @fn             -  I2C_DeInit
 *
 * @brief          - This function rests the I2C  peripheral
 *
 * @parama[in]     - the base address of GPIO port peripheral
 * @parama[in]     - The macros of Enable or Disable
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/


//enable and disable I2C peripheral
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
		if( pI2Cx == I2C1)
					{
			I2C1_RESET();
					}
		else if( pI2Cx == I2C2)
					{
			I2C2_RESET();
					}
}//end of function


/*****************************************************************
 * @fn             -  I2C_MasterSendData
 *
 * @brief          - This function transmit data in mastermode
 *
 * @parama[in]     - the base address of GPIO port peripheral
 * @parama[in]     - The macros of Enable or Disable
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/


void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer, uint32_t Len)
{


	pI2CHandle->pI2Cx->I2C_CR2 |=(0x1 << 16); //1 byte data transfer
	//pI2CHandle->pI2Cx->I2C_CR2 |=(1 << I2C_CR2_AUTOEND);
	pI2CHandle->pI2Cx->I2C_CR2 &=~(1 << I2C_CR2_AUTOEND);
	pI2CHandle->pI2Cx->I2C_CR2 &=~ (1<<I2C_CR2_RD_WRN);
	I2C_PeripheralControl(pI2CHandle->pI2Cx, ENABLE);
		/* Check Tx empty
		if ((I2C2->ISR & I2C_ISR_TXE) == I2C_ISR_TXE)
		{
		I2C2->TXDR = I2C_BYTE_TO_SEND;  Byte to send
		I2C2->CR2 |= I2C_CR2_START;  Go */



	while(Len > 0){

		if((pI2CHandle->pI2Cx->I2C_ISR & I2C_ISR_TXE) == I2C_ISR_TXE )//Wait till TXE is set
		{
			pI2CHandle->pI2Cx->I2C_TXDR = *pTxbuffer;
			pI2CHandle->pI2Cx->I2C_CR2 |= (1<<I2C_CR2_START);
			pTxbuffer++;
			Len--;
		}


	}

	//pI2CHandle->pI2Cx->I2C_CR2 |= (1<<I2C_CR2_STOP);






}

/*****************************************************************
 * @fn             -  I2C_MasterRecieveData
 *
 * @brief          - This function recieves data in mastermode
 *
 * @parama[in]     - the base address of I2c port peripheral
 * @parama[in]     - buffer for data save
 * @parama[in]     - length of buffer
 *
 * @return         -None
 *
 * @note           -None
*/

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxbuffer,uint32_t Len)
{
	/* (1) Timing register value is computed with the AN4235 xls file,
	fast Mode @400kHz with I2CCLK = 48MHz, rise time = 140ns,
	fall time = 40ns */
	/* (2) Periph enable, receive interrupt enable */
	/* (3) Slave address = 0x5A, read transfer, 1 byte to receive, autoend */
	//I2C2->TIMINGR = (uint32_t)0x00B01A4B; /* (1) */
	//I2C2->CR1 = I2C_CR1_PE | I2C_CR1_RXIE; /* (2) */
	//I2C2->CR2 = I2C_CR2_AUTOEND | (1<<16) | I2C_CR2_RD_WRN
	//| (I2C1_OWN_ADDRESS << 1); /* (3) */


	pI2CHandle->pI2Cx->I2C_CR2 |=(1 << 16); //1 byte data transfer
	pI2CHandle->pI2Cx->I2C_CR2 |=(1 << I2C_CR2_AUTOEND);
	//pI2CHandle->pI2Cx->I2C_CR2 &=~(1 << I2C_CR2_AUTOEND);
	pI2CHandle->pI2Cx->I2C_CR1 |= (1<<I2C_CR1_RXIE);
	pI2CHandle->pI2Cx->I2C_CR2 |= (1<<I2C_CR2_RD_WRN);
	I2C_PeripheralControl(pI2CHandle->pI2Cx, ENABLE);

	if (((pI2CHandle->pI2Cx->I2C_ISR & I2C_ISR_RXNE) == I2C_ISR_RXNE))
	{
	/* Read receive register, will clear RXNE flag */
		 *pRxbuffer=pI2CHandle->pI2Cx->I2C_RXDR;
	}





}

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
	if(pI2Cx->I2C_ISR & FlagName)
{

		return FLAG_SET;
}
	return FLAG_RESET;
}//end of function



//Application Callback
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv);



void I2C_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
