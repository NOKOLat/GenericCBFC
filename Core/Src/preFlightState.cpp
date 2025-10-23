/*
 * preFlightState.cpp
 *
 *  Created on: Sep 29, 2025
 *      Author: yuukou
 */

#include "main.h"
#include "stdio.h"

//各種データ
#include "flight_data.hpp"
#include "sbusDecode.hpp"

//preFlight 時に呼ばれる
void preFlightState(flightdata::FlightData* data){

	//現在の状態名を表示
	printf("pre flight state \r\n");
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
	 * flight前の
	 * 処理を
	 * 記述する
	 */


	//flyスイッチがオンになったら、flight前の処理をした後,FLIGHT_STATE へ移行
	if(data->flight_on == true){

		/*
		 * ここに
		 * flightがONになった時の
		 * 処理を
		 * 記述する
		*/

		//current_state がFLIGHT_STATEに一致するまで書き込み
		while(data->current_state != flightdata::State::FLIGHT_STATE){
			data->current_state = flightdata::State::FLIGHT_STATE;
			HAL_Delay(50);
		}
	}

}

