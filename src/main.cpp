#include <iostream>
#include "MyRio.h"

using namespace std;

int main() {

	NiFpga_Status status;

	/*
	 * Open the myRIO NiFpga Session.
	 * This function MUST be called before all other functions. After this call
	 * is complete the myRIO target will be ready to be used.
	 */
	status = MyRio_Open();
	if (MyRio_IsNotSuccess(status))
	{
		return status;
	}

	/*
	 * Your application code goes here.
	 */

	/*
	 * Close the myRIO NiFpga Session.
	 * This function MUST be called after all other functions.
	 */
	status = MyRio_Close();

	return status;

}
