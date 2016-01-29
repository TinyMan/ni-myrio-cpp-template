/*
 * IrqListener.h
 *
 *  Created on: 29 janv. 2016
 *      Author: TinyMan
 */

#ifndef IRQLISTENER_H_
#define IRQLISTENER_H_
#include <functional>
#include "IRQConfigure.h"

class IrqListener {
public:
	typedef void ActionType (IrqListener*);

	NiFpga_IrqContext context = NULL;
	uint8_t irqNumber;
	NiFpga_Bool continueWaiting = NiFpga_True;

	IrqListener(uint8_t irqNumber);

	virtual ~IrqListener();

	void wait();
	void stop();

	void unreg() const;

	void setAction(std::function<ActionType>);
private:
	std::function<ActionType> _action;


};

#endif /* IRQLISTENER_H_ */
