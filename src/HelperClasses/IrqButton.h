/*
 * ButtonIrq.h
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */

#ifndef IRQBUTTON_H_
#define IRQBUTTON_H_

using namespace std;
#include "MyRio.h"
#include "ButtonIRQ.h"
#include "IrqListener.h"

class IrqButton {
public:
	/*
	 * Helper class for manipulating IrqButton
	 * It uses the Examples from NI to register and unregister Irq
	 */
	IrqButton();
	virtual ~IrqButton();

	/*
	 * Refer to Irq_RegisterButtonIrq
	 * @return a new IrqListener that you can use to attach an action to the interrupt
	 */
	IrqListener* reg(const uint8_t irqNumber, const uint32_t count = 1, const Irq_Button_Type type = Irq_Button_RisingEdge);

	/*
	 * Refer to Irq_UnregisterButtonIrq
	 */
	void unreg(const NiFpga_IrqContext, const uint8_t irqNumber);

private:
	MyRio_IrqButton _channel;
};


int testIrqButton();
#endif /* IRQBUTTON_H_ */
