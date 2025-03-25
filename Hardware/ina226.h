//
// Created by Elvis on 2025/1/7.
//

#ifndef PD_TRICKER_HARDWARE_INA226_H_
#define PD_TRICKER_HARDWARE_INA226_H_

#include "stm32f1xx_hal.h"

#define INA226_ADDR 	  0x40

#define Config_Reg        0x00		//模式配置寄存器
#define Shunt_V_Reg       0x01		//采样电阻压差；取值：2.5uV~81.92mV(0~7FFF)(10mΩ采样电阻下最大电流8A)
#define Bus_V_Reg         0x02		//BUS总线电压：1.25mV~40.96V(0~7FFF)
#define Power_Reg         0x03		//功率；Current_LSB * 25，FSR = 0xFFFF
#define Current_Reg       0x04		//电流；LSB = 0.02mA，FSR = 0x7FFF
#define Calib_Reg         0x05		//（当单位为mA时：采样电阻0.002R=0xA00;0.01R=0x200）；写入Calibration Register的数据需要根据实际电路中的采样电阻阻值以及电流分辨率来设置
#define Mask_En_Reg       0x06		//
#define Alert_Reg         0x07		//
#define Man_ID_Reg        0xFE  	//0x5449
#define ID_Reg            0xFF  	//0x2260

typedef struct {
	float voltage;
	unsigned char current_signed;//电流方向
	float current;
	float power;
	uint32_t TestTime;
	uint32_t capacity;
	uint32_t id;
}INA226;
extern INA226 CC;

void INA226_Init(void);
void INA226_SendData(uint8_t addr,uint8_t reg,uint16_t data);
void INA226_SetRegPointer(uint8_t addr,uint8_t reg);
uint16_t INA226_ReadData(uint8_t addr);
uint16_t INA226_Get_ID();
uint16_t INA226_GetShuntVoltage();
uint16_t INA226_GetShuntCurrent();
uint16_t INA226_GetVoltage();
uint16_t INA226_Get_Power();
uint16_t INA226_GET_CAL_REG();

#endif //PD_TRICKER_HARDWARE_INA226_H_
