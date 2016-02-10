/*
 * EncoderHelper.cpp
 *
 *  Created on: 30 janv. 2016
 *      Author: TinyMan
 */

#include "EncoderHelper.h"
#include "MyRioHelper.h"
#include <time.h>
#include <cstdio>

EncoderHelper::EncoderHelper() {

}

EncoderHelper::~EncoderHelper() {
}

Encoder::~Encoder() {
}

void Encoder::configure(Encoder_ConfigureMask mask,
		Encoder_ConfigureSettings settings) {
	Encoder_Configure(&_channel, mask, settings);
}

void Encoder::clearOverflow() {
	configure(Encoder_Overflow, Encoder_ClearOverflow);
}

void Encoder::clearError() {
	configure(Encoder_Error, Encoder_ClearError);
}

void Encoder::setMode(bool quadPhase) {
	Encoder_ConfigureSettings mode = quadPhase ? Encoder_QuadPhase : Encoder_StepDirection;
	configure(Encoder_SignalMode, mode);
}

void Encoder::reset() {
	configure(Encoder_Reset, Encoder_ResetCounter);
}

void Encoder::enable(bool quadPhase) {
	uint8_t mode = quadPhase ? Encoder_QuadPhase : Encoder_StepDirection;
	configure(Encoder_ConfigureMask(Encoder_Enable | Encoder_SignalMode),
			Encoder_ConfigureSettings(Encoder_Enabled | mode));

	uint8_t selectReg;
	/*
	 * Encoder inputs are on pins shared with other onboard devices. To input
	 * from a physical pin, select the encoder on the appropriate SELECT
	 * register.
	 *
	 * Read the value of the SYSSELECTB register.
	 */
	NiFpga_ReadU8(MRio.session, sysSelect, &selectReg);

	/*
	 * Set bit 5 of the SYSSELECTB register to enable ENCB functionality.
	 * The functionality of these bits is specified in the documentation.
	 */
	selectReg = selectReg | (1 << bitNumber);

	/*
	 * Write the updated value of the SYSSELECTB register.
	 */
	NiFpga_WriteU8(MRio.session, sysSelect, selectReg);

}

uint8_t Encoder::status() {
	return Encoder_Status(&_channel);
}


uint32_t Encoder::counter() {
	return Encoder_Counter(&_channel);
}

/**
 * Overview:
 * Demonstrates using the encoder. Reads a step and direction signal from the
 * encoder on connector B. Prints the values to the console.
 *
 * Instructions:
 * 1. Connect a step and direction signal to encoder pins on connector B.
 * 2. Run this program.
 *
 * Output:
 * The program reads the encoder for 60 s. Encoder values are written to the
 * console every 5 s.
 *
 * Note:
 * The Eclipse project defines the preprocessor symbol for the NI myRIO-1900.
 * Change the preprocessor symbol to use this example with the NI myRIO-1950.
 */
int testEncoder() {

	/*
	 * Normally, the main function runs a long running or infinite loop.
	 * Read the encoder output for 60 seconds.
	 */
	time_t currentTime;
	time_t finalTime;
    time_t printTime;

	time(&currentTime);
	finalTime = currentTime + 60;
	printTime = currentTime;

    uint32_t steps;
    const char* direction;
	while (currentTime < finalTime) {
		time(&currentTime);

		/* Don't print every loop iteration. */
		if (currentTime > printTime) {
			steps = MRio.Encoder.A.counter();
			if ((MRio.Encoder.A.status() & Encoder_StDirection)
					== Encoder_Incrementing) {
				direction = "incrementing";
			} else {
				direction = "decrementing";
			}

			printf("Steps %d, Direction: %s\n", steps, direction);

			printTime += 5;
		}
	}
	return 0;
}

