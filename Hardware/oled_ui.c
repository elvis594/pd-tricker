//
// Created by Elvis on 2025/2/22.
//

#include "oled_ui.h"
#include "oled.h"
#include "ina226.h"
#include <stdio.h>
#include <string.h>
char str[32];
extern INA226 CC;
extern u8g2_t u8g2;
void Static_UI(void) {

	u8g2_ClearBuffer(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_7x13_tr);
	u8g2_DrawStr(&u8g2, 25, 10, "PD Trigger");

	u8g2_DrawLine(&u8g2, 0, 12, 128, 12);

	sprintf(str, "Voltage : %.2f V", CC.voltage);
	u8g2_DrawStr(&u8g2, 0, 26, str);
	u8g2_SendBuffer(&u8g2);


}

void flash_ui(void){
	u8g2_ClearBuffer(&u8g2);
	u8g2_DrawStr(&u8g2, 25, 10, "PD Trigger");
	u8g2_DrawLine(&u8g2, 0, 12, 128, 12);
	sprintf(str, "Voltage : %.2f V", CC.voltage);
	u8g2_DrawStr(&u8g2, 0, 26, str);
	sprintf(str, "Current : %.2f A", CC.current);
	u8g2_DrawStr(&u8g2, 0, 40, str);
// 6. 显示功率
	sprintf(str, "Power   : %.2f W", CC.power);
	u8g2_DrawStr(&u8g2, 0, 54, str);
	u8g2_SendBuffer(&u8g2);

}