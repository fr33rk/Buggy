/**
 * Contains the implementation of the CAN message FIFO buffer.
 * 
 * Usage:
 *  - Create variable of type MessageFIFOBuffer e.g. FifoA
 *  - Initialize the buffer via InitFifo(&FifoA).
 *  - Add a CAN message via FifoA->Add(&FifoA, &CanMessage);
 *  - Use FifoA->HasDataAvailable(&FifoA) to test if there is an element in the buffer.
 *  - Use FifoA->GetNext(&FifoA), to get the next CAN message from the buffer.
 * 
 * When the an element is added to the buffer and there is no more space the
 *  FifoA->overflow == true. The message is lost!.
 */

#include "MessageFIFOBuffer.h"
#include <string.h>

/**
 * Add a CAN message to the FIFO buffer.
 * @param fifoBuffer,  the buffer where the message should be added to.
 * @param data, pointer to the memory where the message can be found.
 * @param size, the size of the message that needs to be copied.
 * @return 
 */
MessageFIFOElement* addRawToFifo(volatile void *fifoBuffer, const void *data, const int size)
{
    MessageFIFOBuffer* fifoBufferCasted = (MessageFIFOBuffer*) fifoBuffer;
    MessageFIFOElement *usedBuffer = NULL;
    
    if (fifoBufferCasted->HasSpaceAvailable(fifoBufferCasted))
    {
        usedBuffer = &fifoBufferCasted->data[fifoBufferCasted->head];
        memcpy(usedBuffer, data, size);        
        fifoBufferCasted->head = (fifoBufferCasted->head + 1) % fifoBufferCasted->size;
    }
    else
    {
        fifoBufferCasted->overflow = true;
    }
    
    return usedBuffer;
}

/**
 * Add a CAN message to the FIFO buffer.
 * @param fifoBuffer, the buffer where the message should be added to.
 * @param data, the CAN message that should be added to the buffer.
 */
void addMessageToFifo(volatile void *fifoBuffer, const MessageFIFOElement *data)
{
    addRawToFifo(fifoBuffer, data, sizeof(MessageFIFOElement));
}

/**
 * Get the next message from the FIFO buffer.
 * @param fifoBuffer, the buffer to get the CAN message from.
 * @return, the next message from the buffer. The caller needs to check first if there is a message in the buffer.
 */
MessageFIFOElement getNextFromFifo(volatile void *fifoBuffer)
{
    MessageFIFOBuffer* fifoBufferCasted = (MessageFIFOBuffer*) fifoBuffer;

    MessageFIFOElement data = fifoBufferCasted->data[fifoBufferCasted->tail];
    fifoBufferCasted->tail = (fifoBufferCasted->tail + 1) % fifoBufferCasted->size;
    
    return data;
}

/**
 * Get the current element from the FIFO buffer without freeing its space.
 * @param fifoBuffer, the buffer where the element needs to be peeked of.
 * @return pointer to the element in the buffer which is the current tail.
 */
MessageFIFOElement* peek(volatile void *fifoBuffer)
{
    MessageFIFOBuffer* fifoBufferCasted = (MessageFIFOBuffer*) fifoBuffer;
    return &fifoBufferCasted->data[fifoBufferCasted->tail];
}

/**
 * Checks if there is data in the FIFO buffer.
 * @param fifoBuffer, the buffer that needs to be tested.
 * @return true, when there is at least one element in the list.
 */
bool fifoHasDataAvailable(volatile void *fifoBuffer)
{
    MessageFIFOBuffer* fifoBufferCasted = (MessageFIFOBuffer*) fifoBuffer;
    return (fifoBufferCasted->head != fifoBufferCasted->tail);
}

/**
 * Checks if there is room in the FIFO buffer.
 * @param fifoBuffer, the buffer that needs to be checked.
 * @return True, when there is room for at least one additional message.
 */
bool fifoHasSpaceAvailable(volatile void *fifoBuffer)
{
    MessageFIFOBuffer* fifoBufferCasted = (MessageFIFOBuffer*) fifoBuffer;
    return fifoBufferCasted->head != ((fifoBufferCasted->tail - 1 + fifoBufferCasted->size) % fifoBufferCasted->size);
}

/**
 * Initialize the FIFO buffer.
 * @param fifoBuffer, the buffer that needs to be initialized.
 */
void InitFifo(volatile MessageFIFOBuffer *fifoBuffer)
{
    fifoBuffer->head = 0;
    fifoBuffer->tail = 0;
    fifoBuffer->size = MAX_FIFO_ELEMENTS;
    fifoBuffer->overflow = false;

    fifoBuffer->Add = addMessageToFifo;
    fifoBuffer->AddRaw = addRawToFifo;
    fifoBuffer->GetNext = getNextFromFifo;
    fifoBuffer->Peek = peek;
    fifoBuffer->HasDataAvailable = fifoHasDataAvailable;
    fifoBuffer->HasSpaceAvailable = fifoHasSpaceAvailable;
}
