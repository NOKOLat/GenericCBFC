/*
 * disArmState.cpp
 *
 *  Created on: Sep 29, 2025
 *      Author: yuukou
 */

#include "main.h"
#include "stdio.h"

//各種データ
#include "flight_data.hpp"
#include "sbusDecode.hpp"

//disArm 時に呼ばれる
void disArmState(flightdata::FlightData* data){

	//現在の状態名を表示
	printf("disarm state \r\n");
	HAL_Delay(1000);

	/*
	 * ここに
	 * disarm時の
	 * 処理を
	 * 記述する
	 */

	//armスイッチがオンになったら、PRE_ARM_STATE へ移行
	if(data->arm_on == true){

	//current_state が PRE_ARM_STATE 一致するまで書き込み
		while(data->current_state != flightdata::State::PRE_ARM_STATE){

				data->current_state = flightdata::State::PRE_ARM_STATE;
				HAL_Delay(50);
		}
	}


}
