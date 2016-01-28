/*
 * Accel.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */
#include <iostream>
#include "AccelerometerHelper.h"
#include "MyRioHelper.h"

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

/**
 * Overview:
 * Demonstrates using the onboard accelerometer. Reads the acceleration in the
 * three directions. Prints the values to the console.
 *
 * Instructions:
 * 1. Run this program.
 * 2. Shake the NI myRIO.
 *
 * Output:
 * The program reads the acceleration for 60 s. Acceleration values are written
 * to the console every 1 s.
 *
 * Note:
 * The Eclipse project defines the preprocessor symbol for the NI myRIO-1900.
 * Change the preprocessor symbol to use this example with the NI myRIO-1950.
 */

int testAccelerometer() {
	int LoopDuration = 60, LoopSteps = 1;
	time_t currentTime;
	time_t printTime;
	time_t finalTime;
	double x;
	double y;
	double z;

	/*
	 * Normally, the main function runs a long running or infinite loop.
	 * Read the accelerometer output for 60 seconds.
	 */
	time(&currentTime);
	finalTime = currentTime + LoopDuration;
	printTime = currentTime;
	while (currentTime < finalTime) {
		time(&currentTime);

		/* Don't print every loop iteration. */
		if (currentTime > printTime) {
			x = MRio.Accel.readX();
			y = MRio.Accel.readY();
			z = MRio.Accel.readZ();
			printf("X: %g, Y: %g, Z: %g\n", x, y, z);

			printTime += LoopSteps;
		}
	}
	return 0;
}
