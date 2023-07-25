/*
 * stm32f407xx_rcc_driver.h
 *
 *  Created on: Jul 19, 2023
 *      Author: mucahit
 */

#ifndef INC_STM32F407XX_RCC_DRIVER_H_
#define INC_STM32F407XX_RCC_DRIVER_H_

#include "stm32f407xx.h"

/* Returns APB1 clock value */
uint32_t RCC_GetPCLK1Value(void);

/* Returns APB2 clock value */
uint32_t RCC_GetPCLK2Value(void);

uint32_t RCC_GetPLLOutputClock(void);



#endif /* INC_STM32F407XX_RCC_DRIVER_H_ */
