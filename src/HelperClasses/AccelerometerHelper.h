/*
 * AccelerometerHelper.h
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */

#ifndef ACCELEROMETERHELPER_H_
#define ACCELEROMETERHELPER_H_

#include "Accelerometer.h"

class Accelerometer {
private:
	MyRio_Accl _channel;

public:
	Accelerometer();
	virtual ~Accelerometer();

	double readX() const;
	double readY() const;
	double readZ() const;
	void scaling();
};

int testAccelerometer();
#endif /* ACCELEROMETERHELPER_H_ */
