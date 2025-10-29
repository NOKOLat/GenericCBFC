/*
 * sbusDecode.cpp
 *
 *  Created on: Oct 13, 2025
 *      Author: yuukou
 */

#include "sbusDecode.hpp"
#include "flight_data.hpp"

void sbus_Decode(flightdata::FlightData* data){

	data->sbus_channel_data[0]  = (data->receive_buffer[1]| data->receive_buffer[2] << 8)   & 0x07FF;
	data->sbus_channel_data[1]  = (data->receive_buffer[2] >> 3   | data->receive_buffer[3] << 5)   & 0x07FF;
	data->sbus_channel_data[2]  = (data->receive_buffer[3] >> 6   | data->receive_buffer[4] << 2    | data->receive_buffer[5] << 10) & 0x07FF;
	data->sbus_channel_data[3]  = (data->receive_buffer[5] >> 1   | data->receive_buffer[6] << 7)   & 0x07FF;
	data->sbus_channel_data[4]  = (data->receive_buffer[6] >> 4   | data->receive_buffer[7] << 4)   & 0x07FF;
	data->sbus_channel_data[5]  = (data->receive_buffer[7] >> 7   | data->receive_buffer[8] << 1    | data->receive_buffer[9] << 9) & 0x07FF;
	data->sbus_channel_data[6]  = (data->receive_buffer[9] >> 2   | data->receive_buffer[10] << 6)  & 0x07FF;
	data->sbus_channel_data[7]  = (data->receive_buffer[10] >> 5  | data->receive_buffer[11] << 3)  & 0x07FF;
	data->sbus_channel_data[8]  = (data->receive_buffer[12]       | data->receive_buffer[13] << 8)  & 0x07FF;
	data->sbus_channel_data[9]  = (data->receive_buffer[13] >> 3  | data->receive_buffer[14] << 5)  & 0x07FF;
}


//sbus を読み取った結果の解析（関数名は仮称）
//フェイルセーフの処理を追加しよう
void sbusInterpreter(flightdata::FlightData* data){

	if(data->sbus_channel_data[(uint8_t)flightdata::SbusChannel::arm] > 1000){

		/*
		 * ここに
		 * armのフラグを
		 * 立てる処理を
		 * 記述する
		 */
		data->arm_on = true;
	}
	else{
		/*
		 * ここに
		 * armのフラグを
		 * 倒す処理を
		 * 記述する
		 */
		data->arm_on = false;
	}


	if((data->sbus_channel_data[(uint8_t)flightdata::SbusChannel::fly] > 1000)||(data->sbus_channel_data[(uint8_t)flightdata::SbusChannel::throttle] > 0)){

		/*
		 * ここに
		 * flightスイッチのフラグを
		 * 立てる処理を
		 * 記述する
		 */
		data->flight_on = true;

	}
	else{
		/*
		 * ここに
		 * flightスイッチのフラグを
		 * 倒す処理を
		 * 記述する
		 */
		data->flight_on = false;
	}

	/*
	*ここに
	*他のスイッチの判定
	*sbus通信チェック
	*のコードを追加
	*/
	
		if(data->sbus_lost_connection == true){

		while(data->current_state != flightdata::State::FAILSAFE_STATE)
			data->current_state = flightdata::State::FAILSAFE_STATE;
	}

}

void sbusUpdate(flightdata::FlightData* data){

	data->sbus_lost_count = 0;
}

void sbusLostDetecter(flightdata::FlightData* data){

	if(data->sbus_lost_count > 400){

		data->sbus_lost_connection = true;
	}
	else{

		data->sbus_lost_connection = false;
	}
}
