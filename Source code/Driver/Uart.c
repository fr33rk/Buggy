#include <pic18f4455.h>
#include <string.h>

#include "Uart.h"
#include "BuggyConfig.h"
#include "MessageFIFOBuffer.h"

void TrySend();
void TryReceive();

MessageFIFOBuffer mUartOutMessageBuffer;
MessageFIFOBuffer mUartInMessageBuffer;

MessageFIFOElement *mElementBeingSend;
uint8_t mElementBeingSendIndex;
MessageFIFOElement mElementBeingReceived;
uint8_t mElementBeingReceivedIndex;

/**
 * Initializes the UART module. Messages send and received are buffered in a 5 
 * space fifo buffer. Use 
 * 
 * @param baudrate
 * @return 
 */
bool InitializeUart(const uint32_t baudrate)
{
    unsigned int x;
    x = (_XTAL_FREQ - baudrate * 64) / (baudrate * 64); //SPBRG for Low Baud Rate
    if (x > 255) //If High Baud Rage Required
    {
        x = (_XTAL_FREQ - baudrate * 16) / (baudrate * 16); //SPBRG for High Baud Rate
        BRGH = 1; //Setting High Baud Rate
    }
    if (x < 256)
    {
        SPBRG = x; //Writing SPBRG Register
        SYNC = 0; //Setting Asynchronous Mode, ie UART
        SPEN = 1; //Enables Serial Port
        TRISC7 = 1; //As Prescribed in Datasheet
        TRISC6 = 1; //As Prescribed in Datasheet
        CREN = 1; //Enables Continuous Reception
        TXEN = 1; //Enables Transmission
        
        InitFifo(&mUartOutMessageBuffer);
        mElementBeingSend = NULL;
        mElementBeingSendIndex = 0;
        mElementBeingReceivedIndex = 0;
        memset(&mElementBeingReceived.data[0], '\0', sizeof(mElementBeingReceived.data));
        return true;
    }
    
    return false;
}

void UartSendString(const char* text)
{
    MessageFIFOElement message;
    
    
    uint16_t stringSize = strlen(text);
    if (stringSize > MAX_MESSAGE_SIZE)
    {
        stringSize = MAX_MESSAGE_SIZE;
    }
    
    memcpy(message.data, text, stringSize);
    // Add end of line characters assign string t
    strncpy(&message.data[stringSize], "\r\n\0", 2);     
    mUartOutMessageBuffer.Add(&mUartOutMessageBuffer, &message);
}

void TrySendAndReceive()
{
    TrySend();
    TryReceive();
}

void TryReceive()
{
   if (RCIF) 
   {
       char newCharacter = RCREG;
       bool restart = false;

       mElementBeingReceived.data[mElementBeingReceivedIndex] = newCharacter;
      
       // Now find out if this is the end of the command.
       if (newCharacter == '\n')
       {
           if ((mElementBeingReceivedIndex > 0) && (mElementBeingReceived.data[mElementBeingReceivedIndex] == '\r'))
           {
               // Yes, end of the command.
               mUartInMessageBuffer.Add(&mUartInMessageBuffer, &mElementBeingReceived);
               
               restart = true;
           }
       }
       else
       {
            mElementBeingSendIndex++;
            restart = mElementBeingSendIndex > MAX_MESSAGE_SIZE;
       }
       
       if (restart)
       {
           mElementBeingSendIndex = 0;
           memset((void*)&mElementBeingReceived.data, '\0', sizeof(mElementBeingReceived.data));          
       }
   }
}

void TrySend()
{
    if (TRMT)
    {
        if (mElementBeingSend == NULL)
        {
            if (mUartOutMessageBuffer.HasDataAvailable(&mUartOutMessageBuffer))
            {
                mElementBeingSend = mUartOutMessageBuffer.Peek(&mUartOutMessageBuffer);
            }
        }

        if (mElementBeingSend != NULL)
        {
            char nextCharacter = mElementBeingSend->data[mElementBeingSendIndex];
        
            if (nextCharacter == '\0')
            {
                // Done;
                mElementBeingSend = NULL;
                // Free used buffer.
                mUartOutMessageBuffer.GetNext(&mUartOutMessageBuffer);
            }
            else
            {
                TXREG = nextCharacter;
            }
            
            mElementBeingSendIndex++;
        }
    }    
}
