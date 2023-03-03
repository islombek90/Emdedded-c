/*
 * stm32F0xxx_GPIO_Driver.c
 *
 *  Created on: 26 апр. 2021 г.
 *      Author: Im
 */

#include "stm32F0xxx_GPIO_Driver.h"
/*****************************************************************
 * @fn             -  GPIO_PeriClkControl
 *
 * @brief          - This function enables or disables the GPIO port clock
 *
 * @parama[in]     - the base address of GPIO port peripheral
 * @parama[in]     - The macros of Enable or Disable
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
 */
void GPIO_PeriClkControl(GPIO_RegDef_t *pGPOIx, uint8_t EnorDI)
{
	if (EnorDI == ENABLE)
	{
		if( pGPOIx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if ( pGPOIx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if ( pGPOIx == GPIOC)
				{
					GPIOC_PCLK_EN();
				}
		else if ( pGPOIx == GPIOD)
				{
					GPIOD_PCLK_EN();
				}


		else if ( pGPOIx == GPIOF)
				{
					GPIOF_PCLK_EN();
				}


	}
	else
		if( pGPOIx == GPIOA)
				{
					GPIOA_PCLK_DI();
				}
				else if ( pGPOIx == GPIOB)
				{
					GPIOB_PCLK_DI();
				}
				else if ( pGPOIx == GPIOC)
						{
							GPIOC_PCLK_DI();
						}
				else if ( pGPOIx == GPIOD)
						{
							GPIOD_PCLK_DI();
						}


				else if ( pGPOIx == GPIOF)
						{
							GPIOF_PCLK_DI();
						}



}

/*****************************************************************
 * @fn             - GPIO_Init
 *
 * @brief          - this function will configure pinmode of GPIO port peripheral
 *
 * @parama[in]     - The GPIO port base address
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -None
 *
 * @note           -None
 */
void GPIO_Init(GPIO_handler_t *pGPIOHandler)
{
	//1. Configure mode of GPIO
	uint32_t temp = 0;

	GPIO_PeriClkControl(pGPIOHandler->pGPOIx, ENABLE);

	if (pGPIOHandler -> GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		temp = pGPIOHandler -> GPIO_PinConfig.GPIO_PinMode << (2*pGPIOHandler -> GPIO_PinConfig.GPIO_PinNumber);
		pGPIOHandler->pGPOIx->MODER &= ~( 0x3 << ( 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber)); //clearing

		pGPIOHandler -> pGPOIx->MODER |= temp;

	}
	else // TODO later, interrupts
	{
		if (pGPIOHandler -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			EXTI->EXTI_FTSR |= (1 << pGPIOHandler ->GPIO_PinConfig.GPIO_PinNumber );//1. configure the FTSR
			EXTI->EXTI_RTSR &=~(1 << pGPIOHandler ->GPIO_PinConfig.GPIO_PinNumber ); //CLEAR the RTSR for any case


		}
		else if(pGPIOHandler -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			EXTI->EXTI_RTSR |= (1<< pGPIOHandler ->GPIO_PinConfig.GPIO_PinNumber );//1. configure the RTSR
			EXTI->EXTI_FTSR &=~(1<<pGPIOHandler ->GPIO_PinConfig.GPIO_PinNumber ); //CLEAR the FTSR for any case
		}
		else if(pGPIOHandler -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//1. configure the RFTSR
			EXTI->EXTI_FTSR |= (1<< pGPIOHandler ->GPIO_PinConfig.GPIO_PinNumber );//1. configure the FTSR
			EXTI->EXTI_RTSR |= (1<<pGPIOHandler ->GPIO_PinConfig.GPIO_PinNumber );//1. configure the RTSR
		}

		//2. configure GPIO PORT selection to SYSCFG_EXTI
		uint8_t temp1 = pGPIOHandler ->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandler ->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t port = GPIO_BASEADRESS_TO_CODE(pGPIOHandler->pGPOIx);
		SYSCFG_PCLK_EN();
		SYSCFG->SYSCFG_EXTICR[temp1] |=(port << temp2*4);



		//3. enable the EXTI interrupt using IMR

		EXTI->EXTI_IMR |= (1<< pGPIOHandler ->GPIO_PinConfig.GPIO_PinNumber );

	}

	//2. Configure SPEED
	temp = 0;
	temp = pGPIOHandler -> GPIO_PinConfig.GPIO_PinSpeed << (2*pGPIOHandler -> GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandler->pGPOIx->OSPEEDR &= ~( 0x3 << ( 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber)); //clearing
    pGPIOHandler -> pGPOIx->OSPEEDR|= temp;

	//3. Configure PUPD
	temp = 0;

	temp = pGPIOHandler -> GPIO_PinConfig.GPIO_PinPuPdControl << (2*pGPIOHandler -> GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandler->pGPOIx->PUPDR &= ~( 0x3 << ( 2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandler -> pGPOIx->PUPDR |= temp;
	//4. Configure OP type
	temp = 0;
	temp = pGPIOHandler -> GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandler -> GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandler->pGPOIx->OTYPER &= ~( 0x1 << (  pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber)); //clearing

	pGPIOHandler -> pGPOIx->OTYPER |= temp;

	//5. Configure ALTF mdoe
	if (pGPIOHandler -> GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFUN)
	{
		uint8_t temp1, temp2;
		temp1 = pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber /8;
		temp2 = pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber %8;
		pGPIOHandler->pGPOIx->AFR[temp1] &= ~( 0xF << ( 4* temp2)); //clearing

		pGPIOHandler ->pGPOIx->AFR[temp1] |= (pGPIOHandler->GPIO_PinConfig.GPIO_PinAltFunMode <<(4*temp2));


	}


}
/*****************************************************************
 * @fn             - GPIO_DeInit
 *
 * @brief          - This funtion will reset all regirster adress of GPIO port
 *
 * @parama[in]     - GPIO port base address
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         - None
 *
 * @note           - None
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPOIx)
{

	if( pGPOIx == GPIOA)
			{
				GPIOA_RESET();
			}
			else if ( pGPOIx == GPIOB)
			{
				GPIOB_RESET();
			}
			else if ( pGPOIx == GPIOC)
					{
						GPIOC_RESET();
					}
			else if ( pGPOIx == GPIOD)
					{
						GPIOD_RESET();
					}


			else if ( pGPOIx == GPIOF)
					{
						GPIOF_RESET();
					}


}

/*****************************************************************
 * @fn             - GPIO_ReadFromInputPin
 *
 * @brief          - This funtion will read data from pin
 *
 * @parama[in]     - GPIO port peripheral base address
 * @parama[in]     - Pin Number
 * @parama[in]     -
 *
 * @return         - uint8_t
 *
 * @note           -None
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPOIx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t) ((pGPOIx ->IDR >> PinNumber) & 0x00000001);
	return value;


}

/*****************************************************************
 * @fn             - GPIO_ReadFromInputtPort
 *
 * @brief          - This function reads data from whole port
 *
 * @parama[in]     - GPIO port peripheral base address
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         - uint16_t,
 *
 * @note           - 16 because each port has 16 pins,
 */
uint16_t GPIO_ReadFromInputtPort(GPIO_RegDef_t *pGPOIx)
{
 uint16_t value;
 value = (uint16_t) (pGPOIx ->IDR);
 return value;

}
/*****************************************************************
 * @fn             - GPIO_WriteToOutputPin
 *
 * @brief          - This function writes to pin O or 1
 *
 * @parama[in]     - GPIO port peripheral base address
 * @parama[in]     - Pin NUmber
 * @parama[in]     - Valeu, 1 or 0
 *
 * @return         -None
 *
 * @note           -None
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPOIx, uint8_t PinNumber, uint8_t Value)
{
	if (Value == PIN_SET)
	{
		pGPOIx ->ODR |= (1 << PinNumber);
	}
	else
	{
		pGPOIx ->ODR &=~(1 << PinNumber);

	}



}
/*****************************************************************
 * @fn             - GPIO_WriteToOutputPort
 *
 * @brief          - this function writes to whole port
 *
 * @parama[in]     - GPIO port peripheral base address
 * @parama[in]     - value, 1 or 0
 * @parama[in]     -
 *
 * @return         - None
 *
 * @note           - None
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPOIx,  uint16_t Value)
{

	pGPOIx ->ODR |= Value;

}
/*****************************************************************
 * @fn             - ToggleOutputPin
 *
 * @brief          - This function will toggle the pin, on and off
 *
 * @parama[in]     - GPIO port peripheral base address,
 * @parama[in]     -pin number
 * @parama[in]     -
 *
 * @return         - None
 *
 * @note           -None
 */
void ToggleOutputPin(GPIO_RegDef_t *pGPOIx, uint8_t PinNumber)
{
	pGPOIx -> ODR ^= (1<< PinNumber);


}

/*****************************************************************
 * @fn             -
 *
 * @brief          -
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -
 *
 * @note           -
 */
void GPIO_IRQHandler(uint8_t PinNumber)
{
 // clear the PR register correspoding to the pin number
	if (EXTI->EXTI_PR & (1 << PinNumber)){

		//clear
		EXTI ->EXTI_PR |= (1 << PinNumber);

	}

}
/*****************************************************************
 * @fn             -
 *
 * @brief          -
 *
 * @parama[in]     -
 * @parama[in]     -
 * @parama[in]     -
 *
 * @return         -
 *
 * @note           -
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,  uint8_t EnorDi)
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

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

	//1. lets find the ipr register

	uint8_t ipx = IRQNumber /4;
	uint8_t ipx_section = IRQNumber % 4;
	uint8_t shift_amount = (8*ipx_section)+(8-NO_PR_BIRS_IMPLEMENTED);

	*(NVIC_PR_BASEDADDR + (ipx)) |= (IRQPriority << shift_amount);





}

