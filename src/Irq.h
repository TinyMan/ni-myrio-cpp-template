/*
 * Irq.h
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */

#ifndef IRQ_H_
#define IRQ_H_

#include "IrqButton.h"

class Irq {
public:
	IrqButton Button;
	Irq();
	virtual ~Irq();
};

#endif /* IRQ_H_ */
