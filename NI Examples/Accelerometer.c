/*
 * Example for performing Basic Analog Input and Output
 *
 * Copyright (c) 2013,
 * National Instruments Corporation.
 * All rights reserved.
 */

#include <stdio.h>

/*
 * Include the myRIO header file.
 * The target type must be defined in your project, as a stand-alone #define,
 * or when calling the compiler from the command-line.
 */
#include "MyRio.h"
#include "Accelerometer.h"


/*
 * Declare the myRIO NiFpga_Session so that it can be used by any function in
 * this file. The variable is actually defined in myRIO.c.
 *
 * This removes the need to pass the myrio_session around to every function and
 * only has to be declared when it is being used.
 */
extern NiFpga_Session myrio_session;


/**
 * Reads an accelerometer value from a single register. Reading from
 * the accelerometer is common for all directions.
 *
 * @param[in]  reg  The register address to read from
 * @param[in]  scale_weight The weight for the accelerometer values
 * @return the acceleration value in g's
 */
double Accel_ReadImpl(uint32_t reg, double scale_weight)
{
    NiFpga_Status status;
    uint16_t value;
    double scaledValue;

    /*
     * Get the value of the acceleration value register.
     *
     * The returned NiFpga_Status value is stored for error checking.
     */
    status = NiFpga_ReadU16(myrio_session, reg, &value);

    /*
     * Check if there was an error reading from the read register.
     *
     * If there was an error then the rest of the function cannot complete
     * correctly so print an error message to stdout and return from the
     * function early.
     */
    MyRio_ReturnValueIfNotSuccess(status, 0.0,
           "Could not read from the accelerometer value register!")

    /*
     * The value is always stored in an unsigned 16-bit register, but the value
     * is actually a signed 16-bit value. Cast this value directly to a signed
     * 16-bit value.
     */
    scaledValue = ((int16_t) value) * scale_weight;

    return scaledValue;
}


/**
 * Read the accelerometer value in the X direction.  The channel structure must
 * previously been initialized with the appropriate scale factors with
 * AccelerometerScaling
 *
 * @param[in]  channel  A struct containing the registers for the accelerometer
 *                      to read from
 * @return the accelerometer value where 0 is 0g-force and 1 is 1g-force
 */
double Accel_ReadX(const MyRio_Accl* channel)
{
    return Accel_ReadImpl(channel->xval, channel->scale);
}


/**
 * Read the accelerometer value in the Y direction.  The channel structure must
 * previously been initialized with the appropriate scale factors with
 * AccelerometerScaling
 *
 * @param[in]  channel  A struct containing the registers for the accelerometer
 *                      to read from
 * @return the accelerometer value where 0 is 0g-force and 1 is 1g-force
 */
double Accel_ReadY(const MyRio_Accl* channel)
{
    return Accel_ReadImpl(channel->yval, channel->scale);
}


/**
 * Read the accelerometer value in the Z direction.  The channel structure must
 * previously been initialized with the appropriate scale factors with
 * AccelerometerScaling
 *
 * @param[in]  channel  A struct containing the registers for the accelerometer
 *                      to read from
 * @return the accelerometer value where 0 is 0g-force and 1 is 1g-force
 */
double Accel_ReadZ(const MyRio_Accl* channel)
{
    return Accel_ReadImpl(channel->zval, channel->scale);
}


/**
 * Sets the scale value.
 *
 * @param[in, out] channel  A struct containing the defined constants
 */
void Accel_Scaling(MyRio_Accl* channel)
{
    /*
     * Convert from defined constant to scale.
     */
    channel->scale = 1.0 / channel->scale_wght;
}

