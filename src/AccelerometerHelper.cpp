/*
 * Accel.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */

#include "AccelerometerHelper.h"

Accelerometer::Accelerometer() {
	/*
	 * Specify the registers that correspond to the accelerometer channel
	 * that needs to be accessed.
	 *
	 * Assign constant to the accelerate weight.
	 */
	_channel.xval = ACCXVAL;
	_channel.yval = ACCYVAL;
	_channel.zval = ACCZVAL;
	_channel.scale_wght = ACCSCALEWGHT_CST;
	scaling();
}

Accelerometer::~Accelerometer() {
	// TODO Auto-generated destructor stub
}

double Accelerometer::readX() const {
	return Accel_ReadX(&this->_channel);
}

double Accelerometer::readY() const {
	return Accel_ReadY(&this->_channel);
}

double Accelerometer::readZ() const {
	return Accel_ReadZ(&this->_channel);
}

void Accelerometer::scaling() {
	Accel_Scaling(&this->_channel);
}
