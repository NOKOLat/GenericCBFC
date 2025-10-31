#include "main.h"
#include "stdio.h"


//各種データ
#include "flight_data.hpp"
#include "sbusDecode.hpp"

void failsafeState(flightdata::FlightData* data){

	/*
	 *PWMの停止
	 *LEDの処理
	 *を追加する
	 */
	
	while(1){
		printf("fail safe state \r\n");

		/*
	 	*PWMの停止
	 	*PIDの処理
	 	*を追加する
	 	*/
	}
}
