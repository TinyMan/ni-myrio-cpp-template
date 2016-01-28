#include <iostream>
#include "MyRioHelper.h"

using namespace std;

#if !defined(LoopDuration)
#define LoopDuration    60  /* How long to output the signal, in seconds */
#endif

#if !defined(LoopSteps)
#define LoopSteps       1   /* How long to step between printing, in seconds */
#endif

/**
 * Overview:
 * Demonstrates using the onboard accelerometer. Reads the acceleration in the
 * three directions. Prints the values to the console.
 *
 * Instructions:
 * 1. Run this program.
 * 2. Shake the NI myRIO.
 *
 * Output:
 * The program reads the acceleration for 60 s. Acceleration values are written
 * to the console every 1 s.
 *
 * Note:
 * The Eclipse project defines the preprocessor symbol for the NI myRIO-1900.
 * Change the preprocessor symbol to use this example with the NI myRIO-1950.
 */

int main() {
	time_t currentTime;
	time_t printTime;
	time_t finalTime;
	double x;
	double y;
	double z;

	/*
	 * Normally, the main function runs a long running or infinite loop.
	 * Read the accelerometer output for 60 seconds.
	 */
	time(&currentTime);
	finalTime = currentTime + LoopDuration;
	printTime = currentTime;
	while (currentTime < finalTime) {
		time(&currentTime);

		/* Don't print every loop iteration. */
		if (currentTime > printTime) {
			x = MRio.Accel.readX();
			y = MRio.Accel.readY();
			z = MRio.Accel.readZ();
			printf("X: %g, Y: %g, Z: %g\n", x, y, z);

			printTime += LoopSteps;
		}
	}

}
