/*
 * preArmState.cpp
 *
 *  Created on: Sep 29, 2025
 *      Author: yuukou
 */

#include "flight_data.hpp"
#include "stdio.h"
#include "cstdint"

//preArm 時に呼ばれる
void preArmState(flightdata::FlightData* data){


	printf("pre arm state \r\n");
	HAL_Delay(1000);

	while(data->current_state != (uint8_t)flightdata::state::pre_flight_state){

		data->current_state = (uint8_t)flightdata::state::pre_flight_state;
		HAL_Delay(50);
	}


}

