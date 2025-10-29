/*
 * sbusDecode.hpp
 *
 *  Created on: Oct 13, 2025
 *      Author: yuukou
 */

#ifndef INC_SBUSDECODE_HPP_
#define INC_SBUSDECODE_HPP_


#include "main.h"
#include "flight_data.hpp"

void sbus_Decode(flightdata::FlightData* data);

void sbusInterpreter(flightdata::FlightData* data);

void sbusUpdate(flightdata::FlightData* data);

void sbusLostDetecter(flightdata::FlightData* data);

#endif /* INC_SBUSDECODE_HPP_ */
