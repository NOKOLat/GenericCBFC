/*
 * PWM.hpp
 *
 *  Created on: Nov 7, 2025
 *      Author: yuukou
 */

#ifndef INC_PWM_HPP_
#define INC_PWM_HPP_

#include <cstdint>
#include "array"
#include "tim.h"
#include "MotorSettings.hpp"

class PWM {

private:


public:

	PWM() = default;
	virtual ~PWM() = default;

	/*動力モーターに関する機能*/
	virtual bool MotorSettingCheck(uint8_t motor_number) = 0;
	virtual void InitMotor() = 0;
	virtual void CalcMotorOutput(float throttle, std::array<float,4>& control, uint16_t* motor) = 0;
	virtual void GenerateMotor(uint16_t* motor_pwm) = 0;
	virtual void MotorStop() = 0;
	virtual void SetMotorConfig(const MotorTim& tim, const MotorChannel& channel, const MotorPWM& pwm) = 0;

};

#endif /* INC_PWM_HPP_ */
