/*
 * DioHelper.h
 *
 *  Created on: 1 mars 2016
 *      Author: TinyMan
 */

#ifndef DIOHELPER_H_
#define DIOHELPER_H_
#include "DIO.h"

class Dio {
private:
	MyRio_Dio _channel;

public:
	enum DIO {
		A70, A158, B70, B158, C70
	};
	Dio(enum DIO dio, uint8_t num);

	bool read();
	void write(bool value = true);
};

void testDio();

#endif /* DIOHELPER_H_ */
