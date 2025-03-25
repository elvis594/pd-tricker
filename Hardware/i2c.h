//
// Created by Elvis on 2025/3/6.
//

#ifndef PD_TRICKER_HARDWARE_I2C_H_
#define PD_TRICKER_HARDWARE_I2C_H_

#include <stdlib.h>
#include <stdio.h>
#include "main.h"


/* Private typedef -----------------------------------------------------------*/

/*
   I2C IO port
*/
#define RCC_I2C_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()

#define GPIO_PORT_I2C              GPIOB
#define I2C_SCL_PIN                GPIO_PIN_8
#define I2C_SDA_PIN                GPIO_PIN_9


#define I2C_SCL_1()                HAL_GPIO_WritePin(GPIO_PORT_I2C, I2C_SCL_PIN, GPIO_PIN_SET)             /* SCL = 1 */
#define I2C_SCL_0()                HAL_GPIO_WritePin( GPIO_PORT_I2C, I2C_SCL_PIN, GPIO_PIN_RESET)          /* SCL = 0 */

#define I2C_SDA_1()                HAL_GPIO_WritePin( GPIO_PORT_I2C, I2C_SDA_PIN, GPIO_PIN_SET)            /* SDA = 1 */
#define I2C_SDA_0()                HAL_GPIO_WritePin( GPIO_PORT_I2C, I2C_SDA_PIN, GPIO_PIN_RESET)          /* SDA = 0 */

#define I2C_SDA_READ()             ((GPIO_PORT_I2C->IDR & I2C_SDA_PIN) != 0)                               /* read SDA status */
#define I2C_SCL_READ()             ((GPIO_PORT_I2C->IDR & I2C_SCL_PIN) != 0)                               /* read SCLs tatus */

/* Private define ------------------------------------------------------------*/
#define I2C_WR                      0   /* Writing bit */
#define I2C_RD                      1   /* read bit */

// measurement i2c status
typedef enum{
	I2C_OK = 0,
	I2C_FAIL = 1,
}i2c_TypeDef;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);

void I2C_SendByte(uint8_t _ucByte);
uint8_t I2C_ReadByte(uint8_t ack);
i2c_TypeDef I2C_WaitAck();

void I2C_Ack(void);
void I2C_NAck(void);

i2c_TypeDef i2c_CheckDevice(uint8_t _Address);

#endif //PD_TRICKER_HARDWARE_I2C_H_
