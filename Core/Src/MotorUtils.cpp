/*
 * MotorUtils.cpp
 *
 *  Created on: Nov 7, 2025
 *      Author: yuukou
 */

#include "PWM.hpp"
#include <MotorUtils.hpp>
#include "MotorSettings.hpp"

/* モーター配置（上が前）
 * 	1	2
 *
 * 	3	4
 */

bool MotorUtils::MotorSettingCheck(uint8_t motor_number){


	if(motor_number != 4){

		//setting error
		return false;
	}
	else{

		//valid setting
		return true;
	}

}


void MotorUtils::InitMotor(){

	HAL_TIM_PWM_Start(motor_tim.motor1, motor_channel.motor1);
	HAL_TIM_PWM_Start(motor_tim.motor2, motor_channel.motor2);
    HAL_TIM_PWM_Start(motor_tim.motor3, motor_channel.motor3);
    HAL_TIM_PWM_Start(motor_tim.motor4, motor_channel.motor4);

    __HAL_TIM_SET_COMPARE(motor_tim.motor1 , motor_channel.motor1, motor_pwm.init);
    __HAL_TIM_SET_COMPARE(motor_tim.motor2 , motor_channel.motor2, motor_pwm.init);
    __HAL_TIM_SET_COMPARE(motor_tim.motor3 , motor_channel.motor3, motor_pwm.init);
    __HAL_TIM_SET_COMPARE(motor_tim.motor4 , motor_channel.motor4, motor_pwm.init);

	HAL_Delay(2500);
}


void MotorUtils::GenerateMotor(uint16_t* motor){

	__HAL_TIM_SET_COMPARE(motor_tim.motor1 , motor_channel.motor1, motor[0]);
	__HAL_TIM_SET_COMPARE(motor_tim.motor2 , motor_channel.motor2, motor[1]);
    __HAL_TIM_SET_COMPARE(motor_tim.motor3 , motor_channel.motor3, motor[2]);
    __HAL_TIM_SET_COMPARE(motor_tim.motor4 , motor_channel.motor4, motor[3]);
}


void MotorUtils::CalcMotorOutput(float throttle, std::array<float,4>& control, uint16_t* motor){


    motor[0] = motor_pwm.min + (throttle + control[0] - control[1] - control[2]);
    motor[1] = motor_pwm.min + (throttle + control[0] + control[1] + control[2]);
    motor[2] = motor_pwm.min + (throttle - control[0] - control[1] + control[2]);
    motor[3] = motor_pwm.min + (throttle - control[0] + control[1] - control[2]);

    for(uint8_t i=0; i<4; i++){

        if(motor[i] >= motor_pwm.max){

            motor[i] = motor_pwm.max;
        }

        if(motor[i] <= motor_pwm.min){

            motor[i] = motor_pwm.min;
        }
    }
}


void MotorUtils::SetMotorConfig(const MotorTim& tim, const MotorChannel& channel, const MotorPWM& pwm){

    motor_tim = tim;
    motor_channel = channel;
    motor_pwm = pwm;
}


void MotorUtils::MotorStop(){
	HAL_TIM_PWM_Stop(motor_tim.motor1, motor_channel.motor1);
	HAL_TIM_PWM_Stop(motor_tim.motor2, motor_channel.motor2);
	HAL_TIM_PWM_Stop(motor_tim.motor3, motor_channel.motor3);
	HAL_TIM_PWM_Stop(motor_tim.motor4, motor_channel.motor4);
}
