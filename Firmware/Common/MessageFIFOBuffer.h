/* 
 * File:   MessageFIFOBuffer.h
 * Author: Freerk
 *
 * Created on 18 oktober 2016, 21:19
 */

#ifndef MESSAGEFIFOBUFFER_H
#define	MESSAGEFIFOBUFFER_H

#include "Types.h"

#define MAX_FIFO_ELEMENTS 5
#define MAX_MESSAGE_SIZE 35

// Add 3 extra spaces for <CR><LF>
typedef struct MessageFIFOElement { char data[MAX_MESSAGE_SIZE + 2]; } MessageFIFOElement;

// Struct definition of a FIFO buffer that contains CAN messages.
typedef struct
{
    MessageFIFOElement data[MAX_FIFO_ELEMENTS];

	// Internal variables
    uint16_t tail;         
    uint16_t head;
    uint16_t size;

    bool overflow;    // Flag indicating if a buffer overflow occurred.

	// Function pointers to methods that are used with the FIFO buffer.
	//  unfortunately it is not possible to pass 'self' as a parameter.
	//  So when a method is called a reference to the FIFO buffer must be 
    //  passed a the first parameter.
    // The actual methods are linked in the InitFifo method.
    MessageFIFOElement*(*AddRaw)(volatile void *, const void *message, const int size);
    void (*Add)(volatile void *, const MessageFIFOElement *message);
    MessageFIFOElement (*GetNext) (volatile void *);
    bool (*HasDataAvailable)(volatile void *);
    bool (*HasSpaceAvailable)(volatile void *);        
} MessageFIFOBuffer;

void InitFifo(volatile MessageFIFOBuffer *fifoBuffer);

#endif	/* MESSAGEFIFOBUFFER_H */

