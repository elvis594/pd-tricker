#include "oled.h"
#include "i2c.h"
extern I2C_HandleTypeDef hi2c1;

void u8g2_init(u8g2_t *u8g2) {
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(
		u8g2,
		U8G2_R0,
		u8x8_byte_hw_i2c,
		u8x8_gpio_and_delay_hal
	);
	u8x8_SetI2CAddress(&u8g2->u8x8, 0x78); // I2C 地址，通常为 0x78 或 0x7A
	u8g2_InitDisplay(u8g2);
	u8g2_SetPowerSave(u8g2, 0);

	u8g2_SetFont(u8g2, u8g2_font_8x13B_tr);
}

uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
	static uint8_t buffer[128];
	static uint8_t buf_idx;
	uint8_t *data;

	switch (msg)
	{
		case U8X8_MSG_BYTE_INIT:
		{
			/* add your custom code to init i2c subsystem */
		}
			break;

		case U8X8_MSG_BYTE_START_TRANSFER:
		{
			buf_idx = 0;
		}
			break;

		case U8X8_MSG_BYTE_SEND:
		{
			data = (uint8_t *)arg_ptr;

			while (arg_int > 0)
			{
				buffer[buf_idx++] = *data;
				data++;
				arg_int--;
			}
		}
			break;

		case U8X8_MSG_BYTE_END_TRANSFER:
		{
			if (HAL_I2C_Master_Transmit(&hi2c1, (OLED_ADDRESS), buffer, buf_idx, 1000) != HAL_OK)
				return 0;
		}
			break;

		case U8X8_MSG_BYTE_SET_DC:
			break;

		default:
			return 0;
	}

	return 1;
}

uint8_t u8x8_gpio_and_delay_hal(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
	switch(msg) {
		case U8X8_MSG_DELAY_MILLI:
			HAL_Delay(arg_int);
			break;

		case U8X8_MSG_DELAY_10MICRO:
		case U8X8_MSG_DELAY_100NANO:
		case U8X8_MSG_DELAY_I2C:
			// 不处理或用 __NOP()，因为硬件 I2C 不需要延时
			break;

		case U8X8_MSG_GPIO_AND_DELAY_INIT:
			// 可选：初始化 RESET 引脚
			break;

		case U8X8_MSG_GPIO_RESET:
			// 如果你连了 RESET 引脚，这里控制它；否则跳过
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, arg_int ? GPIO_PIN_SET : GPIO_PIN_RESET);
			break;

		default:
			u8x8_SetGPIOResult(u8x8, 1);
			break;
	}
	return 1;
}


