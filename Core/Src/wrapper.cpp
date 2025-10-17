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

//タイマー
#include "tim.h"


void init(){

	printf("hello, world \r\n");

	//timer開始
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET);
	HAL_TIM_Base_Start_IT(&htim6);
	
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
