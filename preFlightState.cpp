/*
 * preFlightState.cpp
 *
 *  Created on: Sep 29, 2025
 *      Author: yuukou
 */

#include "flight_data.hpp"
#include "stdio.h"
#include "cstdint"

//preFlight 時に呼ばれる
void preFlightState(flightdata::FlightData* data){

		printf("pre flight state \r\n");
		HAL_Delay(1000);

		while(data->current_state != (uint8_t)flightdata::state::flight_state){

			data->current_state = (uint8_t)flightdata::state::flight_state;
			HAL_Delay(50);
		}

}
