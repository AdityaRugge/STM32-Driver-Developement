/*
 * stm32_f4xx.h
 *
 *  Created on: Apr 12, 2026
 *      Author: Aditya
 */

#ifndef INC_STM32_F4XX_H_
#define INC_STM32_F4XX_H_

/*
 * base address of flash and SRAM Memories (memorymap from from datasheet)
*/

#define FLASH_BASEADDR		0x08000000U
#define SRAM1_BASEADDR		0x20000000U
#define SRAM2_BASEADDR		0x2001C000U
#define ROM_BASEADDR		0x1FFF0000U   //system memory
#define SRAM				SRAM1_BASEADDR

/*
 * AHB and APBx Bus peripheral base address
 * */
#define PERIPH_BASE			0x40000000U
#define APB1PERIPH_BASEADDR PERIPH_BASE
#define APB2PERIPH_BASEADDR 0x40010000U
#define AHB1PERIPH_BASEADDR 0x40020000U
#define AHB2PERIPH_BASEADDR 0x50000000U

/*
 * Bus addr of peripheral which is hanging on bus AHB1 bus
 * */
#define GPIOA_BASEADDR		(AHB1PHRIPH_BASE + 0x0000)
#define GPIOB_BASEADDR		(AHB1PHRIPH_BASE + 0x0400)
#define GPIOC_BASEADDR		(AHB1PHRIPH_BASE + 0x0800)
#define GPIOD_BASEADDR		(AHB1PHRIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR		(AHB1PHRIPH_BASE + 0x1000)
#define GPIOF_BASEADDR		(AHB1PHRIPH_BASE + 0x1400)
#define GPIOG_BASEADDR		(AHB1PHRIPH_BASE + 0x1800)
#define GPIOH_BASEADDR		(AHB1PHRIPH_BASE + 0x1C00)

#define RCC_BASEADDR		(AHB1PHRIPH_BASE + 0x3800)



/*
 * Bus addr of peripheral which is hanging on bus APB1 bus
 * */
#define SPI3_BASEADDR		(APB1PERIPH_BASEADDR + 0x3C00)
#define SPI2_BASEADDR		(APB1PERIPH_BASEADDR + 0x3800)

#define USART2_BASEADDR		(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR		(APB1PERIPH_BASEADDR + 0x4800)
#define UART4_BASEADDR		(APB1PERIPH_BASEADDR + 0x4C00)
#define UART5_BASEADDR		(APB1PERIPH_BASEADDR + 0x5000)

#define I2C1_BASEADDR		(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR		(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR		(APB1PERIPH_BASEADDR + 0x5C00)

#define CAN1_BASEADDR		(APB1PERIPH_BASEADDR + 0x6400)
#define CAN2_BASEADDR		(APB1PERIPH_BASEADDR + 0x6800)

#define DAC_BASEADDR		(APB1PERIPH_BASEADDR + 0x7400)

/*
 * Bus addr of peripheral which is hanging on bus APB2 bus
 * */
#define SP1_BASEADDR		(APB2PERIPH_BASEADDR + 0x3000)

#define USART1_BASEADDR		(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR		(APB2PERIPH_BASEADDR + 0x1400)

#define EXTI_BASEADDR		(APB2PERIPH_BASEADDR + 0x3C00)
#define SYSCFG_BASEADDR		(APB2PERIPH_BASEADDR + 0x3800)

/* Pheripheral register definition structure*/  //reference manual : 7.4.11 GPIO register map
typedef struct
{
	volatile uint32_t MODER;    //GPIO port mode register
	volatile uint32_t OTYPER;   //GPIO port output type register
	volatile uint32_t OSPEEDR;  //GPIO port output speed register
	volatile uint32_t PUPDR;	//GPIO port pull-up/pull-down register
	volatile uint32_t IDR;		//GPIO port input data register
	volatile uint32_t ODR;		//GPIO port output data register
	volatile uint32_t BSRR;		//GPIO port bit set/reset register
	volatile uint32_t LCKR;		//GPIO port configuration lock register
	volatile uint32_t AFR[2];   //GPIO alternate function low/high registerAFRL or AFRH
}GPIO_RegDef_t;

/*
 * Peripheral register definition structure for RCC
*/
typedef struct
{
	volatile uint32_t CR;		//  offset 0x00
	volatile uint32_t PLL_CFGR; // 0x04
	volatile uint32_t CFGR;	//  0x08
	volatile uint32_t CIR;		//	0x0c
	volatile uint32_t AHB1_RSTR; // 0x10 etc
	volatile uint32_t AHB2_RSTR;
	volatile uint32_t AHB3_RSTR;
	volatile uint32_t RESERVED;
	volatile uint32_t APB1_RSTR;
	volatile uint32_t APB2_RSTR;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
}RCC_RegDef_t;


/*
 * peripheral definition : bus address tycasted to xx_RegDef_t
 * */
#define GPIOA 		((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB 		((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC 		((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD 		((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE 		((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF 		((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG 		((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH 		((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC 		((RCC_RegDef_t*)RCC_BASEADDR)

/*Clk enable macros for GPIO peripherals  (RCC_AHB1ENR) */
#define GPIOA_PCLK_EN()	(RCC->AHB1ENR |= (1 << 0))    //turn on 0'th bit : Control the bit for clk of GPIO A
#define GPIOB_PCLK_EN()	(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()	(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()	(RCC->AHB1ENR |= (1 << 3)) 
#define GPIOE_PCLK_EN()	(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()	(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()	(RCC->AHB1ENR |= (1 << 6))

/*Clk enable macros for SPIx peripherals*/
#define SPI1_PCLK_EN()	(RCC->AHB1ENR |= (1 << 12))   // Present on RCC_AHB2ENR
#define SPI2_PCLK_EN()	(RCC->AHB1ENR |= (1 << 14))   // Present on RCC_AHB1ENR
#define SPI3_PCLK_EN()	(RCC->AHB1ENR |= (1 << 15))   // Present on RCC_AHB1ENR
#define SPI4_PCLK_EN()	(RCC->AHB1ENR |= (1 << 13))   // Present on RCC_AHB2ENR

/*Clk enable macros for I2Cx peripherals  (RCC_APB1ENR) */
#define I2C1_PCLK_EN()	(RCC->AHB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()	(RCC->AHB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()	(RCC->AHB1ENR |= (1 << 23))

/*Clk enable macros for USARTx peripherals  (RCC_APB1ENR) */
#define USART1_PCLK_EN()	(RCC->AHB2ENR |= (1 << 4))
#define USART2_PCLK_EN()	(RCC->AHB1ENR |= (1 << 17))
#define USART3_PCLK_EN()	(RCC->AHB1ENR |= (1 << 18))
#define USART4_PCLK_EN()	(RCC->AHB1ENR |= (1 << 19))
#define USART5_PCLK_EN()	(RCC->AHB1ENR |= (1 << 20))
#define USART6_PCLK_EN()	(RCC->AHB1ENR |= (1 << 5))

/*Clk enable macros for SYSCFGx peripherals  (RCC_APB2ENR) */
#define SYSCFG_PCLK_EN()	(RCC->AHB2ENR |= (1 << 14))


/*----------------------------------- Clk Disable-------------------------------------------------- */

/* clk disable macro for GPIOx peripherals*/
#define GPIOA_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 0))    //turn off 0'th bit : Control the bit for clk of GPIO A
#define GPIOB_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 3)) 
#define GPIOE_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 6))

/*Clk disable macros for SPIx peripherals*/
#define SPI1_PCLK_DI()	(RCC->AHB2ENR &= ~ (1 << 12))   // Present on RCC_AHB2ENR
#define SPI2_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 14))   // Present on RCC_AHB1ENR
#define SPI3_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 15))   // Present on RCC_AHB1ENR
#define SPI4_PCLK_DI()	(RCC->AHB2ENR &= ~  (1 << 13))  

/*Clk disable macros for I2Cx peripherals  (RCC_APB1ENR) */
#define I2C1_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 21))
#define I2C2_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 22))
#define I2C3_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 23))

/*Clk disable macros for USARTx peripherals  (RCC_APB1ENR) */
#define USART1_PCLK_DI()	(RCC->AHB2ENR &= ~ (1 << 4))
#define USART2_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 17))
#define USART3_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 18))
#define USART4_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 19))
#define USART5_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 20))
#define USART6_PCLK_DI()	(RCC->AHB1ENR &= ~ (1 << 5))

/*Clk disable macros for SYSCFGx peripherals  (RCC_APB2ENR) */
#define SYSCFG_PCLK_DI()	(RCC->AHB2ENR &= ~ (1 << 14))

#endif /* INC_STM32_F4XX_H_ */
