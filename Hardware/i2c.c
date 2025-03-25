//
// Created by Elvis on 2025/3/6.
//

#include "I2C.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void  board_I2CInit( void )
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	RCC_I2C_CLK_ENABLE();

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = I2C_SCL_PIN|I2C_SDA_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStruct);
}

void I2C_Delay(void)
{
	uint8_t i;
	for (i = 0; i < 30; i++);
}

void I2C_Init(void)
{
	board_I2CInit();  /* I2C port init */
	I2C_Stop();
}

void I2C_Start(void)
{
	I2C_SDA_1();
	I2C_SCL_1();
	I2C_Delay();
	I2C_SDA_0();
	I2C_Delay();
	I2C_SCL_0();
	I2C_Delay();
}


void I2C_Stop(void)
{
	I2C_SDA_0();
	I2C_SCL_1();
	I2C_Delay();
	I2C_SDA_1();
}

void I2C_SendByte(uint8_t _ucByte)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			I2C_SDA_1();
		}
		else
		{
			I2C_SDA_0();
		}
		I2C_Delay();
		I2C_SCL_1();
		I2C_Delay();
		I2C_SCL_0();
		if (i == 7)
		{
			I2C_SDA_1();
		}
		_ucByte <<= 1;
		I2C_Delay();
	}
}


uint8_t I2C_ReadByte(unsigned char ack)
{
	uint8_t i;
	uint8_t value;

	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		I2C_SCL_1();
		I2C_Delay();
		if (I2C_SDA_READ())
		{
			value++;
		}
		I2C_SCL_0();
		I2C_Delay();
	} if (!ack){
		I2C_NAck();
	} else{
		I2C_Ack();
	}

	return value;
}

/**
  * @brief  wait for I2C ack.
* @retval result:
  */
i2c_TypeDef I2C_WaitAck(void)
{
	i2c_TypeDef set = I2C_OK;

	I2C_SDA_1();
	I2C_Delay();
	I2C_SCL_1();
	I2C_Delay();

	if (I2C_SDA_READ())
	{
		set = I2C_FAIL;
	}

	I2C_SCL_0();
	I2C_Delay();

	return set;
}

void I2C_Ack(void)
{
	I2C_SDA_0();
	I2C_Delay();
	I2C_SCL_1();
	I2C_Delay();
	I2C_SCL_0();
	I2C_Delay();
	I2C_SDA_1();
}


void I2C_NAck(void)
{
	I2C_SDA_1();
	I2C_Delay();
	I2C_SCL_1();
	I2C_Delay();
	I2C_SCL_0();
	I2C_Delay();
}

i2c_TypeDef I2C_CheckDevice(uint8_t _Address)
{
	i2c_TypeDef ucAck = I2C_FAIL;

	if (I2C_SDA_READ() && I2C_SCL_READ())
	{
		I2C_Start();

		I2C_SendByte(_Address | I2C_WR);
		ucAck = I2C_WaitAck();

		I2C_Stop();
	}

	return ucAck;
}

/* End of this file */
