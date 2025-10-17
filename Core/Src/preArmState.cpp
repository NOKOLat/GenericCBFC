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

	while(data->current_state != flightdata::State::PRE_FLIGHT_STATE){

		data->current_state = flightdata::State::PRE_FLIGHT_STATE;
		HAL_Delay(50);
	}


}

