/*
 * stm32F0xxx_i2c_Driver.h
 *
 *  Created on: 24 июн. 2021 г.
 *      Author: Im
 */

#ifndef INC_STM32F0XXX_I2C_DRIVER_H_
#define INC_STM32F0XXX_I2C_DRIVER_H_

#include "STM32F0xxx.h"

typedef struct
{
	uint8_t I2C_DeviceAddress;
	uint8_t I2C_SlaveDeviceAddress;
	uint32_t I2C_SCLSpeed;
	uint8_t I2C_ACKControl;
	uint16_t I2C_FMDutyCylce;

}I2C_PinConfig_t;


typedef struct
{
	I2C_RegDef_t    *pI2Cx;           // adress of I2Cx perihperals
	I2C_PinConfig_t I2C_Config;		// I2cx register configuration
	uint8_t         *TxBuffer;		// Transmit buffer
	uint8_t         *RxBuffer;		// Receive buffer
	uint32_t         RxLen;			// Len of receoption buffer
	uint32_t         TxLen;			//Len of Transmition buffer
	uint8_t          TxRxState;		// i2c states
	uint8_t          DevAddr;		// slave/device address
	uint32_t         RxSize;        //to store Rx size
	uint8_t          Sr;             // repeated start

}I2C_Handle_t;

/*
 * @Speed Macros
 */

#define I2C_SCL_SPEED_SM     100000
#define I2C_SCL_SPEED_FM4k   400000
#define I2C_SCL_SPEED_FM2k   200000

/*
 * @ACK Macros
 */

#define I2C_ACK_EN           1
#define I2C_ACK_DI           0

/*
 * @FM Duty Cycle control Macros
 */

#define I2C_FM_DUTY_2        0
#define I2C_FM_DUTY_16_9     1

// define I2c states
#define I2C_READY            0
#define I2C_BUSY_IN_TX       1
#define I2C_BUSY_IN_RX       2


void I2C_PeriClkControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDI);

//enable and disable I2C peripheral
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDI);

//I2C init Deinit
void I2C_Init(I2C_Handle_t *pI2CHandler);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxbuffer,uint32_t Len);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxbuffer,uint32_t Len);

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);



//Application Callback
void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv);



void I2C_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);




#endif /* INC_STM32F0XXX_I2C_DRIVER_H_ */
