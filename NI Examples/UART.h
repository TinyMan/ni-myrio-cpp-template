/*
 * Uart.h
 *
 * Copyright (c) 2013,
 * National Instruments Corporation.
 * All rights reserved.
 */

#ifndef UART_h_
#define UART_h_

#include <stdint.h>
#include <stddef.h>
#include "visa.h"


/**
 * UART parity configurations.
 */
typedef enum
{
    Uart_ParityNone  = 0,
    Uart_ParityOdd   = 1,
    Uart_ParityEven  = 2,
    Uart_ParityMark  = 3,
    Uart_ParitySpace = 4
} Uart_Parity;


/**
 * UART stop bit configurations.
 */
typedef enum
{
    Uart_StopBits1_0 = 10,    /* 1.0 stop bits */
    Uart_StopBits1_5 = 15,    /* 1.5 stop bits */
    Uart_StopBits2_0 = 20     /* 2.0 stop bits */
} Uart_StopBits;


/**
 * Port information for a particular UART.
 */
typedef struct
{
    const char *        name;       /**< Resource name on UART port*/
    ViSession           defaultRM;  /**< Default resource manager session*/
    ViSession           session;      /**< ViSession reference*/
} MyRio_Uart;


#ifdef __cplusplus
extern "C" {
#endif


/**
 * Opens a UART session.
 */
int32_t Uart_Open(MyRio_Uart* port, const uint32_t baud,
                  const uint8_t dataBits, const Uart_StopBits stopBits,
                  const Uart_Parity parity);


/**
 * Closes a UART session.
 */
int32_t Uart_Close(MyRio_Uart* port);


/**
 * Reads binary data from a UART port. If the number of bytes in the UART
 * receive FIFO is less than number bytes to read, this function blocks until either
 * all the bytes are available to be removed from the FIFO, or until a timeout
 * occurs.
 */
int32_t Uart_Read(MyRio_Uart* port, uint8_t* const data,
                  const size_t nData);


/**
 * Writes data to a UART transmit FIFO. If not enough space is available in the
 * FIFO this function blocks until sufficient space is available or a timeout
 * occurs.
 */
int32_t Uart_Write(MyRio_Uart* port, const uint8_t* const data,
                   const size_t nData);


/**
 * Clears UART receive buffer.
 */
int32_t Uart_Clear(MyRio_Uart* port);

#ifdef __cplusplus
}
#endif


#endif /* UART_h_ */
