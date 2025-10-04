/*
 * disArmState.cpp
 *
 *  Created on: Sep 29, 2025
 *      Author: yuukou
 */

#include "main.h"
#include "stdio.h"
#include "flight_data.hpp"

//disArm 時に呼ばれる
void disArmState(flightdata::FlightData* data){

		printf("disarm state \r\n");
		HAL_Delay(1000);

		while(data->current_state != (uint8_t)flightdata::state::pre_arm_state){

				data->current_state = (uint8_t)flightdata::state::pre_arm_state;
				HAL_Delay(50);
		}

}
