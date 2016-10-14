/**
 *   See C file.
 */

#ifndef DI_COMMON_CAN_FIFO_H
#define	DI_COMMON_CAN_FIFO_H

#include "DI.Common.CAN.Defs.Command.h"

// Used buffers for CAN message handling.
typedef enum
{
    BufferDMA = 0x00,
    BufferCANRxFifoBufferInRAM = 0x01,
    BufferCANTxFifoBufferInRAM = 0x02,
} enmFIFOBuffer;

#define MAX_FIFO_ELEMENTS 16

// Struct definition of a FIFO buffer that contains CAN messages.
typedef struct
{
    CANMessage data[MAX_FIFO_ELEMENTS];

	// Internal variables
    uint tail;         
    uint head;
    uint size;

    bool overflow;    // Flag indicating if a buffer overflow occurred.

	// Function pointers to methods that are used with the FIFO buffer.
	//  unfortunately it is not possible to pass 'self' as a parameter.
	//  So when a method is called a reference to the FIFO buffer must be 
    //  passed a the first parameter.
    // The actual methods are linked in the InitFifo method.
    CANMessage*(*AddRaw)(volatile void *, const void *message, const int size);
    void (*Add)(volatile void *, const CANMessage *message);
    CANMessage (*GetNext) (volatile void *);
    bool (*HasDataAvailable)(volatile void *);
    bool (*HasSpaceAvailable)(volatile void *);        
} CANFIFOBuffer;

void InitFifo(volatile CANFIFOBuffer *fifoBuffer);

#endif	/* DI_COMMON_CAN_FIFO_H */

