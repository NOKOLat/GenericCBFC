//基本機能
#include "wrapper.hpp"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"

//各状態のヘッダファイル
#include "preArmState.hpp"
#include "preFlightState.hpp"
#include "flightState.hpp"
#include "disArmState.hpp"
#include "failsafeState.hpp"

//データ管理
#include "flight_data.hpp"
#include "sbusDecode.hpp"

//タイマー、ループ管理
#include "tim.h"
#include "loopFlagReset.hpp"
#include "loopFlagSet.hpp"




void init(){

	loopFlagReset(&flightdata);
	
	printf("hello, world \r\n");

	//timer開始
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim6);

	//uart割り込み開始
	HAL_UART_Receive_DMA(&huart1,flightdata.receive_buffer, 25);
	
	HAL_Delay(100);
}

void loop(){

	if(flightdata.switch_flag == false){

		loopFlagSet(&flightdata);
	
		switch(flightdata.current_state){
	
			case flightdata::State::PRE_ARM_STATE :
					preArmState(&flightdata);
			break;
	
			case flightdata::State::PRE_FLIGHT_STATE :
					preFlightState(&flightdata);
			break;
	
			case flightdata::State::FLIGHT_STATE :
					flightState(&flightdata);
			break;
	
			case flightdata::State::DISARM_STATE :
					disArmState(&flightdata);
			break;
	
			case flightdata::State::FAILSAFE_STATE:
					failsafeState(&flightdata);
			break;
	
		}
	}
}

//timer割り込み処理
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim == &htim6){

	//タイマーが最大値に達したら、フラグをリセット
	loopFlagReset(&flightdata);

	}

}

//uart割り込み, sbus_Decode() 呼び出し
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    //データがSBUSの形式であるか確認
	if(flightdata.receive_buffer[0] == 0x0F && flightdata.receive_buffer[24] == 0x00){

		sbus_Decode(&flightdata);//SBUSデータの分解
		sbusInterpreter(&flightdata);//スイッチ判定
    }

    //受信の再開
    HAL_UART_Receive_DMA(&huart1, flightdata.receive_buffer, 25);
}
