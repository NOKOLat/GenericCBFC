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

protected:

    // Servo設定のみ基底が保持
    ServoTim servo_tim{};
    ServoChannel servo_channel{};
    ServoPWM servo_pwm{};

public:

	PWM() = default;
	virtual ~PWM() = default;

	/*サーボモーターに関する機能*/
	virtual void InitServo();
    virtual void CalcServo(SbusChannelData sbus_data, uint16_t adc_value, std::array<uint16_t,2>& servo);
    virtual void GenerateServo(std::array<uint16_t,2>& servo);
    virtual void SetServoConfig(const ServoTim& tim, const ServoChannel& channel, const ServoPWM& pwm);


	/*動力モーターに関する機能*/
	virtual bool MotorSettingCheck(uint8_t motor_number) = 0;
	virtual void InitMotor() = 0;
	virtual void CalcMotorOutput(float throttle, std::array<float,4>& control, uint16_t* motor) = 0;
	virtual void GenerateMotor(uint16_t* motor_pwm) = 0;
	virtual void MotorStop() = 0;
	virtual void SetMotorConfig(const MotorTim& tim, const MotorChannel& channel, const MotorPWM& pwm) = 0;

};

#endif /* INC_PWM_HPP_ */
