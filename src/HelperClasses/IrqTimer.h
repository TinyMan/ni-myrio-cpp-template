/*
 * IrqTimer.h
 *
 *  Created on: 4 févr. 2016
 *      Author: TinyMan
 */

#ifndef IRQTIMER_H_
#define IRQTIMER_H_
#include "TimerIRQ.h"
#include "IrqListener.h"

class IrqTimer {
private:
	MyRio_IrqTimer _channel;

public:
	IrqTimer();
	virtual ~IrqTimer();

	IrqListener* reg(uint32_t timeout);
	void unreg(const NiFpga_IrqContext& context);

	static int test();

};

#endif /* IRQTIMER_H_ */
