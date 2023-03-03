/*
 * STM32F0xxx.h
 *
 *  Created on: Apr 22, 2021
 *      Author: Im
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define __vo volatile
#define __weak __attribute__((weak))

/*Main flasn and Sram base addresses*/
#ifndef INC_STM32F0XXX_H_
#define INC_STM32F0XXX_H_

/*********************************************STRAT FILE OF THE PROCESSOR****************************************/
/* Cortex Mx NVIC Macros definition
 *
 */
//defining interrupt set register
#define NVIC_ISER0					   ((__vo uint32_t*)0xE000E100)
//#define NVIC_ISER0					   0xE000E104     /* For other Mx processors if needed*/
//#define NVIC_ISER0					   0xE000E108     /* For other Mx processors if needed*/

//defining interrupt clear register
#define NVIC_ICER0					   ((__vo uint32_t*)0xE000E180)
//#define NVIC_ICER0					   0xE000E184    /* For other Mx processors if needed*/
//#define NVIC_ICER0					   0xE000E188   /* For other Mx processors if needed*/

//defining interrupt priority register based address
#define NVIC_PR_BASEDADDR              ((__vo uint32_t*) 0xE000E400)

#define NO_PR_BIRS_IMPLEMENTED         4


#define FLASH_BASEADDR                 0x08000000U 			 /* Main memory of flash */
#define SRAM1_BASEADDR                 0x20000000U			/*Main Sram1 of MCU*/
#define SRAM                           SRAM1_BASEADDR		/*Redefining Sram 1 as main SRAM*/
#define ROM_BASEADDR                   0x1FFFEC00U			/*main memory of system*/


/*Bus bus addresses*/

#define PERIPH_BASEADDR				   0x40000000U              /*Starting Address of Peripherals*/
#define APB_BASEADDR				   PERIPH_BASEADDR		    /*base address of APB*/
#define AHB1_BASEADDR                  0x40020000U				/*Base address of AHB1 bus*/
#define AHB2_BASEADDR                  0x48000000U              /*Base address of AHB2 bus*/


/*Defining GPIO addresses on AHB2 BUS*/

#define GPIOA_BASEADDR                (AHB2_BASEADDR +0x0000)
#define GPIOB_BASEADDR                (AHB2_BASEADDR +0x0400)
#define GPIOC_BASEADDR                (AHB2_BASEADDR +0x0800)
#define GPIOD_BASEADDR                (AHB2_BASEADDR +0x0C00)
#define GPIOF_BASEADDR                (AHB2_BASEADDR +0x1400)

/*Defining GPIO addresses on AHB1 BUS*/

#define DMA_BASEADDR                  AHB1_BASEADDR
#define RCC_BASEADDR                  (AHB1_BASEADDR+0x1000)

/* Defining peripherals on APB BUS */

#define ADC_BASEADDR              (APB_BASEADDR+0x12400)
#define DBGMCU_BASEADDR           (APB_BASEADDR+0x15800)
#define EXTI_BASEADDR             (APB_BASEADDR+0x10400)
#define I2C1_BASEADDR             (APB_BASEADDR+0x5400)
#define I2C2_BASEADDR             (APB_BASEADDR+0x5800)
#define PWM_BASEADDR              (APB_BASEADDR+0x7000)
#define RTC_BASEADDR              (APB_BASEADDR+0x2800)
#define SP1_BASEADDR              (APB_BASEADDR+0x13000)
#define SP2_BASEADDR              (APB_BASEADDR+0x3800)
#define SYSCFG_BASEADDR           (APB_BASEADDR+0x10000)
#define TIM1_BASEADDR             (APB_BASEADDR+0x12C00)
#define TIM3_BASEADDR             (APB_BASEADDR+0x0400)
#define TIM6_BASEADDR             (APB_BASEADDR+0x1000)
#define TIM14_BASEADDR            (APB_BASEADDR+0x2000)
#define TIM15_BASEADDR            (APB_BASEADDR+0x14000)
#define TIM16_BASEADDR            (APB_BASEADDR+0x14400)
#define TIM17_BASEADDR            (APB_BASEADDR+0x14800)
#define USART1_BASEADDR           (APB_BASEADDR+0x13800)
#define USART2_BASEADDR           (APB_BASEADDR+0x4400)


/*defining the registers of each Ports, here type struct is used to make it automatically
instead of defining each port register separately*/
typedef struct
{
	__vo uint32_t MODER;             /* Base address of GPIO port, offset is +0x0000*/
	__vo uint32_t OTYPER;            /* offset addition done automatically, +0x0004*/
	__vo uint32_t OSPEEDR;           /* offset addition done automatically, +0x0004*/
	__vo uint32_t PUPDR;             /* offset addition done automatically, +0x0004*/
	__vo uint32_t IDR;              /* offset addition done automatically, +0x0004*/
	__vo uint32_t ODR;              /* offset addition done automatically, +0x0004*/
	__vo uint32_t BSRR;             /* offset addition done automatically, +0x0004*/
	__vo uint32_t LCKR;             /* offset addition done automatically, +0x0004*/
	__vo uint32_t AFR[2];           /*here, array is assigned where AF[0] is for Low register and AF[1] is for high register offset addition done automatically, +0x0004*/
	__vo uint32_t BRR;              /* offset addition done automatically, +0x0004*/


} GPIO_RegDef_t;

typedef struct
{
	__vo uint32_t EXTI_IMR;             /* Base address EXTI, offset is +0x0000*/
	__vo uint32_t EXTI_EMR;            /* offset addition done automatically, +0x0004*/
	__vo uint32_t EXTI_RTSR;           /* offset addition done automatically, +0x0004*/
	__vo uint32_t EXTI_FTSR;             /* offset addition done automatically, +0x0004*/
	__vo uint32_t EXTI_SWIER;              /* offset addition done automatically, +0x0004*/
	__vo uint32_t EXTI_PR;              /* offset addition done automatically, +0x0004*/



} EXTI_RegDef_t;


typedef struct
{
	__vo uint32_t SYSCFG_CFGR1;                /* Base address EXTI, offset is     +0x0000*/
	__vo uint32_t RESERVED;                    /* offset addition done automatically, +0x4*/
	__vo uint32_t SYSCFG_EXTICR[4];              /* offset addition done automatically,  0x8*/
	__vo uint32_t SYSCFG_CFGR2;                /* offset addition done automatically, 0x18*/


} SYSCFG_RegDef_t;

/*defining the registers of each SPI, here type struct is used to make it automatically
instead of defining each SPI register separately*/
typedef struct
{
	__vo uint32_t CR1;             /* Base address of GPIO port, offset is +0x0000*/
	__vo uint32_t CR2;            /* offset addition done automatically, +0x0004*/
	__vo uint32_t SR;            /* offset addition done automatically, +0x0004*/
	__vo uint32_t DR;           /* offset addition done automatically, +0x0004*/
	__vo uint32_t CRCPR;             /* offset addition done automatically, +0x0004*/
	__vo uint32_t RXCRCR;              /* offset addition done automatically, +0x0004*/
	__vo uint32_t TXCRCR;              /* offset addition done automatically, +0x0004*/


}SPI_RegDef_t;


/*defining the registers of each USART, here type struct is used to make it automatically
instead of defining each USART register separately*/
typedef struct
{
	__vo uint32_t USART_CR1;             /* Base address of GPIO port, offset is +0x0000*/
	__vo uint32_t USART_CR2;            /* offset addition done automatically, +0x0004*/
	__vo uint32_t USART_CR3;            /* offset addition done automatically, +0x0004*/
	__vo uint32_t USART_BRR;           /* offset addition done automatically, +0x0004*/
	__vo uint32_t RESERVED;
	__vo uint32_t USART_RTOR;             /* offset addition done automatically, +0x0004*/
	__vo uint32_t USART_RQR;              /* offset addition done automatically, +0x0004*/
	__vo uint32_t USART_ISR;              /* offset addition done automatically, +0x0004*/
	__vo uint32_t USART_ICR;              /* offset addition done automatically, +0x0004*/
	__vo uint32_t USART_RDR;              /* offset addition done automatically, +0x0004*/
	__vo uint32_t USART_TDR;              /* offset addition done automatically, +0x0004*/


}USART_RegDef_t;


//dereferencing USART struct

#define USART1   ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2   ((USART_RegDef_t*)USART2_BASEADDR)


/*defining and type casting each port*/
#define GPIOA   ((GPIO_RegDef_t*)GPIOA_BASEADDR)  /*GPIOA type casted to GPIOA BASEADDRESS*/
#define GPIOB   ((GPIO_RegDef_t*)GPIOB_BASEADDR)  /*GPIOB type casted to GPIOB BASEADDRESS*/
#define GPIOC   ((GPIO_RegDef_t*)GPIOC_BASEADDR)  /*GPIOC type casted to GPIOC BASEADDRESS*/
#define GPIOD   ((GPIO_RegDef_t*)GPIOD_BASEADDR)  /*GPIOD type casted to GPIOD BASEADDRESS*/
#define GPIOF   ((GPIO_RegDef_t*)GPIOF_BASEADDR)  /*GPIOF type casted to GPIOF BASEADDRESS*/

//defining type casting of EXTI peripheral
#define EXTI   ((EXTI_RegDef_t*)EXTI_BASEADDR)  /*GPIOF type casted to GPIOF BASEADDRESS*/

//defining SYSCFG peripheral struct so we can further dereference it
#define SYSCFG   ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

//dereferencing SPI struct

#define SPI1   ((SPI_RegDef_t*)SP1_BASEADDR)
#define SPI2   ((SPI_RegDef_t*)SP2_BASEADDR)

typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t APB1RSTR;
	__vo uint32_t AHBENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t APB1ENR;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t AHBRSTR;
	__vo uint32_t CFGR2;
	__vo uint32_t CFGR3;
	__vo uint32_t CR2;


} RCC_RegDef_t;

// defining I2C register definition struct

typedef struct
{
	__vo uint32_t I2C_CR1;             //offset address of first register 0x0
	__vo uint32_t I2C_CR2;			   //the next register address, +0x4 added automatical, 0x4
	__vo uint32_t I2C_OAR1;            //0x8
	__vo uint32_t I2C_OAR2;            //0xC  --> 12 in Dec
	__vo uint32_t I2C_TIMINGR;         //0x10 --> 16 in Dec
	__vo uint32_t I2C_TIMEOUTR;		   //0x14 --> 20 in Dec
	__vo uint32_t I2C_ISR;			   //0x18 --> 24 in Dec
	__vo uint32_t I2C_ICR;             //0x1C --> 28 in Dec
	__vo uint32_t I2C_PECR;			   //0x20 --> 32 in Dec
	__vo uint32_t I2C_RXDR;            //0x24 --> 36 in Dec
	__vo uint32_t I2C_TXDR;            //0x28 --> 40 in Dec



}I2C_RegDef_t;

//defining peripheral definition macros

#define I2C1   ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2   ((I2C_RegDef_t*)I2C2_BASEADDR)

/*defining and type casting RCC base adress so we can further dereference it*/
#define RCC  ((RCC_RegDef_t*)RCC_BASEADDR)

/*Enabling Clocks of Ports*/
#define GPIOA_PCLK_EN()   (RCC -> AHBENR |= (1 << 17)) /*bitwise or operation was done to set 17 bit of AHBENR register*/
#define GPIOB_PCLK_EN()   (RCC -> AHBENR |= (1 << 18)) /*bitwise or operation was done to set 18 bit of AHBENR register*/
#define GPIOC_PCLK_EN()   (RCC -> AHBENR |= (1 << 19)) /*bitwise or operation was done to set 19 bit of AHBENR register*/
#define GPIOD_PCLK_EN()   (RCC -> AHBENR |= (1 << 20)) /*bitwise or operation was done to set 20 bit of AHBENR register*/
#define GPIOF_PCLK_EN()   (RCC -> AHBENR |= (1 << 22)) /*bitwise or operation was done to set 22 bit of AHBENR register*/


/*Enable clocks of I2cx*/

#define I2C1_PCLK_EN()  (RCC-> APB1ENR |= (1<<21))  /*Enabling Peripheral clock of I2C1 */
#define I2C2_PCLK_EN()  (RCC-> APB1ENR |= (1<<22))  /*Enabling Peripheral clock of I2C2 */




/*Enable clocks of SPIx*/

#define SPI1_PCLK_EN()  (RCC-> APB2ENR |= (1<<12))  /*Enabling Peripheral clock of SPI1 */
#define SPI2_PCLK_EN()  (RCC-> APB1ENR |= (1<<14))  /*Enabling Peripheral clock of SPI2 */


/*Enable clocks of UARTx*/

#define UART1_PCLK_EN()  (RCC-> APB2ENR |= (1<<14))  /*Enabling Peripheral clock of UART1 */
#define UART2_PCLK_EN()  (RCC-> APB1ENR |= (1<<17))  /*Enabling Peripheral clock of UART2 */

/*Enable clocks of SYSCFG*/
#define SYSCFG_PCLK_EN()  (RCC-> APB2ENR |= (1<<0))  /*Enabling Peripheral clock of SYSCFG */

/*Disabling Clocks of Ports*/
#define GPIOA_PCLK_DI()   (RCC -> AHBENR &= ~(1 << 17)) /*bitwise AND operation was done to Clear 17 bit of AHBENR register*/
#define GPIOB_PCLK_DI()   (RCC -> AHBENR &= ~(1 << 18)) /*bitwise AND operation was done to Clear 18 bit of AHBENR register*/
#define GPIOC_PCLK_DI()   (RCC -> AHBENR &= ~(1 << 19)) /*bitwise AND operation was done to Clear 19 bit of AHBENR register*/
#define GPIOD_PCLK_DI()   (RCC -> AHBENR &= ~(1 << 20)) /*bitwise AND operation was done to Clear 20 bit of AHBENR register*/
#define GPIOF_PCLK_DI()   (RCC -> AHBENR &= ~(1 << 22)) /*bitwise AND operation was done to Clear 22 bit of AHBENR register*/


/*Disabling clocks of I2cx*/

#define I2C1_PCLK_DI()  (RCC-> APB1ENR &= ~ (1<<21))  /*Disabling Peripheral clock of I2C1 */
#define I2C2_PCLK_DI()  (RCC-> APB1ENR &= ~(1<<22))  /*Disabling Peripheral clock of I2C2 */




/*Disabling clocks of SPIx*/

#define SPI1_PCLK_DI()  (RCC-> APB2ENR &= ~ (1<<12))  /*Disabling Peripheral clock of SPI1 */
#define SPI2_PCLK_DI()  (RCC-> APB1ENR &= ~ (1<<14))  /*Disabling Peripheral clock of SPI2 */


/*Disabling clocks of UARTx*/

#define UART1_PCLK_DI()  (RCC-> APB1ENR &= ~(1<<17))  /*Disabling Peripheral clock of UART1 */
#define UART2_PCLK_DI()  (RCC-> APB2ENR &= ~(1<<14))  /*Disabling Peripheral clock of UART2 */

/*Disabling clocks of SYSCFG*/
#define SYSCFG_PCLK_DI()  (RCC-> APB2ENR &= ~ (1<<0))  /*Disabling Peripheral clock of SYSCFG */

/*Macros to reset GPIO peripherals*/

#define GPIOA_RESET()            do{RCC->AHBRSTR |= (1 << 17); RCC->AHBRSTR &= ~(1 << 17);} while(0)
#define GPIOB_RESET()            do{RCC->AHBRSTR |= (1 << 18); RCC->AHBRSTR &= ~(1 << 18);} while(0)
#define GPIOC_RESET()            do{RCC->AHBRSTR |= (1 << 19); RCC->AHBRSTR &= ~(1 << 19);} while(0)
#define GPIOD_RESET()            do{RCC->AHBRSTR |= (1 << 20); RCC->AHBRSTR &= ~(1 << 20);} while(0)
#define GPIOF_RESET()            do{RCC->AHBRSTR |= (1 << 22); RCC->AHBRSTR &= ~(1 << 22);} while(0)


// macros to reset SPI peripherals
#define SPI1_RESET()            do{RCC->APB2RSTR |= (1<<12); RCC->APB1RSTR &= ~(1 << 12);} while(0)
#define SPI2_RESET()            do{RCC->APB1RSTR |= (1<<14); RCC->APB2RSTR &= ~(1 << 14);} while(0)


//macros for resetting I2C peripherals
#define I2C1_RESET()            do{RCC->APB1RSTR |= (1<<21); RCC->APB2RSTR &= ~(1 << 21);} while(0)
#define I2C2_RESET()            do{RCC->APB1RSTR |= (1<<22); RCC->APB2RSTR &= ~(1 << 22);} while(0)



#define GPIO_BASEADRESS_TO_CODE(x)   ((x == GPIOA) ? 0 :\
									 (x == GPIOB) ? 1 :\
									 (x == GPIOC) ? 2 :\
									 (x == GPIOD) ? 3 :\
									 (x == GPIOF) ? 4 :0)

//  defining EXTI IRQ numbers

#define IRQ_NO_EXTI0_1          5
#define IRQ_NO_EXTI2_3          6
#define IRQ_NO_EXTI4_15         7

//defining SPI IRQ number
#define IRQ_NO_SPI1            25
#define IRQ_NO_SPI2            26

//defining UART IRQ number
#define IRQ_NO_USART1            27
#define IRQ_NO_USART2            28


// define nvic priority numbers


#define NVIC_PRI0 		 0
#define NVIC_PRI1 		 1
#define NVIC_PRI2        2
#define NVIC_PRI3 		 3
#define NVIC_PRI4 		 4
#define NVIC_PRI5 		 5
#define NVIC_PRI6 		 6
#define NVIC_PRI7 		 7
#define NVIC_PRI8 		 8
#define NVIC_PRI9 		 9
#define NVIC_PRI10 		 10
#define NVIC_PRI11 		 11
#define NVIC_PRI12 		 12
#define NVIC_PRI13 		 13
#define NVIC_PRI14 		 14
#define NVIC_PRI15 		 15

/* SPI bit positions definitions
 * SPI control register 1 bit positions
 * */

#define SPI_CR1_CPHA      0
#define SPI_CR1_CPOL      1
#define SPI_CR1_MSTR      2
#define SPI_CR1_BR        3
#define SPI_CR1_SPE       6
#define SPI_CR1_LSBFIRST  7
#define SPI_CR1_SSI       8
#define SPI_CR1_SSM       9
#define SPI_CR1_RXONLY    10
#define SPI_CR1_CRCL      11
#define SPI_CR1_CRCNEXT   12
#define SPI_CR1_CRCEN     13
#define SPI_CR1_BIDIOE    14
#define SPI_CR1_BIDIMODE  15

//SPI control register 2 bit positions

#define SPI_CR2_RXDMAEN      0
#define SPI_CR2_TXDMAEN      1
#define SPI_CR2_SSOE         2
#define SPI_CR2_NSSP         3
#define SPI_CR2_FRF          4
#define SPI_CR2_ERRIE        5
#define SPI_CR2_RXNEIE       6
#define SPI_CR2_TXEIE        7
#define SPI_CR2_DS           8
#define SPI_CR2_FRXTH        12
#define SPI_CR2_LDMA_RX      13
#define SPI_CR2_LDMA_TX      14


// SPI STATUS registers
#define SPI_SR_RXNE        0
#define SPI_SR_TXE         1
#define SPI_SR_CRCERR      4
#define SPI_SR_MODF        5
#define SPI_SR_OVR         6
#define SPI_SR_BSY         7
#define SPI_SR_FRE         8
#define SPI_SR_FRLVL       9
#define SPI_SR_FTLVL       11



/*
 * I2C bit position definitions
 * CR1 register bit definitions
 */

#define I2C_CR1_PE        0
#define I2C_CR1_TXIE      1
#define I2C_CR1_RXIE      2
#define I2C_CR1_ADDRIE    3
#define I2C_CR1_ACKIE     4
#define I2C_CR1_STOPIE    5
#define I2C_CR1_TCIE      6
#define I2C_CR1_ERRIE     7
#define I2C_CR1_DNF       8
#define I2C_CR1_ANFOFF    12
#define I2C_CR1_TXDMAEN   14
#define I2C_CR1_RXDMAEN   15
#define I2C_CR1_SBC       16
#define I2C_CR1_NESTRETCH 17
#define I2C_CR1_GCEN      19
#define I2C_CR1_SMBHEN    20
#define I2C_CR1_SMDHEN    21
#define I2C_CR1_ALERTEN   22
#define I2C_CR1_RECEN     23

//CR2 register definitions

#define I2C_CR2_SADD      0
#define I2C_CR2_RD_WRN    10
#define I2C_CR2_ADD10     11
#define I2C_CR2_HEAD10R   12
#define I2C_CR2_START     13
#define I2C_CR2_STOP      14
#define I2C_CR2_NACK      15
#define I2C_CR2_NBYTES    16
#define I2C_CR2_RELOAD    24
#define I2C_CR2_AUTOEND   25
#define I2C_CR2_RECBYTE   26

//ISR interrupt and status register bit definitions

#define I2C_ISR_TXE       0
#define I2C_ISR_TXIS      1
#define I2C_ISR_RXNE      2
#define I2C_ISR_ADDR      3
#define I2C_ISR_NACKF     4
#define I2C_ISR_STOPF     5
#define I2C_ISR_TC        6
#define I2C_ISR_TCR       7
#define I2C_ISR_BERR      8
#define I2C_ISR_ARLO      9
#define I2C_ISR_OVR       10
#define I2C_ISR_PECER     11
#define I2C_ISR_TIMEOUT   12
#define I2C_ISR_ALERT     13
#define I2C_ISR_BUSY      15
#define I2C_ISR_DIR       16
#define I2C_ISR_ADDCODE   17

//ICR interrupt clear register bit definitons
#define I2C_ICR_ADDRCF    3
#define I2C_ICR_NACKCF    4
#define I2C_ICR_STOPCF    5
#define I2C_ICR_BERRCF    8
#define I2C_ICR_ARLOCF    9
#define I2C_ICR_OVRCF     10
#define I2C_ICR_PECERCF   11
#define I2C_ICR_TIMEOUTCF 12
#define I2C_ICR_ALERTCF   13


//RXDR recieve data register bit definitions
#define I2C_RXDR_RXDATA   0


//TXDR transmit data register bit definitions
#define I2C_TXDR_TXDATA   0

/*
 * USART bit position definitions
 * CR1 register bit definitions
 */

#define USART_CR1_UE       0
#define USART_CR1_RE       2
#define USART_CR1_TE       3
#define USART_CR1_IDLEIE   4
#define USART_CR1_RXNEIE   5
#define USART_CR1_TCIE     6
#define USART_CR1_TXEIE    7
#define USART_CR1_PEIE     8
#define USART_CR1_PS	   9
#define USART_CR1_PCE     10
#define USART_CR1_WAKE    11
#define USART_CR1_M0      12
#define USART_CR1_MME     13
#define USART_CR1_CMIE    14
#define USART_CR1_OVER8   15
#define USART_CR1_DEDT    16
#define USART_CR1_DEAT    21
#define USART_CR1_RTOIE   26
#define USART_CR1_M1      28


/*
 * USART bit position definitions
 * CR2 register bit definitions
 */

#define USART_CR2_ADDM7       6
#define USART_CR2_LBCL        8
#define USART_CR2_CPHA        9
#define USART_CR2_CPOL        10
#define USART_CR2_CLKEN       11
#define USART_CR2_STOP        12
#define USART_CR2_SWAP        15
#define USART_CR2_RXINV       16
#define USART_CR2_TXINV       17
#define USART_CR2_DATAINV     18
#define USART_CR2_MSBFIRST    19
#define USART_CR2_ABREN       20
#define USART_CR2_ABRMOD      21
#define USART_CR2_RTOEN       23
#define USART_CR2_ADD3        24
#define USART_CR2_ADD7        28

/*
 * USART bit position definitions
 * CR3 register bit definitions
 */
#define USART_CR3_CTSIE		  10
#define USART_CR3_CTSE		  9
#define USART_CR3_RTSE        8
#define USART_CR3_EIE         0
/*
 * BRR register bit definitions
 */
#define USART_BRR_BRR         0



/*
 * ISR register bit definitions
 */
#define USART_ISR_PE          0
#define USART_ISR_FE          1
#define USART_ISR_NF          2
#define USART_ISR_ORE         3
#define USART_ISR_IDLE        4
#define USART_ISR_RXNE        5
#define USART_ISR_TC          6
#define USART_ISR_TXE		  7
#define USART_ISR_CTSIF       9
#define USART_ISR_CTS         10
#define USART_ISR_RTOF        11
#define USART_ISR_ABRE		  14
#define USART_ISR_ABRF        15
#define USART_ISR_BUSY        16
#define USART_ISR_CMF         17
#define USART_ISR_SBKF        18
#define USART_ISR_RWU         19
/*
 * ICR register bit definitions
 */
#define USART_ICR_PECF       0
#define USART_ICR_FECF       1
#define USART_ICR_NCF        2
#define USART_ICR_ORECF      3
#define USART_ICR_IDLECF     4
#define USART_ICR_TCCF       6
#define USART_ICR_CTSCF      9
#define USART_ICR_RTOCF      11
#define USART_ICR_CMCF       17


/*
 * RDR register bit definitions
 */
#define USART_RDR_RDR       0

/*
 * TDR register bit definitions
 */
#define USART_TDR_TDR       0






#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define PIN_SET SET
#define PIN_RESET RESET
#define FLAG_RESET RESET
#define FLAG_SET  SET


#include "stm32F0xxx_GPIO_Driver.h"
#include "stm32F0xxx_SPI_Driver.h"
#include "stm32F0xxx_i2c_Driver.h"
#include "stm32F0xxx_UART_Driver.h"
#include "stm32F0xxx_rcc_driver.h"


#endif /* INC_STM32F0XXX_H_ */
