/*
 * ButtonIrq.cpp
 *
 *  Created on: 28 janv. 2016
 *      Author: TinyMan
 */
#include <thread>
#include <iostream>

#include "MyRioHelper.h"
#include "IrqButton.h"

IrqButton::IrqButton() {
	/*
	 * Specify the settings that correspond to the IRQ channel
	 * that you need to access.
	 */
	_channel.btnIrqNumber = IRQDI_BTNNO;
	_channel.btnCount = IRQDI_BTNCNT;
	_channel.btnIrqEnable = IRQDI_BTNENA;
	_channel.btnIrqRisingEdge = IRQDI_BTNRISE;
	_channel.btnIrqFallingEdge = IRQDI_BTNFALL;
}

IrqButton::~IrqButton() {

}

IrqListener* IrqButton::reg(const uint8_t irqNumber, const uint32_t count,
		const Irq_Button_Type type) {
	IrqListener *l = new IrqListener(irqNumber);

	Irq_RegisterButtonIrq(&_channel, &l->context, irqNumber, count, type);

	return l;
}

void IrqButton::unreg(const NiFpga_IrqContext context,
		const uint8_t irqNumber) {
	Irq_UnregisterButtonIrq(&_channel, context, irqNumber);
}

int testIrqButton() {
	int LoopDuration = 60, LoopSteps = 1;
	time_t currentTime;
	time_t printTime;
	time_t finalTime;

	/*
	 * Configure the Button IRQ number, incremental times, and trigger type.
	 */
	const uint8_t IrqNumberConfigure = 3;
	const uint32_t CountConfigure = 1;
	const Irq_Button_Type TriggerTypeConfigure = Irq_Button_RisingEdge;

	printf("Button Input IRQ:\n");

	/* configure Irq Button */
	IrqListener* listener = MRio.Irq.Button.reg(IrqNumberConfigure, CountConfigure, TriggerTypeConfigure);

	/* configure listener */
	listener->setAction([](IrqListener*){
		std::cout << "Bouton appuyé !" << std::endl;
	});


	/* create waiting thread */
	std::thread t ([=](){
		listener->wait();
	});

	/*
	 * Normally, the main function runs a long running or infinite loop.
	 * Read the console output for 60 seconds so that you can recognize the
	 * explanation and loop times.
	 */
	std::cout << "starting loop" << std::endl;
	time(&currentTime);
	finalTime = currentTime + LoopDuration;
	printTime = currentTime;
	while (currentTime < finalTime) {
		static uint32_t loopCount = 0;
		time(&currentTime);

		/* Don't print every loop iteration. */
		if (currentTime > printTime) {
			printf("main loop,%d\n", ++loopCount);

			printTime += LoopSteps;
		}
	}

	/*
	 * Set the indicator to end the new thread.
	 */
	listener->continueWaiting = NiFpga_False;

	/*
	 * Wait for the end of the IRQ thread.
	 */
	t.join();

	/*
	 * Distable the button interrupt, so you can configure this I/O next time.
	 * Every IrqConfigure() function should have its corresponding clear function,
	 * and their parameters should also match.
	 */


	listener->unreg();
	delete listener;

	return 0;
}
