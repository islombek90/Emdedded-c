/*
 * stm32F0xxx_rcc_Driver.h
 *
 *  Created on: Aug 17, 2021
 *      Author: Im
 */

#ifndef INC_STM32F0XXX_RCC_DRIVER_H_
#define INC_STM32F0XXX_RCC_DRIVER_H_
#include "STM32F0xxx.h"


//This returns the APB1 clock value
uint32_t RCC_GetPCLK1Value(void);

//This returns the APB2 clock value
uint32_t RCC_GetPCLK2Value(void);


uint32_t  RCC_GetPLLOutputClock(void);


#endif /* INC_STM32F0XXX_RCC_DRIVER_H_ */
