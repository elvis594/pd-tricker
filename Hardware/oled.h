
#ifndef OLED_H
#define  OLED_H

#include "u8g2/u8g2.h"
#include "u8g2/u8x8.h"

#define OLED_ADDRESS 0x78

void u8g2_init(u8g2_t *u8g2);
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay_hal(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#endif
