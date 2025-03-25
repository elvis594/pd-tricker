//
// Created by Elvis on 2025/1/7.
//

#include "key.h"
#include "stm32f1xx_hal.h"

#define KEY_COUNT   2  // 按键数量
#define NO_KEY      0  // 未检测到按键

typedef struct {
	GPIO_TypeDef* port;  // GPIO 端口
	uint16_t pin;        // GPIO 引脚
	char key_val;        // 返回的按键值
} KeyInfo;

// 定义多个按键信息
KeyInfo keys[KEY_COUNT] = {
	{GPIOB, GPIO_PIN_3, 'A'},
	{GPIOA, GPIO_PIN_15, 'B'}
};

void key_init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();  // 使能 GPIOA 时钟

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;   // 使用内部上拉
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	for (int i = 0; i < KEY_COUNT; i++)
	{
		GPIO_InitStruct.Pin = keys[i].pin;
		HAL_GPIO_Init(keys[i].port, &GPIO_InitStruct);
	}
}


// 通用按键扫描函数
char key_scan(void)
{
	for (int i = 0; i < KEY_COUNT; i++)
	{
		if (HAL_GPIO_ReadPin(keys[i].port, keys[i].pin) == GPIO_PIN_RESET)
		{
			HAL_Delay(10); // 消抖
			if (HAL_GPIO_ReadPin(keys[i].port, keys[i].pin) == GPIO_PIN_RESET)
			{
				while (HAL_GPIO_ReadPin(keys[i].port, keys[i].pin) == GPIO_PIN_RESET); // 等待释放
				return keys[i].key_val; // 返回按键值
			}
		}
	}
	return NO_KEY;
}
