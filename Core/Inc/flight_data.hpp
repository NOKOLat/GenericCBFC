/*
 * flight_data.hpp
 *
 *  Created on: Sep 29, 2025
 *      Author: yuukou
 */

#ifndef INC_FLIGHT_DATA_HPP_
#define INC_FLIGHT_DATA_HPP_

#include "main.h"
#include "cstdint"
#include "usart.h"
#include "stdio.h"

struct flightdata {


	enum class State : uint8_t{

		PRE_ARM_STATE,
		PRE_FLIGHT_STATE,
		FLIGHT_STATE,
		DISARM_STATE,
		FAILSAFE_STATE,
	};


	struct FlightData {

		  State current_state;

		  uint16_t sbus_channel_data[10];
		  uint8_t receive_buffer[25] = {};

		  uint32_t sbus_lost_count = 0;
		  bool sbus_lost_connection = false;
		  bool sbus_failsafe_bit = false;

		  bool arm_on = false;
		  bool flight_on = false;

		  bool switch_flag = false;

		  float accel[3];
		  float gyro[3];
		  float mag[3];
		  float angle[3];
		  float rate[3];
		  float pid_result[3];
		  uint16_t motor_pwm[4];
		  uint16_t servo_pwm[2];
		};



	enum class SbusChannel : uint8_t {

		  throttle = 3 - 1,
		  pitch = 2 - 1,
		  roll = 1 - 1,
		  yaw = 4 - 1,
		  arm = 6 - 1,
		  fly = 5 - 1,
		  drop = 7 - 1,
		  autodrop = 8 - 1,
	};

};

extern flightdata::FlightData flightdata;


#endif /* INC_FLIGHT_DATA_HPP_ */
