/*
 * ButtonIRQ.h
 *
 * Copyright (c) 2014,
 * National Instruments.
 * All rights reserved.
 */

#ifndef ButtonIRQ_h_
#define ButtonIRQ_h_

#include "IRQConfigure.h"


#if NiFpga_Cpp
extern "C" {
#endif


/**
 * Flags that indicate whether the Button IRQ is triggered by the rising edge, falling edge, or both edges.
 */
typedef enum
{
    Irq_Button_RisingEdge,      /**< IRQ is triggered by the rising edge */
    Irq_Button_FallingEdge,     /**< IRQ is triggered by the falling edge */
    Irq_Button_Edge             /**< IRQ is triggered by both the rising and falling edge */
} Irq_Button_Type;


/**
 * Registers and settings for a particular button IRQ I/O.
 */
typedef struct
{
    uint32_t btnCount;                /**< Button IRQ count register */
    uint32_t btnIrqNumber;            /**< Button IRQ number register */
    uint32_t btnIrqEnable;            /**< Button IRQ enable register */
    uint32_t btnIrqRisingEdge;        /**< Button IRQ rising edge-triggered register */
    uint32_t btnIrqFallingEdge;       /**< Button IRQ falling edge-triggered register */
    Irq_Channel btnChannel;           /**< Button IRQ supported I/O */
} MyRio_IrqButton;


/**
 * Configure the Button IRQ.
 */
int32_t Irq_RegisterButtonIrq(MyRio_IrqButton* irqChannel, 
                              NiFpga_IrqContext* irqContext,
                              uint8_t irqNumber, 
                              uint32_t count, 
                              Irq_Button_Type type);


/**
 * Clear the button IRQ settings.
 */
int32_t Irq_UnregisterButtonIrq(MyRio_IrqButton* irqChannel, 
                                NiFpga_IrqContext irqContext,
                                uint8_t irqNumber);

#if NiFpga_Cpp
}
#endif

#endif /* ButtonIRQ_h_ */
