/*
 * PWMHelper.h
 *
 *  Created on: 30 janv. 2016
 *      Author: TinyMan
 */

#ifndef PWMHELPER_H_
#define PWMHELPER_H_
#include "PWM.h"

class Pwm {
protected:
	MyRio_Pwm _channel;
	uint8_t pwmNo;
	MyRio1900Fpga20_ControlU8 sysSelect;
public:
	virtual ~Pwm();
	virtual void enable(bool inverted = false);
	virtual void disable();
	virtual void clockSelect(Pwm_ClockDivider divider);
	virtual void counterMax(uint16_t max);
	virtual void counterCompare(uint16_t compareValue);
	virtual void setDuty(double percent);
	virtual uint16_t getCounter();

};
class PwmA0 : public Pwm{
public:
	PwmA0(){
		pwmNo = 0;
		sysSelect = SYSSELECTA;
	    _channel.cnfg = PWMA_0CNFG;
	    _channel.cs = PWMA_0CS;
	    _channel.max = PWMA_0MAX;
	    _channel.cmp = PWMA_0CMP;
	    _channel.cntr = PWMA_0CNTR;
	}
};
class PwmA1 : public Pwm{
public:
	PwmA1(){
		pwmNo = 1;
		sysSelect = SYSSELECTA;
	    _channel.cnfg = PWMA_1CNFG;
	    _channel.cs = PWMA_1CS;
	    _channel.max = PWMA_1MAX;
	    _channel.cmp = PWMA_1CMP;
	    _channel.cntr = PWMA_1CNTR;
	}
};
class PwmA2 : public Pwm{
public:
	PwmA2(){
		pwmNo = 2;
		sysSelect = SYSSELECTA;
	    _channel.cnfg = PWMA_2CNFG;
	    _channel.cs = PWMA_2CS;
	    _channel.max = PWMA_2MAX;
	    _channel.cmp = PWMA_2CMP;
	    _channel.cntr = PWMA_2CNTR;
	}
};
class PwmB0 : public Pwm{
public:
	PwmB0(){
		pwmNo = 0;
		sysSelect = SYSSELECTB;
	    _channel.cnfg = PWMB_0CNFG;
	    _channel.cs = PWMB_0CS;
	    _channel.max = PWMB_0MAX;
	    _channel.cmp = PWMB_0CMP;
	    _channel.cntr = PWMB_0CNTR;
	}
};
class PwmB1 : public Pwm{
public:
	PwmB1(){
		pwmNo = 1;
		sysSelect = SYSSELECTB;
	    _channel.cnfg = PWMB_1CNFG;
	    _channel.cs = PWMB_1CS;
	    _channel.max = PWMB_1MAX;
	    _channel.cmp = PWMB_1CMP;
	    _channel.cntr = PWMB_1CNTR;
	}
};
class PwmB2 : public Pwm{
public:
	PwmB2(){
		pwmNo = 2;
		sysSelect = SYSSELECTB;
	    _channel.cnfg = PWMB_2CNFG;
	    _channel.cs = PWMB_2CS;
	    _channel.max = PWMB_2MAX;
	    _channel.cmp = PWMB_2CMP;
	    _channel.cntr = PWMB_2CNTR;
	}
};
class PWMHelper {
public:
	PWMHelper();
	virtual ~PWMHelper();

	PwmA0 A0;
	PwmA1 A1;
	PwmA2 A2;
	PwmB0 B0;
	PwmB1 B1;
	PwmB2 B2;
};

int testPwm();
#endif /* PWMHELPER_H_ */
