/*
 * stm32F0xxx_SPI_Driver.c
 *
 *  Created on: 16 мая 2021 г.
 *      Author: Im
 */
#include "stm32F0xxx_SPI_Driver.h"

//

static void spi_tx_interrupt_hadle(SPI_handler_t *pHandler);
static void spi_rx_interrupt_hadle(SPI_handler_t *pHandler);
static void spi_ovr_interrupt_hadle(SPI_handler_t *pHandler);



uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{

	if(pSPIx->SR & FlagName)
	{

		return FLAG_SET;
	}
	return FLAG_RESET;

/*****************************************************************
 * @fn             -  SPI _PeriClkControl
 *
 * @brief          - This function enables or disables the SPI  clock
 *
 * @parama[in]     - the base address of GPIO port peripheral
 * @parama[in]     - The macros of Enable or Disable
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/




}

void SPI_PeriClkControl(SPI_RegDef_t *pSPIx, uint8_t EnorDI)

{
	if (EnorDI == ENABLE)
	{
		if( pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if ( pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}


	}
	else
		if( pSPIx == SPI1)
				{
					SPI1_PCLK_DI();
				}
				else if ( pSPIx == SPI2)
				{
					SPI2_PCLK_DI();
				}
				}

/*****************************************************************
 * @fn             -  SPI _PeripheralControl
 *
 * @brief          - This function enables or disables the SPI  peripheral
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDI){

	if(EnorDI == ENABLE)
			{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);



			}
	else{

		pSPIx->CR1 &=~ (1 << SPI_CR1_SPE);
	}

}

/*****************************************************************
 * @fn             -  SPI_SSIConfig
 *
 * @brief          - This function configure SSI of SPI
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDI){

	if(EnorDI == ENABLE)
				{
			pSPIx->CR1 |= (1 << SPI_CR1_SSI);



				}
		else{

			pSPIx->CR1 &=~ (1 << SPI_CR1_SSI);
		}

}

/*****************************************************************
 * @fn             -  SPI_SSOEConfig
 *
 * @brief          - This function configure SSOE of SPI
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDI){

	if(EnorDI == ENABLE)
				{
			pSPIx->CR2 |= (1 << SPI_CR2_SSOE);



				}
		else{

			pSPIx->CR2 &=~ (1 << SPI_CR2_SSOE);
		}

}
/*****************************************************************
 * @fn             -  SPI_Init
 *
 * @brief          -
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/




void SPI_Init(SPI_handler_t *pSPIHandler){


//fisrst lets config SPI_CR1 register



	SPI_PeriClkControl(pSPIHandler->pSPIx, ENABLE);
	uint32_t tempregCR1 = 0;
	//uint32_t tempregCR2 = 0;

	//1.  configure device mode
	tempregCR1 |= pSPIHandler->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR ;

	//2. configure bus mode
	if(pSPIHandler->SPI_Config.SPI_BusConfig  == SPI_MODE_FD)
	{
		//bidi mode should be cleared

		tempregCR1 &=~(1 << SPI_CR1_BIDIMODE);

	}
	else if(pSPIHandler->SPI_Config.SPI_BusConfig  == SPI_MODE_HD)
	{
		//bidi mode should be set
		tempregCR1 |= (1 << SPI_CR1_BIDIMODE);
	}
	else if(pSPIHandler->SPI_Config.SPI_BusConfig  == SPI_MODE_SIMPLEX_RECIEVE_ONLY)
	{

		//bidi mode should be cleared
		//rxonly bit bould be set
		tempregCR1 &=~(1<<SPI_CR1_BIDIMODE);
		tempregCR1 |=(1<<SPI_CR1_RXONLY);
	}


	//3. configure DFF

	tempregCR1|= pSPIHandler->SPI_Config.SPI_DFF << SPI_CR1_CRCL;

	//4. configure CPHA
	tempregCR1 |= pSPIHandler->SPI_Config.SPI_CPHA << SPI_CR1_CPHA;

	//5. configure CPOL
	tempregCR1 |= pSPIHandler->SPI_Config.SPI_CPOL << SPI_CR1_CPOL;

	//6. configure SSM
	tempregCR1 |= pSPIHandler->SPI_Config.SPI_SSM << SPI_CR1_SSM;

	//7. configure CLK speed
	tempregCR1 |= pSPIHandler->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR;

	pSPIHandler ->pSPIx ->CR1 = tempregCR1;
	//pSPIHandler ->pSPIx ->CR2 = tempregCR2;


}

/*****************************************************************
 * @fn             -  SPI_DeInit
 *
 * @brief          -
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/



void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

	if( pSPIx == SPI1)
				{
		SPI1_RESET();
				}
	else if( pSPIx == SPI2)
				{
					SPI2_RESET();





}
}

/*****************************************************************
 * @fn             -  SPI_SendData
 *
 * @brief          -
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/


void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTX_Buffer, uint32_t Len)
{


	while(Len > 0){

		//while (!(pSPIx->SR & (1 <<1))); loop will wait until ST gets 1, if SR gets 1 the negation will be zero, which means whille loop will runs 1 time and exit

			while(SPI_GetFlagStatus(pSPIx, SPI_TX_FLAG) == FLAG_RESET);

			if ((pSPIx->CR1 & (1 << SPI_CR1_CRCL)))
				{
					pSPIx->DR  = *((uint16_t*)pTX_Buffer);
					Len--;
					Len--;
					(uint16_t*)pTX_Buffer++;


			}//else if((pSPIx->CR1 & ( 0<< SPI_CR1_CRCL)))
			else
				{

					pSPIx->DR  = *pTX_Buffer;
					Len--;

					pTX_Buffer++;
				}


			}

		}







/*****************************************************************
 * @fn             -  SPI_RecieveData
 *
 * @brief          -
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/

void SPI_RecveiveData(SPI_RegDef_t *pSPIx, uint8_t *pRX_Buffer, uint32_t Len){
/*****************************************************************
 * @fn             -  SPI_RecveiveData
 *
 * @brief          -
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/

while(Len > 0){

	//while (!(pSPIx->SR & (1 <<1))); loop will wait until ST gets 1, if SR gets 1 the negation will be zero, which means whille loop will runs 1 time and exit

		while(SPI_GetFlagStatus(pSPIx, SPI_RX_FLAG) == (uint8_t)FLAG_RESET);

		if (pSPIx->CR1 & (1 << SPI_CR1_CRCL))
			{
				// 16 bit DFF
				 *((uint16_t*)pRX_Buffer) = pSPIx->DR ;
				Len--;
				Len--;
				(uint16_t*)pRX_Buffer++;

			}else
			{
				//8 bit DFF
				*pRX_Buffer = pSPIx->DR ;
				Len--;

				pRX_Buffer++;
			}


		}

	}








/*****************************************************************
 * @fn             -  SPI_IRQInterrupConfig
 *
 * @brief          -
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/

void SPI_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi)
{

if(EnorDi == ENABLE){
		//enabling interrupt

		if(IRQNumber <= 31)
		{
			//set ISER0
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber >31 && IRQNumber<64)
		{
			//set ISER1
			//*NVIC_ISER1 |= (1 << IRQNumber % 32);

		}

		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//set ISER2
			//*NVIC_ISER2 |= (1 << IRQNumber % 64);
		}

	}
	else {

		//disabling interrupt
		if(IRQNumber <= 31)
				{
				  // SET ICER0
				*NVIC_ICER0 |= (1 << IRQNumber);
				}
				else if(IRQNumber >31 && IRQNumber < 64)
				{
				 // SET ICER1
				//	*NVIC_ICER1 |= (1 << IRQNumber %32);

				}

				else if(IRQNumber >= 64 && IRQNumber<96)
				{
					//SET ICER 2
				//	*NVIC_ICER2 |= (1 << IRQNumber % 64);
				}

	}


}

/*****************************************************************
 * @fn             -  SPI_IRQPriority
 *
 * @brief          -
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
*/

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	//1. lets find the ipr register

	uint8_t ipx = IRQNumber /4;
	uint8_t ipx_section = IRQNumber % 4;
	uint8_t shift_amount = (8*ipx_section)+(8-NO_PR_BIRS_IMPLEMENTED);

	*(NVIC_PR_BASEDADDR + (ipx)) |= (IRQPriority << shift_amount);



}


uint8_t SPI_SendDataIT(SPI_handler_t *pSPIHandle, uint8_t *pTX_Buffer, uint32_t Len)
{

	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_TX){

		//1. save tx buffer address and len information in some global variables

		 pSPIHandle ->TxBuffer = pTX_Buffer;
		 pSPIHandle ->TxLen=Len;

		//2. MArk SPI sate as busy
		//so that no other instruction can take over same SPI peripheral
		 pSPIHandle ->TxState =  SPI_BUSY_IN_TX;


		//3. enable TXEIE
		 pSPIHandle->pSPIx->CR2 |= (1<<SPI_CR2_TXEIE);


		//4. transmit via ISR






	}
	return state;

}
uint8_t SPI_RecveiveDataIT(SPI_handler_t *pSPIHandle, uint8_t *pRX_Buffer, uint32_t Len)
{

	uint8_t state = pSPIHandle->RxState;

	if(state != SPI_BUSY_IN_RX){

		//1. save tx buffer address and len information in some global variables

		 pSPIHandle ->RxBuffer = pRX_Buffer;
		 pSPIHandle ->RxLen=Len;

		//2. MArk SPI sate as busy
		//so that no other instruction can take over same SPI peripheral
		 pSPIHandle ->RxState =  SPI_BUSY_IN_RX;


		//3. enable RXNEIE
		 pSPIHandle->pSPIx->CR2 |= (1<<SPI_CR2_RXNEIE);


		//4. transmit via ISR






	}
	return state;



}

void SPI_IRQHandler(SPI_handler_t *pHandler)
{
	uint8_t temp1, temp2;

	//1. lets check for TXE

	temp1= pHandler ->pSPIx->SR & (1 << SPI_SR_TXE);
	temp2= pHandler ->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);

	if (temp1 && temp2){

		//hanlde TXE
		spi_tx_interrupt_hadle(pHandler);


	}


	//2. lets check for RXE


	temp1= pHandler ->pSPIx->SR & (1 << SPI_SR_RXNE);
	temp2= pHandler ->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);

	if (temp1 && temp2){

		//hanlde RXE
		spi_rx_interrupt_hadle(pHandler);


	}

	//3. lets check for OVR


	temp1= pHandler ->pSPIx->SR & (1 << SPI_SR_OVR);
	temp2= pHandler ->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);

	if (temp1 && temp2){

		//hanlde OVR
		spi_ovr_interrupt_hadle(pHandler);


	}


}

// some helper functions

static void spi_tx_interrupt_hadle(SPI_handler_t *pHandler)
{
	if ((pHandler->pSPIx->CR1 & (1 << SPI_CR1_CRCL)))
		{
		pHandler->pSPIx->DR  = *((uint16_t*)pHandler->TxBuffer);
		pHandler->TxLen--;
		pHandler->TxLen--;
			(uint16_t*)pHandler->TxBuffer++;


	}//else if((pSPIx->CR1 & ( 0<< SPI_CR1_CRCL)))
	else
		{

		pHandler->pSPIx->DR  = *pHandler->TxBuffer;
		pHandler->TxLen--;
		pHandler->TxBuffer++;
		}
	//if len is 0 close the transmission
	if(!pHandler->TxLen){

		SPI_CloseTransmission(pHandler);
		SPI_ApplicationEventCallback(pHandler, SPI_EVENT_TX_CMPLT);


	}


	}









static void spi_rx_interrupt_hadle(SPI_handler_t *pHandler)
{

	if (pHandler->pSPIx->CR1 & (1 << SPI_CR1_CRCL))
		{
			// 16 bit DFF
			 *((uint16_t*)pHandler->RxBuffer) = (uint16_t)pHandler->pSPIx->DR ;
			pHandler->RxLen=-2;
			pHandler->RxBuffer++;
			pHandler->RxBuffer++;

		}else
		{
			//8 bit DFF
			*pHandler->RxBuffer = pHandler->pSPIx->DR ;
			pHandler->RxLen--;

			pHandler->RxBuffer++;
		}

	//if len is 0 close the reception
	if(!pHandler->RxLen){
		SPI_CloseReception(pHandler);
		SPI_ApplicationEventCallback(pHandler, SPI_EVENT_RX_CMPLT);

	}

}


static void spi_ovr_interrupt_hadle(SPI_handler_t *pHandler)
{
	uint8_t temp;
	//clear the ovr flag
	if(pHandler->TxState != SPI_BUSY_IN_TX){

		temp = pHandler->pSPIx->DR;
		temp = pHandler->pSPIx->SR;

	}

	(void)temp;
	//inform the application
	SPI_ApplicationEventCallback(pHandler, SPI_EVENT_OVRF_ERR);


}


void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{

	}
void SPI_CloseTransmission(SPI_handler_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &=~(1<<SPI_CR2_TXEIE);
	pSPIHandle->TxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_READY;
	}
void SPI_CloseReception(SPI_handler_t *pSPIHandle)
{

	pSPIHandle->pSPIx->CR2 &=~(1<<SPI_CR2_RXNEIE);
	pSPIHandle->RxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;

	}



__weak void SPI_ApplicationEventCallback(SPI_handler_t *pSPIHandle, uint8_t AppEv)
{
	//this is the weak implementation. the application may override this funtion

}






