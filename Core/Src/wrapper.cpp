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



void init(){

	printf("hello, world \r\n");
	HAL_Delay(100);
}

void loop(){

	switch(flightdata.current_state){

		case flightdata::state::PRE_ARM_STATE :
				preArmState(&flightdata);
		break;

		case flightdata::state::PRE_FLIGHT_STATE :
				preFlightState(&flightdata);
		break;

		case flightdata::state::FLIGHT_STATE :
				flightState(&flightdata);
		break;

		case flightdata::state::DISARM_STATE :
				disArmState(&flightdata);
		break;

		case flightdata::state::FAILSAFE_STATE:
				failsafeState(&flightdata);
		break;

	}
}
