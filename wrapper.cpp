//基本機能
#include "wrapper.hpp"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"

//各状態のヘッダファイル
//各状態では、flightdata::debug をインクリメントして、それを print する。
//状態遷移は、各関数の中でカウントを行う。
#include "preArmState.hpp"
#include "preFlightState.hpp"
#include "flightState.hpp"
#include "disArmState.hpp"
#include "failsafeState.hpp"

//データ管理
#include "flight_data.hpp"



//flightdata::FlightData* flightdata;

void init(){
	//割り込み開始
//	HAL_UART_Receive_DMA(&huart1, flightdata.receive_buffer, 25);

	printf("hello, world \r\n");
	HAL_Delay(100);
}

void loop(){

//	printf("sbus_channel 6 %d : sbus_channel 7 %d " ,flightdata.sbus_channel_data[5], flightdata.sbus_channel_data[6]);

	switch(flightdata.current_state){

		case (uint8_t)flightdata::state::pre_arm_state :
				preArmState(&flightdata);
		break;

		case (uint8_t)flightdata::state::pre_flight_state :
				preFlightState(&flightdata);
		break;

		case (uint8_t)flightdata::state::flight_state :
				flightState(&flightdata);
		break;

		case (uint8_t)flightdata::state::disarm_state :
				disArmState(&flightdata);
		break;

		case (uint8_t)flightdata::state::failsafe_state:
				failsafeState(&flightdata);
		break;

	}
}
