/*
 * PWMHelper.h
 *
 *  Created on: 30 janv. 2016
 *      Author: TinyMan
 */

#ifndef PWMHELPER_H_
#define PWMHELPER_H_
#include "PWM.h"

/* frequency preset */
#define CLOCKDIVIDER(a) (a << 16)
#define COUNTERMAX(a) (a)
#define FREQUENCY_50HZ 50
#define FREQUENCY_100HZ 100
#define FREQUENCY_10KHZ 10000
#define FREQUENCY_1KHZ 1000

/** **/

class Pwm {
public:
	MyRio_Pwm _channel;
	uint8_t pwmNo;
	MyRio1900Fpga20_ControlU8 sysSelect;
	uint16_t _counterMax = 0;
	uint16_t _counterCompare = 0;
	Pwm_ClockDivider _clockDivider = Pwm_1x;

public:
	virtual ~Pwm();
	void enable(bool inverted = false);
	void disable();
	void clockSelect(Pwm_ClockDivider divider);
	void counterMax(uint16_t max);
	void counterCompare(uint16_t compareValue);
	void setDuty(float percent);
	uint16_t getCounter();
	void setFrequency(uint32_t freq);

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
