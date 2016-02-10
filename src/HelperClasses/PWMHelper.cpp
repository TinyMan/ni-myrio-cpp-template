/*
 * PWMHelper.cpp
 *
 *  Created on: 30 janv. 2016
 *      Author: TinyMan
 */

#include "PWMHelper.h"
#include "MyRioHelper.h"
#include <time.h>
#include <iostream>
#include <cstdio>

PWMHelper::PWMHelper() {

}

PWMHelper::~PWMHelper() {
}

Pwm::~Pwm() {
	disable();
}


void Pwm::enable(bool inverted) {

	uint8_t inv = false ? Pwm_Inverted : Pwm_NotInverted;
	Pwm_Configure(&MRio.Pwm.A0._channel,
			(Pwm_ConfigureMask) (Pwm_Invert | Pwm_Mode),
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

	selectReg = selectReg | (1 << (2 + this->pwmNo));

	/*
	 * Write the updated value of the SYSSELECTA register.
	 */
	NiFpga_WriteU8(MRio.session, sysSelect, selectReg);

}

void Pwm::clockSelect(Pwm_ClockDivider divider) {
	_clockDivider = divider;
	Pwm_ClockSelect(&_channel, divider);
}

void Pwm::counterMax(uint16_t max) {
	_counterMax = max;
	Pwm_CounterMaximum(&_channel, max);
}

void Pwm::counterCompare(uint16_t compareValue) {
	_counterCompare = compareValue;
	Pwm_CounterCompare(&_channel, compareValue);
}

void Pwm::setDuty(float percent) {
	counterCompare((uint16_t) (percent*_counterMax));
}

void Pwm::disable() {
	Pwm_Configure(&_channel, (Pwm_ConfigureMask) (Pwm_Mode),
			(Pwm_ConfigureSettings) (Pwm_Disabled));
}

uint16_t Pwm::getCounter() {
	return Pwm_Counter(&_channel);
}

void Pwm::setFrequency(uint32_t freq) {
	using namespace std;
	switch(freq){
	case FREQUENCY_10KHZ:
	case FREQUENCY_1KHZ:
		clockSelect(Pwm_4x);
		break;
	case FREQUENCY_50HZ:
		clockSelect(Pwm_32x);
		break;
	case FREQUENCY_100HZ:
		clockSelect(Pwm_16x);
		break;
	}
	switch(freq){
	case FREQUENCY_10KHZ:
		counterMax(1000);
		break;
	case FREQUENCY_1KHZ:
		counterMax(10000);
		break;
	case FREQUENCY_50HZ:
	case FREQUENCY_100HZ:
		counterMax(25000);
		break;
	}/*
	_counterMax = uint8_t(freq >> 16);
	_clockDivider = Pwm_ClockDivider(freq);*/
	//cout << _counterCompare << "\n" << _clockDivider << endl;
	/*counterMax(_counterMax);
	clockSelect(_clockDivider);*/
}


/**
 * Overview:
 * Demonstrates using the PWM. Generates a PWM signal from PWM 0 on
 * connector A.
 *
 * Instructions:
 * 1. Connect an oscilloscope to the PWM 0 pin on connector A.
 * 2. Run this program.
 *
 * Output:
 * The program generates a 25% duty cycle signal at 10 kHz for 60 s.
 *
 * Note:
 * The Eclipse project defines the preprocessor symbol for the NI myRIO-1900.
 * Change the preprocessor symbol to use this example with the NI myRIO-1950.
 */
int testPwm() {

	printf("PWM\n");

	Pwm& pwm = MRio.Pwm.A0;
	pwm.setFrequency(FREQUENCY_50HZ);

	/* should be equivalent to:
	pwm.clockSelect(Pwm_32x);
	pwm.counterMax(25000);
	*/

	pwm.enable();

	float dutyCycle= 0.75;
	float i = 0.001;
	pwm.setDuty(dutyCycle);
	/*
	 * Normally, the main function runs a long running or infinite loop.
	 * Keep the program running for 60 seconds so that the PWM output can be
	 * observed using an external instrument.
	 */

	time_t currentTime;
	time_t finalTime;
	time(&currentTime);
	finalTime = currentTime + 60;
	time_t nextInvert = currentTime;
	using namespace std;
	while (currentTime < finalTime) {
		//std::cout << "inner loop\n";
		if(currentTime >= nextInvert){
			if(dutyCycle <= 0.090 || dutyCycle >= 0.1) i = -i;
			dutyCycle = dutyCycle + i;
			pwm.setDuty(dutyCycle);
			cout << dutyCycle << endl;
			nextInvert = currentTime + 1;
		}
		time(&currentTime);
	}

	return 0;
}
