//
// Created by Elvis on 2025/1/7.
//

#include "ina226.h"
#include "i2c.h"

void delay_nms(uint16_t ms)
{
	uint16_t i = 0;
	uint32_t M = 0;
	for (i = 0; i < ms; i++)
		for (M=12000;M>0;M--);
}
void INA226_IIC_Init()
{
	I2C_Init();
}

void INA226_WriteRegister(uint8_t addr, uint8_t reg, uint16_t value) {
	I2C_Start();
	I2C_SendByte(addr << 1); // **发送设备地址 (写)**
	I2C_WaitAck();
	I2C_SendByte(reg);        // **发送寄存器地址**
	I2C_WaitAck();
	I2C_SendByte(value >> 8); // **发送高字节**
	I2C_WaitAck();
	I2C_SendByte(value & 0xFF); // **发送低字节**
	I2C_WaitAck();
	I2C_Stop();
}

uint16_t INA226_ReadRegister(uint8_t addr, uint8_t reg) {
	uint16_t data = 0;

	I2C_Start();
	I2C_SendByte(addr << 1);  // 发送 7-bit 地址 + 写
	I2C_WaitAck();
	I2C_SendByte(reg);        // 发送寄存器地址
	I2C_WaitAck();
	I2C_Start();              // 重新启动
	I2C_SendByte((addr << 1) | 1); // 发送 7-bit 地址 + 读
	I2C_WaitAck();
	data = I2C_ReadByte(1) << 8;  // 读取高字节
	I2C_WaitAck();
	data |= I2C_ReadByte(0);      // 读取低字节
	I2C_WaitAck();
	I2C_Stop();

	return data;
}

void INA226_Init(void)
{
	INA226_IIC_Init();

	delay_nms(10);
	INA226_WriteRegister(INA226_ADDR,0x00,0x4727);//初始化结果采用64次平均值，全功能，连续模式
	INA226_WriteRegister(INA226_ADDR,0x05,0x200);//（当单位为mA时：0.002R=0xA00;0.01R=0x200）;(上限8A)

}

void INA226_SetRegPointer(uint8_t addr,uint8_t reg)
{
	I2C_Start();
	I2C_SendByte(addr);
	I2C_WaitAck();
	I2C_SendByte(reg);
	I2C_WaitAck();
	I2C_Stop();
}

uint16_t INA226_GetShuntCurrent()
{
	return INA226_ReadRegister(INA226_ADDR,Current_Reg);
}

//获取 id
uint16_t  INA226_Get_ID()
{
	return INA226_ReadRegister(INA226_ADDR, ID_Reg);
}

//获取校准值
uint16_t INA226_GET_CAL_REG()
{
	return INA226_ReadRegister(INA226_ADDR, Calib_Reg);
}

//1.25mV/bit
uint16_t INA226_GetVoltage()
{
	return INA226_ReadRegister(INA226_ADDR, Bus_V_Reg);
}

//2.5uV/bit
uint16_t INA226_GetShuntVoltage()
{
	uint16_t temp = 0;
	temp = INA226_ReadRegister(INA226_ADDR,Shunt_V_Reg);
	if (temp&0x8000) temp = ~(temp-1);
	return temp;
}

//2.5mW/bit
uint16_t INA226_Get_Power()
{
	return INA226_ReadRegister(INA226_ADDR, Power_Reg);
}
