/*
 * EncoderHelper.h
 *
 *  Created on: 30 janv. 2016
 *      Author: TinyMan
 */

#ifndef ENCODERHELPER_H_
#define ENCODERHELPER_H_
#include "Encoder.h"
#include "MyRio.h"

class Encoder {
protected:
	MyRio_Encoder _channel;
	uint8_t bitNumber = 5;
	MyRio1900Fpga20_ControlU8 sysSelect;
public:
	virtual ~Encoder();
	virtual void configure(Encoder_ConfigureMask mask,
			Encoder_ConfigureSettings settings);
	virtual void clearOverflow();
	virtual void clearError();
	virtual void setMode(bool quadPhase);
	virtual void reset();
	virtual void enable(bool quadPhase = false);
	virtual uint8_t status();
	virtual uint32_t counter();

};
class EncoderA : public Encoder {
public:
	EncoderA() {
		sysSelect = SYSSELECTA;
		_channel.cnfg = ENCACNFG;
		_channel.stat = ENCASTAT;
		_channel.cntr = ENCACNTR;
	}
};
class EncoderB : public Encoder {
public:
	EncoderB() {
		sysSelect = SYSSELECTB;
		_channel.cnfg = ENCBCNFG;
		_channel.stat = ENCBSTAT;
		_channel.cntr = ENCBCNTR;
	}
};
class EncoderC0 : public Encoder {
public:
	EncoderC0() {
		bitNumber = 0;
		sysSelect = SYSSELECTC;
		_channel.cnfg = ENCC_0CNFG;
		_channel.stat = ENCC_0STAT;
		_channel.cntr = ENCC_0CNTR;
	}
};
class EncoderC1 : public Encoder {
public:
	EncoderC1() {
		/* NOT YET SUPPORTED BY NI */
		sysSelect = SYSSELECTC;
		_channel.cnfg = ENCC_1CNFG;
		_channel.stat = ENCC_1STAT;
		_channel.cntr = ENCC_1CNTR;
	}
};
class EncoderHelper {
public:
	EncoderA A;
	EncoderB B;
	EncoderC0 C0;

	EncoderHelper();
	virtual ~EncoderHelper();
};

int testEncoder();

#endif /* ENCODERHELPER_H_ */
