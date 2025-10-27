/*
 * flightState.cpp
 *
 *  Created on: Sep 29, 2025
 *      Author: yuukou
 */

#include "main.h"
#include "stdio.h"

//各種データ
#include "flight_data.hpp"
#include "sbusDecode.hpp"

//flight 時に呼ばれる
void flightState(flightdata::FlightData* data){

	//現在の状態名を表示
	printf("flight state \r\n");
	HAL_Delay(1000);

	//armスイッチがオフになったらDISARM_STATE へ移行
	if(data->arm_on == false){

		//current_data が DISARM_STATE に一致するまで書き込み
		while(data->current_state != flightdata::State::DISARM_STATE){
			data->current_state = flightdata::State::DISARM_STATE;
			HAL_Delay(50);
		}
	}

	/*
	 * ここに
	 * flight中の
	 * 処理を
	 * 記述する
	 */

}

