/*
 * Example for accessing the encoder
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
#include "Encoder.h"

/*
 * Declare the myRIO NiFpga_Session so that it can be used by any function in
 * this file. The variable is actually defined in myRIO.c.
 *
 * This removes the need to pass the myrio_session around to every function and
 * only has to be declared when it is being used.
 */
extern NiFpga_Session myrio_session;


/**
 * Sets options for the encoder configuration register.
 *
 * @param[in]  channel  A struct containing the registers on the encoder channel
 *                      to modify.
 * @param[in]  mask     Array of flags that indicate which of the configure
 *                      settings are valid.
 * @param[in]  settings Array of flags that indicate the configuration settings.
 */
void Encoder_Configure(MyRio_Encoder* channel, Encoder_ConfigureMask mask,
                       Encoder_ConfigureSettings settings)
{
    NiFpga_Status status;
    uint8_t cnfgValue;

    /*
     * Get the current value of the configure register.
     *
     * The returned NiFpga_Status value is stored for error checking.
     */
    status = NiFpga_ReadU8(myrio_session, channel->cnfg, &cnfgValue);

    /*
     * Check if there was an error reading from the encoder registers.
     *
     * If there was an error then the rest of the function cannot complete
     * correctly so print an error message to stdout and return from the
     * function early.
     */
    MyRio_ReturnIfNotSuccess(status,
        "Could not read from the encoder configure registers!")

    /*
     * Clear the value of the masked bits in the configure register. This is
     * done so that the correct value can be set later on.
     */
    cnfgValue = cnfgValue & (~mask);

    /*
     * Set the value of the settings in the configure register. If the
     * value to set is 0 this operation would not work unless the bit was
     * previously cleared.
     */
    cnfgValue = cnfgValue | settings;


    /*
     * Write the new value of the configure register to the device.
     */
    NiFpga_MergeStatus(&status,
            NiFpga_WriteU8(myrio_session, channel->cnfg, cnfgValue));

    /*
     * Check if there was an error writing to encoder configure registers.
     *
     * If there was an error then print an error message to stdout.
     */
    MyRio_ReturnIfNotSuccess(status,
            "Could not write to the encoder configure registers!")
}


/**
 * Reads the encoder status, returning the status as bits.
 *
 * @param[in]  channel  A struct containing the registers on the encoder channel
 *                      to read.
 * @return              The status as a bit field.
 */
uint8_t Encoder_Status(MyRio_Encoder* channel)
{
    NiFpga_Status status;
    uint8_t statusValue;

    /*
     * Get the value of the status register.
     *
     * The returned NiFpga_Status value is stored for error checking.
     */
    status = NiFpga_ReadU8(myrio_session, channel->stat, &statusValue);

    /*
     * Check if there was an error reading from the encoder register.
     *
     * If there was an error then the status is undefined.rest Print an
     * error message to stdout and return a default status.
     */
    MyRio_ReturnValueIfNotSuccess(status, 0,
            "Could not read from the encoder status register!");

    /*
     *  Return the value of the status.
     */
    return statusValue;
}


/**
 * Reads the number of steps that the encoder has gone through. The behavior
 * depends on the SignalMode.
 *
 * ENC_QUAD_PHASE:
 * The counter increments when phase A leads phase B and decrements when phase
 * B leads phase A.
 *
 * ENC_SET_AND_DIRECTION:
 * The counter increments when the direction input is low and decrements when
 * the direction input is high.
 *
 * @param[in]  channel  A struct containing the registers on the encoder channel
 *                      to read.
 * @return              The status as a bit field.
 */
uint32_t Encoder_Counter(MyRio_Encoder* channel)
{
     NiFpga_Status status;
     uint32_t counterValue;

    /*
     * Get the value of the counter register.
     *
     * The returned NiFpga_Status value is stored for error checking.
     */
    status = NiFpga_ReadU32(myrio_session, channel->cntr, &counterValue);

    /*
     * Check if there was an error reading from the encoder register.
     *
     * If there was an error then the value of the counter is undefined
     * so print an error message to stdout and return 0.
     */
    MyRio_ReturnValueIfNotSuccess(status, 0,
            "Could not read from the encoder counter register!");

    /*
     * Return the value of the counter.
     */
    return counterValue;
}
