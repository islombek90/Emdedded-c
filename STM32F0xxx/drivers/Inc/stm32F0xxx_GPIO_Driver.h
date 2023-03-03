/*
 * stm32F0xxx_GPIO_Driver.h
 *
 *  Created on: 26 апр. 2021 г.
 *      Author: Im
 */

#ifndef INC_STM32F0XXX_GPIO_DRIVER_H_
#define INC_STM32F0XXX_GPIO_DRIVER_H_

#include "STM32F0xxx.h"



typedef struct {
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;


}GPIO_PinConfig_t;

typedef struct
{
	//place to hold GPIO base address according to port
	GPIO_RegDef_t *pGPOIx;                   /*this holds the address of pin to which port it belongs*/
	GPIO_PinConfig_t GPIO_PinConfig;         /*This will hold the pin settings*/

} GPIO_handler_t;



/*GPIO_PIN_NO
 * possible GPIO PIN NO
 */
#define GPIO_PIN_NO_0     0
#define GPIO_PIN_NO_1     1
#define GPIO_PIN_NO_2     2
#define GPIO_PIN_NO_3     3
#define GPIO_PIN_NO_4     4
#define GPIO_PIN_NO_5     5
#define GPIO_PIN_NO_6     6
#define GPIO_PIN_NO_7     7
#define GPIO_PIN_NO_8     8
#define GPIO_PIN_NO_9     9
#define GPIO_PIN_NO_10    10
#define GPIO_PIN_NO_11    11
#define GPIO_PIN_NO_12    12
#define GPIO_PIN_NO_13    13
#define GPIO_PIN_NO_14    14
#define GPIO_PIN_NO_15    15

/* GPIO_PIN_MODES
 * possible input modes
 */

#define GPIO_MODE_IN      0
#define GPIO_MODE_OUT     1
#define GPIO_MODE_ALTFUN  2
#define GPIO_MODE_ANALOG  3
#define GPIO_MODE_IT_FT   4
#define GPIO_MODE_IT_RT   5
#define GPIO_MODE_IT_RFT  6

/*GPIO_OUTPUT_TYPE*/
#define GPIO_PIN_OUT_PUSHPULL   0
#define GPIO_PIN_OUT_OPDRN      1

/*GPIO_SPEED*/
#define GPIO_PIN_SPEED_LOW     0
#define GPIO_PIN_SPEED_MED     1
#define GPIO_PIN_SPEED_HI      2

/*GPIO_PUSH UP and PULL DOWN configuration*/
#define GPIO_PIN_PUSHPULL_NO   0
#define GPIO_PIN_PUSHPULL_PU   1
#define GPIO_PIN_PUSHPULL_PD   2






// Enable and Disable Clock of GPIO

void GPIO_PeriClkControl(GPIO_RegDef_t *pGPOIx, uint8_t EnorDI);

//GPIO init Deinit
void GPIO_Init(GPIO_handler_t *pGPIOHandler);
void GPIO_DeInit(GPIO_RegDef_t *pGPOIx);

//GPIO mode
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPOIx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputtPort(GPIO_RegDef_t *pGPOIx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPOIx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPOIx,  uint16_t Value);
void ToggleOutputPin(GPIO_RegDef_t *pGPOIx, uint8_t PinNumber);

//GPIO interrupt
void GPIO_IRQHandler(uint8_t PinNumber);
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);





#endif /* INC_STM32F0XXX_GPIO_DRIVER_H_ */
