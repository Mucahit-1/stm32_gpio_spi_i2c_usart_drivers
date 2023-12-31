/*
 * stm32f407xx_i2c_driver1.h
 *
 *  Created on: Jul 17, 2023
 *      Author: mucahit
 */

#ifndef SRC_STM32F407XX_I2C_DRIVER_H_
#define SRC_STM32F407XX_I2C_DRIVER_H_

#include "stm32f407xx.h"

// configuration structure for I2C peripheral
typedef struct{

	uint8_t I2C_SCLSpeed;                   // possible values from @I2C_SCLSpeed
	uint8_t I2C_DeviceAddress;              // the value will initialize by user
	uint8_t I2C_ACKControl;                 // possible values from @I2C_ACKControl
	uint8_t I2C_FMDutyCycle;                // possible values from @I2C_FMDutyCycle

}I2C_Config_t;



//this is a handle structure for I2cx

typedef struct{

	I2C_RegDef_t *pI2Cx;              // this holds the base address of the I2Cx
	I2C_Config_t I2C_Config;          // this holds I2C configuration settings
	uint8_t  *pTxBuffer;
	uint8_t  *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxRxState;
	uint8_t SlaveAddr;
	uint32_t RxSize;
	uint8_t Sr;


}I2C_Handle_t;



// I2C application state

#define I2C_READY            0
#define I2C_BUSY_IN_TX       1
#define I2C_BUSY_IN_RX       2



// @I2C_SCLSpeed

#define I2C_SLC_SPEED_SM       100000 // standard mode 100KHz
#define I2C_SLC_SPEED_FM       400000 // fast mode 400KHz



// @I2C_ACKControl

// we took this possible values from CR1 register
#define I2C_ACK_ENABLE      1
#define I2C_ACK_DISABLE     0


//  @I2C_FMDutyCycle

// we took this possible values from CCR register
#define I2C_FM_DUTY_2       0
#define I2C_FM_DUTY_16_9    1

// I2C related status flag definition

#define I2C_FLAG_TXE           ( 1 << I2C_SR1_TxE )
#define I2C_FLAG_RXNE          ( 1 << I2C_SR1_RxNE )
#define I2C_FLAG_SB            ( 1 << I2C_SR1_SB )
#define I2C_FLAG_ADDR          ( 1 << I2C_SR1_ADDR )
#define I2C_FLAG_BTF           ( 1 << I2C_SR1_BTF )
#define I2C_FLAG_ADD10         ( 1 << I2C_SR1_ADD10 )
#define I2C_FLAG_STOPF         ( 1 << I2C_SR1_STOPF )
#define I2C_FLAG_BERR          ( 1 << I2C_SR1_BERR )
#define I2C_FLAG_ARLO          ( 1 << I2C_SR1_ARLO )
#define I2C_FLAG_AF            ( 1 << I2C_SR1_AF )
#define I2C_FLAG_OVR           ( 1 << I2C_SR1_OVR )
#define I2C_FLAG_BUSY          ( 1 << SPI_SR_BSY )
#define I2C_FLAG_PECEER        ( 1 << I2C_SR1_PECERR )
#define I2C_FLAG_TIMEOUT       ( 1 << I2C_SR1_TIMEOUT )
#define I2C_FLAG_SMBALERT      ( 1 << I2C_SR1_SMBALERT )


#define I2C_DISABLE_REAPETEDS   RESET
#define I2C_ENABLE_REAPETEDS   SET


// I2C application event macros

#define I2C_EV_TX_CMPLT             0
#define I2C_EV_RX_CMPLT             1
#define I2C_EV_STOP                 2
#define I2C_ERROR_BERR              3
#define I2C_ERROR_ARLO              4
#define I2C_ERROR_AF                5
#define I2C_ERROR_OVR               6
#define I2C_ERROR_TIMEOUT           7
#define I2C_EV_DATA_REQ             8
#define I2C_EV_DATA_RCV             9

/***************************************************************************************
 *                          APIs supported by this I2C driver
 ***************************************************************************************/

//peripheral clock setup
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx , uint8_t EnorDi);


//init and de-init
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);



// Data send and receive

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle , uint8_t *pTxbuffer , uint32_t Len , uint8_t slaveAdrress , uint8_t sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle , uint8_t *pRxbuffer , uint32_t Len , uint8_t slaveAdrress , uint8_t sr);

//here the functions type is uint8_t because here we return the application state
uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle , uint8_t *pTxbuffer , uint32_t Len , uint8_t slaveAdrress , uint8_t sr);
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle , uint8_t *pRxbuffer , uint32_t Len , uint8_t slaveAdrress , uint8_t sr);



void I2C_SlaveSendData(I2C_RegDef_t *pI2Cx , uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2Cx);


void I2C_CloseReceiveData(I2C_Handle_t *pI2CHandle);
void I2C_CloseSendData(I2C_Handle_t *pI2CHandle);



// IRQ configuration and ISR handling

void I2C_IRQInterruptConfig(uint8_t IRQNumber , uint8_t EnorDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber  , uint32_t IRQPriority);
void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);
void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle);

// other peripheral control APIs

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx , uint8_t EnorDi);
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName);

void I2C_SlaveEnableDisableCallBackEvent(I2C_RegDef_t *pI2Cx , uint8_t EnorDi);

//application call back

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle ,uint8_t AppEv);




#endif /* SRC_STM32F407XX_I2C_DRIVER_H_ */
