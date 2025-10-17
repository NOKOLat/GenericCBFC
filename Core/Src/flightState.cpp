/*
 * flightState.cpp
 *
 *  Created on: Sep 29, 2025
 *      Author: yuukou
 */

#include "stdio.h"
#include "flight_data.hpp"

//flight 時に呼ばれる
void flightState(flightdata::FlightData* data){

		printf("flight state \r\n");
		HAL_Delay(1000);

		while(data->current_state != flightdata::State::DISARM_STATE){
			data->current_state = flightdata::State::DISARM_STATE;
			HAL_Delay(50);
		}

}
