/*
 * preArmState.cpp
 *
 *  Created on: Sep 29, 2025
 *      Author: yuukou
 */

#include "main.h"
#include "stdio.h"

//各種データ
#include "flight_data.hpp"
#include "sbusDecode.hpp"


//preArm 時に呼ばれる
void preArmState(flightdata::FlightData* data){


	//現在の状態名を出力
	printf("pre arm state \r\n");
	HAL_Delay(1000);

	//armされたら,arm時処理をした後,PRE_FLIGHT_STATE へ移行
	if(data->arm_on == true){

		/*
		*ここに
		*armした時の
		*処理を
		*記述する
		*/

		//current_state が PRE_FLIGHT_STATE に等しくなるまで書き込み
		while(data->current_state != flightdata::State::PRE_FLIGHT_STATE){

			data->current_state = flightdata::State::PRE_FLIGHT_STATE;
			HAL_Delay(50);
		}
	}

	/*
	 * ここに
	 * prearm時の
	 * 処理を
	 * 記述する
	 */

}



