/*
 * MyRioHelper.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */

#include "MyRioHelper.h"

MyRio& MRio = MyRio::instance();

MyRio::MyRio() {
	NiFpga_Status status = MyRio_Open();
	if (MyRio_IsNotSuccess(status)) {
		throw status;
	}
}

MyRio::~MyRio() {
	NiFpga_Status status = MyRio_Close();
}

