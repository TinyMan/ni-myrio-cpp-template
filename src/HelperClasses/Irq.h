/*
 * Irq.h
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */

#ifndef IRQ_H_
#define IRQ_H_
using namespace std;
#include "IrqButton.h"
#include "IrqTimer.h"

class Irq {
public:
	IrqButton Button;
	IrqTimer Timer;
	Irq();
	virtual ~Irq();
};

#endif /* IRQ_H_ */
