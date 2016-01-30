/*
 * PWMHelper.cpp
 *
 *  Created on: 30 janv. 2016
 *      Author: TinyMan
 */

#include "PWMHelper.h"
#include "MyRioHelper.h"
#include <time.h>

PWMHelper::PWMHelper() {

}

PWMHelper::~PWMHelper() {
}

Pwm::~Pwm() {
	disable();
}

void Pwm::enable(bool inverted) {
	uint8_t inv = inverted ? Pwm_Inverted : Pwm_NotInverted;
	Pwm_Configure(&_channel, (Pwm_ConfigureMask) (Pwm_Invert | Pwm_Mode),
			(Pwm_ConfigureSettings) (inv | Pwm_Enabled));

	/*
	 * PWM outputs are on pins shared with other onboard devices. To output on
	 * a physical pin, select the PWM on the appropriate SELECT register. See
	 * the MUX example for simplified code to enable-disable onboard devices.
	 *
	 * Read the value of the SYSSELECTA register.
	 */
	uint8_t selectReg;
	NiFpga_ReadU8(MRio.session, sysSelect, &selectReg);

	/*
	 * Set bit2 of the SYSSELECTA register to enable PWMA_0 functionality.
	 * The functionality of the bit is specified in the documentation.
	 */

	selectReg = selectReg | (1 << (2 + pwmNo));

	/*
	 * Write the updated value of the SYSSELECTA register.
	 */
	NiFpga_WriteU8(MRio.session, sysSelect, selectReg);

}

void Pwm::clockSelect(Pwm_ClockDivider divider) {
	Pwm_ClockSelect(&_channel, divider);
}

void Pwm::counterMax(uint16_t max) {
	Pwm_CounterMaximum(&_channel, max);
}

void Pwm::counterCompare(uint16_t compareValue) {
	Pwm_CounterCompare(&_channel, compareValue);
}

void Pwm::setDuty(double percent) {
}

void Pwm::disable() {
	Pwm_Configure(&_channel, (Pwm_ConfigureMask) (Pwm_Mode),
			(Pwm_ConfigureSettings) (Pwm_Disabled));
}

uint16_t Pwm::getCounter() {
	return Pwm_Counter(&_channel);
}

int testPwm() {
	MRio.Pwm.A0.clockSelect(Pwm_4x);
	MRio.Pwm.A0.counterMax(1000);
	MRio.Pwm.A0.counterCompare(250);
	MRio.Pwm.A0.enable();

	/*
	 * Normally, the main function runs a long running or infinite loop.
	 * Keep the program running for 60 seconds so that the PWM output can be
	 * observed using an external instrument.
	 */

    time_t currentTime;
    time_t finalTime;
	time (&currentTime);
	finalTime = currentTime + 60;
	while (currentTime < finalTime) {
		time(&currentTime);
	}

	return 0;
}
