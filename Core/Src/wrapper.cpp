#include "wrapper.hpp"
#include "gpio.h"
#include "usart.h"
#include <stdio.h>
#include "string"

uint8_t  ReceiveBuffer[25];
uint16_t SBUSData[10] = {};
uint8_t current_state = 0;


void SBUS_decode();
void preArm_State();
void preFlight_State();
void Flight_State();
void Disarm();
void Failsafe();


enum class statemanager : uint8_t {

	preArm = 0,
	preFlight = 1,
	Flight = 2,
	Disarm = 3,
	Failsafe = 4,
};


void init(){

    HAL_UART_Receive_DMA(&huart1, ReceiveBuffer, 25);
	printf("connection\n");
    
}

void loop(){

	switch(current_state){
		case preArm :
			preArm_State();
		break;

		case preFlight :
			preFlight_State();
		break;

		case Flight :
			Flight_State();
		break;

		case Disarm :
			Disarm();
		break;

		case Failsafe :
			Failsafe();
		break;
	}
		
    printf("ch1: %d ch2: %d ch3: %d ch4: %d\n", SBUSData[0], SBUSData[1], SBUSData[2], SBUSData[3]);
    printf("ch5: %d ch6: %d ch7: %d ch8: %d ch9: %d ch10: %d\n", SBUSData[4], SBUSData[5], SBUSData[6], SBUSData[7], SBUSData[8], SBUSData[9]);
	HAL_Delay(100);
}

//データを受信したら呼び出される
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    //データがSBUSの形式であるか確認
	if(ReceiveBuffer[0] == 0x0F && ReceiveBuffer[24] == 0x00){

		SBUS_decode();//SUBSデータの分解
    }

    //受信の再開
    HAL_UART_Receive_DMA(&huart1, ReceiveBuffer, 25);
}

//SBUSからデータを取り出すプログラム
void SBUS_decode(){

    SBUSData[0]  = (ReceiveBuffer[1]        | ReceiveBuffer[2] << 8)   & 0x07FF;
    SBUSData[1]  = (ReceiveBuffer[2] >> 3   | ReceiveBuffer[3] << 5)   & 0x07FF;
    SBUSData[2]  = (ReceiveBuffer[3] >> 6   | ReceiveBuffer[4] << 2    | ReceiveBuffer[5] << 10) & 0x07FF;
    SBUSData[3]  = (ReceiveBuffer[5] >> 1   | ReceiveBuffer[6] << 7)   & 0x07FF;
    SBUSData[4]  = (ReceiveBuffer[6] >> 4   | ReceiveBuffer[7] << 4)   & 0x07FF;
    SBUSData[5]  = (ReceiveBuffer[7] >> 7   | ReceiveBuffer[8] << 1    | ReceiveBuffer[9] << 9) & 0x07FF;
    SBUSData[6]  = (ReceiveBuffer[9] >> 2   | ReceiveBuffer[10] << 6)  & 0x07FF;
    SBUSData[7]  = (ReceiveBuffer[10] >> 5  | ReceiveBuffer[11] << 3)  & 0x07FF;
    SBUSData[8]  = (ReceiveBuffer[12]       | ReceiveBuffer[13] << 8)  & 0x07FF;
    SBUSData[9]  = (ReceiveBuffer[13] >> 3  | ReceiveBuffer[14] << 5)  & 0x07FF;
}

void preArm_State(){

	printf("pre arming state; ch1: %d ch2: %d ch3: %d ch4: %d\r\n", SBUSData[0], SBUSData[1], SBUSData[2], SBUSData[3]);
	printf("pre arming state; ch5: %d ch6: %d ch7: %d ch8: %d ch9: %d ch10: %d\r\n", SBUSData[4], SBUSData[5], SBUSData[6], SBUSData[7], SBUSData[8], SBUSData[9]);

	if((SBUSData[5] > 1000) && (SBUSData[6] > 1000)){
		current_state = (uint8_t)statemanager::preFlight;
	}

	HAL_Delay(100);
}

void preFlight_State(){

	printf("pre flight state; ch1: %d ch2: %d ch3: %d ch4: %d\r\n", SBUSData[0], SBUSData[1], SBUSData[2], SBUSData[3]);
	printf("pre flight state; ch5: %d ch6: %d ch7: %d ch8: %d ch9: %d ch10: %d\r\n", SBUSData[4], SBUSData[5], SBUSData[6], SBUSData[7], SBUSData[8], SBUSData[9]);

	if((SBUSData[5] < 1000) && (SBUSData[6] > 1000)){
		current_state = (uint8_t)statemanager::Flight;
	}

}

void Disarm(){

	printf("disarm\r\n");

	if(SBUSData[6] > 1000){

		current_state = (uint8_t)statemanager::preArm;
	}

	HAL_Delay(100);
}

void Failsafe(){
	printf("fail safe!!");

}
