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
}GPIO_PinConfig_t

/*handle structure for a GPIO pins*/

typedef struct
{
	GPIO_RegDef_t *pGPIOx; //this holds base addr of the gpio port to which the pin belongs
	GPIO_PinConfig_t GPIO_PinConfig; // this holds pin config setting

}GPIO_Handle_t

#endif /* STM32_F4XX_GPIO_DRIVER_H_ */
