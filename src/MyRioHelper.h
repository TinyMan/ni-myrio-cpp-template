/*
 * MyRioHelper.h
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */

#ifndef MYRIOHELPER_H_
#define MYRIOHELPER_H_

#include "MyRio.h"

/* include all other classes */
#include "AccelerometerHelper.h"

class MyRio {
private:
	MyRio();
	~MyRio();

public:
	Accelerometer Accel;
	static MyRio& instance() { static MyRio instance; return instance;}
};

extern MyRio& MRio;


#endif /* MYRIOHELPER_H_ */
