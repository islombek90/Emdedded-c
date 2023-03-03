/*
 * stm32F0xxx_SPI_Driver.h
 *
 *  Created on: 15 мая 2021 г.
 *      Author: Im
 */

#ifndef INC_STM32F0XXX_SPI_DRIVER_H_
#define INC_STM32F0XXX_SPI_DRIVER_H_

#include "STM32F0xxx.h"

typedef struct {

	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_DFF;
	uint8_t SPI_CPHA;
	uint8_t SPI_CPOL;
	uint8_t SPI_SSM;
	uint8_t SPI_SclkSpeed;

}SPI_Config_t;


typedef struct
{
	//place to hold GPIO base address according to port
	SPI_RegDef_t *pSPIx;                   /*this holds the address of pin to which port it belongs*/
	SPI_Config_t SPI_Config;         /*This will hold the pin settings*/
	uint8_t      *TxBuffer;         // adress to store global buffer variables
	uint8_t      *RxBuffer;         // address to store receive variables
	uint32_t        TxLen;            // the length of transmit signal
	uint32_t        RxLen ;           //the length of receive signal
	uint8_t        TxState;         // Tx status
	uint8_t        RxState ;         // Rx status

} SPI_handler_t;

/****************************************API START***********************************
 *
 *
 * */

/*
 * @SPI_DeviceMode
 */

#define SPI_DEVICE_MASTER    1
#define SPI_DEVICE_SLAVE     0

/*
 * @SPI_BusConfig
 */

#define SPI_MODE_FD                     0
#define SPI_MODE_HD                     1
#define SPI_MODE_SIMPLEX_RECIEVE_ONLY   2

/*
 * @SPI_DFF
 */


#define SPI_DATA_SIZE8                0
#define SPI_DATA_SIZE16               1


/*
 * @SPI_CPHA
 */

#define SPI_CPHA_HIGH               1
#define SPI_CPHA_LOW                0

/*
 * @SPI_CPOL
 */

#define SPI_CPOL_HIGH              1
#define SPI_CPOL_LOW               0

/*
 * @SPI_SMM
 */

#define SPI_SMM_EN             1
#define SPI_SMM_DI             0


/*
 * @SPI_SclkSpeed
 */

#define SPI_CLKSPEED_DIV2          0
#define SPI_CLKSPEED_DIV4          1
#define SPI_CLKSPEED_DIV8          2
#define SPI_CLKSPEED_DIV16         3
#define SPI_CLKSPEED_DIV32         4
#define SPI_CLKSPEED_DIV64         5
#define SPI_CLKSPEED_DIV128        6
#define SPI_CLKSPEED_DIV256        7

/*SPI masks for STATUS register*/

#define SPI_TX_FLAG         (1<< SPI_SR_TXE)
#define SPI_RX_FLAG			(1<<SPI_SR_RXNE)
#define SPI_BUSY_FLAG		(1<<SPI_SR_BSY)

/* the possible state for intterupt based SPI*/

#define SPI_READY                 0
#define SPI_BUSY_IN_RX            1
#define SPI_BUSY_IN_TX            2


// events

#define SPI_EVENT_TX_CMPLT     1
#define SPI_EVENT_RX_CMPLT     2
#define SPI_EVENT_OVRF_ERR     3

void SPI_PeriClkControl(SPI_RegDef_t *pSPIx, uint8_t EnorDI);

//enable and disable SPI peripheral
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDI);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDI);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDI);
//SPI init Deinit
void SPI_Init(SPI_handler_t *pSPIHandler);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTX_Buffer, uint32_t Len);
void SPI_RecveiveData(SPI_RegDef_t *pSPIx, uint8_t *pRX_Buffer, uint32_t Len);

uint8_t SPI_SendDataIT(SPI_handler_t *pSPIHandle, uint8_t *pTX_Buffer, uint32_t Len);
uint8_t SPI_RecveiveDataIT(SPI_handler_t *pSPIHandle, uint8_t *pRX_Buffer, uint32_t Len);

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmission(SPI_handler_t *pSPIHandle);
void SPI_CloseReception(SPI_handler_t *pSPIHandle);

//Application Callback
void SPI_ApplicationEventCallback(SPI_handler_t *pSPIHandle, uint8_t AppEv);


void SPI_IRQHandler(SPI_handler_t *pHandler);
void SPI_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);



#endif /* INC_STM32F0XXX_SPI_DRIVER_H_ */
