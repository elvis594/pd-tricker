//
// Created by Elvis on 2025/1/7.
//

#include "ch224.h"
#include "stm32f1xx_hal.h"

void ch224_init()
{
	//默认5V
	set_voltage(5);
}
// 设定电压
void set_voltage(int voltage) {
	if (voltage == 5) {
		CH224_CFG1(1);
		CH224_CFG2(0);
		CH224_CFG3(0);
	} else if (voltage == 9) {
		CH224_CFG1(0);
		CH224_CFG2(0);
		CH224_CFG3(0);
	} else if (voltage == 12) {
		CH224_CFG1(0);
		CH224_CFG2(0);
		CH224_CFG3(1);
	} else if (voltage == 20) {
		CH224_CFG1(0);
		CH224_CFG2(1);
		CH224_CFG3(0);
	}
}