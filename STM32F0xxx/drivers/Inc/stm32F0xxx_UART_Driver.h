/*
 * stm32F0xxx_UART_Driver.h
 *
 *  Created on: 16 авг. 2021 г.
 *      Author: Im
 */

#ifndef INC_STM32F0XXX_UART_DRIVER_H_
#define INC_STM32F0XXX_UART_DRIVER_H_


#include "STM32F0xxx.h"

typedef struct {

	uint8_t USART_WordLength;
	uint8_t USART_OverSampling;
	uint32_t USART_BaudRate;
	uint8_t USART_StopBitMode;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;
	uint8_t USART_Mode;

}USART_Config_t;


typedef struct
{
	//place to hold GPIO base address according to port
	USART_RegDef_t *pUSARTx;                   /*this holds the address of pin to which port it belongs*/
	USART_Config_t USART_Config;         /*This will hold the pin settings*/
	uint8_t      *pTxBuffer;         // adress to store global buffer variables
	uint8_t      *pRxBuffer;         // address to store receive variables
	uint32_t        TxLen;            // the length of transmit signal
	uint32_t        RxLen ;           //the length of receive signal
	uint8_t        TxBusyState;         // Tx status
	uint8_t        RxBusyState ;         // Rx status

} USART_handler_t;

/****************************************API START***********************************
 *

 * @USART possible modes
 */

#define USART_MODE_ONLY_TX                    0
#define USART_MODE_ONLY_RX                    1
#define USART_MODE_TXRX                       2

/*
 * @USART Word Length
 */

#define USART_WORD_LENGTH_8                0
#define USART_WORD_LENGTH_9                1


/*
 *@USART_Baud
 *Possible options for USART_Baud
 */
#define USART_STD_BAUD_1200					1200
#define USART_STD_BAUD_2400					2400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define SUART_STD_BAUD_3M 					3000000

/*
 * @USART Parity Control
 */

#define USART_PARITY_EN_ODD          2
#define USART_PARITY_EN_EVEN         1
#define USART_PARITY_DISABLE         0


/*@USART_NoOfStopBits
*Possible options for USART_NoOfStopBits
*/
#define USART_STOPBITS_1     0
#define USART_STOPBITS_0_5   1
#define USART_STOPBITS_2     2
#define USART_STOPBITS_1_5   3


/*
*@USART_HWFlowControl
*Possible options for USART_HWFlowControl
*/
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3



/*
 * USART flags
 */

#define USART_FLAG_TXE 			( 1 << USART_ISR_TXE)
#define USART_FLAG_RXNE 		( 1 << USART_ISR_RXNE)
#define USART_FLAG_TC 			( 1 << USART_ISR_TC)

/*
 * Application states
 */
#define USART_BUSY_IN_RX 1
#define USART_BUSY_IN_TX 2
#define USART_READY 0


#define 	USART_EVENT_TX_CMPLT     0
#define		USART_EVENT_RX_CMPLT     1
#define		USART_EVENT_IDLE         2
#define		USART_EVENT_CTS          3
#define		USART_EVENT_PE           4
#define		USART_ERR_FE     	     5
#define		USART_ERR_NE    	     6
#define		USART_ERR_ORE    	     7




void USART_PeriClkControl(USART_RegDef_t *pUSARTx, uint8_t EnorDI);

//enable and disable USART peripheral
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDI);

//USART init Deinit
void USART_Init(USART_handler_t *pUSARTHandler);
void USART_DeInit(USART_RegDef_t *pUSARTx);

void USART_SendData(USART_handler_t  *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_handler_t  *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);

uint8_t USART_SendDataIT(USART_handler_t *pUSARTHandle, uint8_t *pTX_Buffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_handler_t *pUSARTHandle, uint8_t *pRX_Buffer, uint32_t Len);

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t FlagName);

void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);

//Application Callback
void USART_ApplicationEventCallback(USART_handler_t *pUSARTHandle, uint8_t AppEv);


void USART_IRQHandling(USART_handler_t *pHandler);
void USART_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);


#endif /* INC_STM32F0XXX_UART_DRIVER_H_ */
