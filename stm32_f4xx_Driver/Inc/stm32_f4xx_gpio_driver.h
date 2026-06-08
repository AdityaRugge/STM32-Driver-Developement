/*
 * stm32_f4xx_gpio_driver.h
 *
 *  Created on: Jun 8, 2026
 *      Author: Aditya
 */

#ifndef STM32_F4XX_GPIO_DRIVER_H_
#define STM32_F4XX_GPIO_DRIVER_H_

#include "stm32_f4xx.h"

/*handle config structure for a GPIO pins*/
typedef struct
{
	uint8_t GPIO_PinNumber; //this holds base addr of the gpio port to which the pin belongs
	uint8_t GPIO_PinMode; // this holds pin config setting
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

/*handle structure for a GPIO pins*/

typedef struct
{
	GPIO_RegDef_t *pGPIOx; //this holds base addr of the gpio port to which the pin belongs
	GPIO_PinConfig_t GPIO_PinConfig; // this holds pin config setting

}GPIO_Handle_t;

/*********APIs supported by this driver***********/	
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*This function will control the peripheral clock for a GPIO port*/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*This function will read from input pin*/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

/*This function will write to output pin*/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);

/*This function will toggle the output pin*/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

//IRQ Configuration and ISR handling
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);


#endif /* STM32_F4XX_GPIO_DRIVER_H_ */
