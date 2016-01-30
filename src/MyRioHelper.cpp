/*
 * MyRioHelper.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */

#include "MyRioHelper.h"

MyRio& MRio = MyRio::instance();
extern NiFpga_Session myrio_session;

MyRio::MyRio() {
	session = myrio_session;
	NiFpga_Status status = MyRio_Open();
	if (MyRio_IsNotSuccess(status)) {
		throw status;
	}
}

MyRio::~MyRio() {
	MyRio_Close();
}

