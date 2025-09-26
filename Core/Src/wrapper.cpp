#include "wrapper.hpp"
#include "gpio.h"
#include "usart.h"
#include <stdio.h>
#include "string"

uint8_t  receive_buffer[25];
uint16_t sbus_data[10] = {};
uint8_t current_state = 0;


void SBUS_decode();
void preArmState();
void preFlightState();
void flightState();
void disArmState();
void failsafeState();


enum class statemanager : uint8_t {

	preArm = 0,
	preFlight = 1,
	Flight = 2,
	Disarm = 3,
	Failsafe = 4,
};


void init(){

    HAL_UART_Receive_DMA(&huart1, receive_buffer, 25);
	printf("connection\n");
    
}

void loop(){

	switch(current_state){
		case preArm :
			preArmState();
		break;

		case preFlight :
			preFlightState();
		break;

		case Flight :
			flightState();
		break;

		case Disarm :
			disArmState();
		break;

		case Failsafe :
			failsafeState();
		break;
	}
		
    printf("ch1: %d ch2: %d ch3: %d ch4: %d\n", sbus_data[0], sbus_data[1], sbus_data[2], sbus_data[3]);
    printf("ch5: %d ch6: %d ch7: %d ch8: %d ch9: %d ch10: %d\n", sbus_data[4], sbus_data[5], sbus_data[6], sbus_data[7], sbus_data[8], sbus_data[9]);
	HAL_Delay(100);
}

//データを受信したら呼び出される
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    //データがSBUSの形式であるか確認
	if(receive_buffer[0] == 0x0F && receive_buffer[24] == 0x00){

		SBUS_decode();//SBUSデータの分解
    }

    //受信の再開
    HAL_UART_Receive_DMA(&huart1, receive_buffer, 25);
}

//SBUSからデータを取り出すプログラム
void SBUS_decode(){

    sbus_data[0]  = (receive_buffer[1]        | receive_buffer[2] << 8)   & 0x07FF;
    sbus_data[1]  = (receive_buffer[2] >> 3   | receive_buffer[3] << 5)   & 0x07FF;
    sbus_data[2]  = (receive_buffer[3] >> 6   | receive_buffer[4] << 2    | receive_buffer[5] << 10) & 0x07FF;
    sbus_data[3]  = (receive_buffer[5] >> 1   | receive_buffer[6] << 7)   & 0x07FF;
    sbus_data[4]  = (receive_buffer[6] >> 4   | receive_buffer[7] << 4)   & 0x07FF;
    sbus_data[5]  = (receive_buffer[7] >> 7   | receive_buffer[8] << 1    | receive_buffer[9] << 9) & 0x07FF;
    sbus_data[6]  = (receive_buffer[9] >> 2   | receive_buffer[10] << 6)  & 0x07FF;
    sbus_data[7]  = (receive_buffer[10] >> 5  | receive_buffer[11] << 3)  & 0x07FF;
    sbus_data[8]  = (receive_buffer[12]       | receive_buffer[13] << 8)  & 0x07FF;
    sbus_data[9]  = (receive_buffer[13] >> 3  | receive_buffer[14] << 5)  & 0x07FF;
}

void preArmState(){

	printf("pre arming state; ch1: %d ch2: %d ch3: %d ch4: %d\r\n", sbus_data[0], sbus_data[1], sbus_data[2], sbus_data[3]);
	printf("pre arming state; ch5: %d ch6: %d ch7: %d ch8: %d ch9: %d ch10: %d\r\n", sbus_data[4], sbus_data[5], sbus_data[6], sbus_data[7], sbus_data[8], sbus_data[9]);

	if((sbus_data[5] > 1000) && (sbus_data[6] > 1000)){
		current_state = (uint8_t)statemanager::preFlight;
	}

	HAL_Delay(100);
}

void preFlightState(){

	printf("pre flight state; ch1: %d ch2: %d ch3: %d ch4: %d\r\n", sbus_data[0], sbus_data[1], sbus_data[2], sbus_data[3]);
	printf("pre flight state; ch5: %d ch6: %d ch7: %d ch8: %d ch9: %d ch10: %d\r\n", sbus_data[4], sbus_data[5], sbus_data[6], sbus_data[7], sbus_data[8], sbus_data[9]);

	if((sbus_data[5] < 1000) && (sbus_data[6] > 1000)){
		current_state = (uint8_t)statemanager::Flight;
	}

}

void disArmState(){

	printf("disarm\r\n");

	if(sbus_data[6] > 1000){

		current_state = (uint8_t)statemanager::preArm;
	}

	HAL_Delay(100);
}

void failsafeState(){
	printf("fail safe!!");

}
