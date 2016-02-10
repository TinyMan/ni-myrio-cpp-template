/*
 * IrqListener.cpp
 *
 *  Created on: 29 janv. 2016
 *      Author: TinyMan
 */

#include "MyRioHelper.h"
#include "IrqListener.h"
#include <cstdio>

IrqListener::IrqListener(uint8_t irqNumber) :
		irqNumber(irqNumber) {

}

IrqListener::~IrqListener() {
	//unreg();
}

// TODO check for errors (uint8_t cast to NiFpga_Irq)
void IrqListener::wait() {
	while (1) {
		uint32_t irqAssert = 0;
		static uint32_t irqCount = 0;

		/*
		 * Stop the calling thread, wait until a selected IRQ is asserted.
		 */
		Irq_Wait(&context, (NiFpga_Irq) irqNumber, &irqAssert,
				&continueWaiting);

		/*
		 * If an IRQ was asserted.
		 */
		if (irqAssert & (1 << irqNumber)) {
			printf("IRQ%d,%d\n", irqNumber, ++irqCount);

			// trigger the action set by the user
			if (_action)
				_action(this);


			/*
			 * Acknowledge the IRQ(s) when the assertion is done.
			 */
			Irq_Acknowledge(irqAssert);


		}

		/*
		 * Check the indicator to see if the new thread is stopped.
		 */
		if (!(continueWaiting)) {
			printf("The IRQ thread ends.\n");
			break;
		}
	}
}

void IrqListener::unreg() const {
	// unregister Irq
	MRio.Irq.Button.unreg(context, irqNumber);
}

void IrqListener::setAction(std::function<ActionType> function) {
	_action = function;
}

void IrqListener::stop() {
	continueWaiting = NiFpga_False;
}

