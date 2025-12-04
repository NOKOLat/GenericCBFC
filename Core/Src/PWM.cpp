/*
 * PWM.cpp
 *
 *  Created on: Nov 7, 2025
 *      Author: yuukou
 */

#include <PWM.hpp>
#include <array>
#include "flight_data.hpp"

// Servoの開閉判定
void PWM::CalcServo(flightdata::SbusChannel sbus_data, uint16_t adc_value, std::array<uint16_t, 2>& servo){

	/*仮の手動投下装置*/	
	if((adc_value > 1000) || sbus_data.drop == 2){

		servo[1] = servo_pwm.open;
	} 
	else {
		servo[1] = servo_pwm.close;
	}
	
}

// Servo初期化
void PWM::InitServo(){

	HAL_TIM_PWM_Start(servo_tim.servo1, servo_channel.servo1);
	HAL_TIM_PWM_Start(servo_tim.servo2, servo_channel.servo2);

	__HAL_TIM_SET_COMPARE(servo_tim.servo1 , servo_channel.servo1, servo_pwm.close);
	__HAL_TIM_SET_COMPARE(servo_tim.servo2 , servo_channel.servo2, servo_pwm.close);
}

// Servo出力
void PWM::GenerateServo(std::array<uint16_t,2>& servo){

	__HAL_TIM_SET_COMPARE(servo_tim.servo1 , servo_channel.servo1, servo[0]);
	__HAL_TIM_SET_COMPARE(servo_tim.servo1 , servo_channel.servo2, servo[1]);
}

// Servo設定
void PWM::SetServoConfig(const ServoTim& tim, const ServoChannel& channel, const ServoPWM& pwm){
	
	servo_tim = tim;
	servo_channel = channel;
	servo_pwm = pwm;
}

