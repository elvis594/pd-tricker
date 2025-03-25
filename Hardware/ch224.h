//
// Created by Elvis on 2025/1/7.
//

#ifndef PD_TRICKER_HARDWARE_CH224_H_
#define PD_TRICKER_HARDWARE_CH224_H_

#define CH224_CFG1(x) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define CH224_CFG2(x) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define CH224_CFG3(x) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, (x) ? GPIO_PIN_SET : GPIO_PIN_RESET)

void ch224_init(void);
void set_voltage(int voltage);

#endif //PD_TRICKER_HARDWARE_CH224_H_
