/*
 * IrqTimer.cpp
 *
 *  Created on: 4 févr. 2016
 *      Author: TinyMan
 */

#include "IrqTimer.h"
#include <time.h>
#include "MyRioHelper.h"
#include <iostream>
#include <thread>

IrqTimer::IrqTimer() {
	_channel.timerWrite = IRQTIMERWRITE;
	_channel.timerSet = IRQTIMERSETTIME;
}

IrqTimer::~IrqTimer() {
}

IrqListener* IrqTimer::reg(uint32_t timeout) {
	IrqListener *l = new IrqListener();
	Irq_RegisterTimerIrq(&_channel, &l->context, timeout);

	return l;
}

void IrqTimer::unreg(const NiFpga_IrqContext& context) {
	Irq_UnregisterTimerIrq(&_channel, context);
}

int IrqTimer::test() {
	int LoopDuration = 10, LoopSteps = 1;
	time_t currentTime;
	time_t printTime;
	time_t finalTime;

	/*
	 * Configure the timer IRQ and set the time interval. The IRQ occurs after the time interval.
	 */
	const uint32_t timeoutValue = 5000000;

	printf("Timer IRQ:\n");

	/* configure Irq Timer */
	IrqListener* listener = MRio.Irq.Timer.reg(timeoutValue);

	/* configure listener */
	listener->setAction([](IrqListener*) {
		std::cout << "Time elapsed" << std::endl;
	});
	/* create waiting thread */
	std::thread t([=]() {
		listener->wait();
	});

	/** then, do whatever you like **/

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
