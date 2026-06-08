/*
 * stm32_f4xx-gpio_driver.c
 *
 *  Created on: Jun 8, 2026
 *      Author: Aditya
 */

#include "stm32_f4xx_gpio_driver.h"

/**
*
 * @fn			- GPIO_Init
 *
 * @brief		- This function initializes the GPIO port and pin according to the specified parameters in the GPIO_Handle_t structure
 *
 * @param[in]	- pGPIOHandle: pointer to a GPIO_Handle_t structure that contains the configuration information for the specified GPIO pin
 *
 * @return		- none
 *
 * @Note		- none
 */

/*********APIs supported by this driver***********/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    //configure the mode of gpio pin
    uint32_t temp = 0; //temp register
    //1. configure the mode of gpio pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        //non interrupt mode
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
        pGPIOHandle->pGPIOx->MODER |= temp; //setting
    }
    else
    {
        //interrupt mode
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            //1. configure the FTSR
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //clear the corresponding RTSR bit
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
                {
                    //1. configure the RTSR
                    EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                    //clear the corresponding FTSR bit
                    EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                }
                else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
                {
                    //1. configure both FTSR and RTSR
                    EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                    EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                }

                //2. configure the GPIO port selection in SYSCFG_EXTICR
                uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
                uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
                uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
                SYSCFG_PCLK_EN(); //enable the clock for SYSCFG peripheral
                SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);
                //3. enable the EXTI interrupt delivery using IMR
                EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }   

    //2. configure the speed
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
    pGPIOHandle->pGPIOx->OSPEEDR |= temp; //setting             

    //3. configure the pupd settings
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
    pGPIOHandle->pGPIOx->PUPDR |= temp; //setting

    //4. configure the output type
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
    pGPIOHandle->pGPIOx->OTYPER |= temp; //setting      

    //5. configure the alt functionality
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1, temp2;
        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)); //clearing
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2)); //setting
    }   

}   

/*
 * @fn			- GPIO_DeInit
 * @brief		- This function deinitializes the GPIO port
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @return		- none
 * @Note		- none
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if(pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if(pGPIOx == GPIOG)
    {
        GPIOG_REG_RESET();
    }
    else if(pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
}   

/*
 * @fn			- GPIO_PeriClockControl
 * @brief		- This function will control the peripheral clock for a GPIO port
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @param[in]	- EnorDi: enable or disable the clock for the specified GPIO port
 * @return		- none
 * @Note		- none
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if(pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if(pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
    }
    else
    {
        if(pGPIOx == GPIOA)
                {
                    GPIOA_PCLK_DI();
                }
                else if(pGPIOx == GPIOB)
                {
                    GPIOB_PCLK_DI();
                }
                else if(pGPIOx == GPIOC)
                {
                    GPIOC_PCLK_DI();
                }
                else if(pGPIOx == GPIOD)
                {
                    GPIOD_PCLK_DI();
                }
                else if(pGPIOx == GPIOE)
                {
                    GPIOE_PCLK_DI();
                }
                else if(pGPIOx == GPIOF)
                {
                    GPIOF_PCLK_DI();
                }
                else if(pGPIOx == GPIOG)
                {
                    GPIOG_PCLK_DI();
                }
                else if(pGPIOx == GPIOH)
                {
                    GPIOH_PCLK_DI();
                }   
    }   
}       

/*
 * @fn			- GPIO_ReadFromInput
 * @brief		- This function reads the value from the specified GPIO pin
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @param[in]	- PinNumber: the number of the pin to read
 * @return		- the value of the specified GPIO pin
 * @Note		- none
 */
uint8_t GPIO_ReadFromInput(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;
    value = (pGPIOx->IDR >> PinNumber) & 0x1;
    return value;
}   

/*
 * @fn			- GPIO_ReadFromInputPort
 * @brief		- This function reads the value from the specified GPIO port
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @return		- the value of the specified GPIO port
 * @Note		- none
 */
uint32_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return (pGPIOx->IDR);
}

/*
 * @fn			- GPIO_WriteToOutputPin
 * @brief		- This function writes a value to the specified GPIO pin
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @param[in]	- PinNumber: the number of the pin to write to
 * @param[in]	- Value: the value to write to the specified GPIO pin
 * @return		- none
 * @Note		- none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value == GPIO_PIN_SET)
    {
        pGPIOx->BSRR = (1 << PinNumber);
    }
    else
    {
        pGPIOx->BSRR = (1 << (PinNumber + 16));
    }
}

/*
 * @fn			- GPIO_WriteToOutputPort
 * @brief		- This function writes a value to the specified GPIO port
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @param[in]	- Value: the value to write to the specified GPIO port
 * @return		- none
 * @Note		- none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint32_t Value)
{
    pGPIOx->ODR = Value;
}

/*
 * @fn			- GPIO_ToggleOutputPin
 * @brief		- This function toggles the value of the specified GPIO pin
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @param[in]	- PinNumber: the number of the pin to toggle
 * @return		- none
 * @Note		- none
 */ 
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1 << PinNumber);
}   

/*
 * @fn			- GPIO_IRQConfig
 * @brief		- This function configures the interrupt for the specified GPIO pin
 * @param[in]	- IRQNumber: the number of the IRQ to configure
 * @param[in]	- EnorDi: enable or disable the interrupt for the specified IRQ number
 * @return		- none
 * @Note		- none
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        NVIC_EnableIRQ(IRQNumber);
    }
    else
    {
        NVIC_DisableIRQ(IRQNumber);
    }
}

/*
 * @fn			- GPIO_IRQPriorityConfig
 * @brief		- This function configures the priority of the specified IRQ number
 * @param[in]	- IRQNumber: the number of the IRQ to configure
 * @param[in]	- IRQPriority: the priority to set for the specified IRQ number
 * @return		- none
 * @Note		- none
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    NVIC_SetPriority(IRQNumber, IRQPriority);
}

/*
 * @fn			- GPIO_IRQHandling
 * @brief		- This function handles the interrupt for the specified GPIO pin
 * @param[in]	- PinNumber: the number of the pin for which the interrupt occurred
 * @return		- none
 * @Note		- none
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{
    // Implementation for handling GPIO interrupt
}

/*
 * @fn			- GPIO_DeInit
 * @brief		- This function deinitializes the GPIO port
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @return		- none
 * @Note		- none
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    // Implementation for deinitializing GPIO port
}

/*
 * @fn			- GPIO_PeriClockControl
 * @brief		- This function will control the peripheral clock for a GPIO port
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @param[in]	- EnorDi: enable or disable the clock for the specified GPIO port
 * @return		- none
 * @Note		- none
 */ 
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    // Implementation for controlling peripheral clock for GPIO port
}

/*
 * @fn			- GPIO_ReadFromInput
 * @brief		- This function reads the value from the specified GPIO pin
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @param[in]	- PinNumber: the number of the pin to read
 * @return		- the value of the specified GPIO pin
 * @Note		- none
 */
uint8_t GPIO_ReadFromInput(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    // Implementation for reading from input pin
}

/*
 * @fn			- GPIO_ReadFromInputPort
 * @brief		- This function reads the value from the specified GPIO port
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @return		- the value of the specified GPIO port
 * @Note		- none
 */
uint32_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    // Implementation for reading from input port
}

/*
 * @fn			- GPIO_WriteToOutputPin
 * @brief		- This function writes a value to the specified GPIO pin
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @param[in]	- PinNumber: the number of the pin to write to
 * @param[in]	- Value: the value to write to the specified GPIO pin
 * @return		- none
 * @Note		- none
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value == SET)
    {
        pGPIOx->ODR |= (1 << PinNumber);
    }
    else
    {
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}

/*
 * @fn			- GPIO_WriteToOutputPort
 * @brief		- This function writes a value to the specified GPIO port
 * @param[in]	- pGPIOx: pointer to a GPIO_RegDef_t structure
 * @param[in]	- Value: the value to write to the specified GPIO port
 * @return		- none
 * @Note		- none
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint32_t Value)
{
    pGPIOx->ODR = Value;
}
