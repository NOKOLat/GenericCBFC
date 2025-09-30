#include "wrapper.hpp"
#include "FlightManger.hpp"
#include "gpio.h"
#include "spi.h"
#include "usart.h"
#include <stdio.h>
#include "string"

uint8_t  ReceiveBuffer[25];
uint16_t SBUSData[10] = {};
// FlightManger flightManger;
// enum class DrownStatus:uint8_t{
//     Initial=0,
//     ArmStandby,
//     FlightStandby,
//     Flying,
//     Disarmed,
// };
// drownStatus = DrownStatus::Initial;
void SBUS_decode();
void Read();
void init(){
    // HAL_UART_Receive_DMA(&huart1, ReceiveBuffer, 25);
	printf("connection\n");
}

void loop(){
    // printf("ch1: %d ch2: %d ch3: %d ch4: %d\n", SBUSData[0], SBUSData[1], SBUSData[2], SBUSData[3]);
    // printf("ch5: %d ch6: %d ch7: %d ch8: %d ch9: %d ch10: %d\n", SBUSData[4], SBUSData[5], SBUSData[6], SBUSData[7], SBUSData[8], SBUSData[9]);
//     switch (drownStatus)
//     {
//     case DrownStatus::Initial:
//         /* code */
//         printf("status1\n");
//         drownStatus = DrownStatus::ArmStandby;
//         break;
//     case DrownStatus::ArmStandby:
//         /* code */
//         printf("status2\n");
//         drownStatus = DrownStatus::FlightStandby;
//         break;
//     case DrownStatus::FlightStandby:
//         /* code */
//         printf("status3\n");
//         drownStatus = DrownStatus::Flying;
//         break;
//     case DrownStatus::Flying:
//         /* code */
//         printf("status4\n");
//         drownStatus = DrownStatus::Disarmed;
//         break;
//     case DrownStatus::Disarmed:
//         /* code */
//         printf("status5\n");
// drownStatus = DrownStatus::ArmStandby;
//         break;
//     default:
//         break;
//     }
uint8_t tx_buffer[2] = {};
uint8_t rx_buffer[2] = {};

tx_buffer[0] = 0x75 | 0x80;//読み取りたいレジスタのアドレス
tx_buffer[1] = 0x00;//からのデータ

//CSピンをLOWにする(通信開始)
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

//アドレスの送信とデータの受信
HAL_SPI_TransmitReceive(&hspi1, tx_buffer, rx_buffer, 2, 1000);

//CSピンをHIGHにする(通信終了)
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);

//受信したデータを取得(2番目の要素に入る)
uint8_t ReadValue = rx_buffer[1];
    printf("%d", ReadValue);
    printf("loop\n");
	HAL_Delay(1000);
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
