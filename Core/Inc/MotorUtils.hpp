/*
 * MotorUtils.hpp
 *
 *  Created on: Nov 7, 2025
 *      Author: yuukou
 */

#ifndef INC_MOTORUTILS_HPP_
#define INC_MOTORUTILS_HPP_

#include <cstdint>
#include "array"
#include "tim.h"
#include "PWM.hpp"
#include "MotorSettings.hpp"


class MotorUtils : public PWM{

public:

	MotorUtils() = default;

	virtual ~MotorUtils() = default;

	bool MotorSettingCheck(uint8_t motor_number) override;
	void InitMotor() override;
	void CalcMotorOutput(float throttle, std::array<float,4>& control, uint16_t* motor) override;
	void GenerateMotor(uint16_t* motor_pwm) override;
	void MotorStop() override;
	void SetMotorConfig(const MotorTim& tim, const MotorChannel& channel, const MotorPWM& pwm) override;


private:

    MotorTim motor_tim{};
    MotorChannel motor_channel{};
    MotorPWM motor_pwm{};

};

#endif /* INC_MOTORUTILS_HPP_ */
