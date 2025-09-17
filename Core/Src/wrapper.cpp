#include "wrapper.hpp"
#include "gpio.h"
#include <stdio.h>


void init(){

	printf("ProgramStart\n");

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);

	HAL_Delay(1000);
}

void loop(){

	static uint32_t count = 0;

	printf("count: %d\n", count++);

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);

	HAL_Delay(1000);
}
