#include <pic18f4455.h>
#include <string.h>
#include <stdlib.h>
#include "Uart.h"
#include "BuggyConfig.h"
#include "LEDs.h"
#include "BuggyCommands.h"
#include "BuggyMemory.h"

// Add global variables here.
MessageFIFOBuffer UartInMessageBuffer;

// Add local variables here.
#ifdef USE_UART_OUT_FIFO
    static MessageFIFOBuffer mUartOutMessageBuffer;
#else
    static MessageFIFOElement mElementBeingSend;
#endif

static MessageFIFOElement *mpElementBeingSend;
static uint8_t mElementBeingSendIndex;
static MessageFIFOElement mElementBeingReceived;
static uint8_t mElementBeingReceivedIndex;

// Add function prototypes here.
void HandleTxInterrupt();
void HandleRxInterrupt();

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
        SPBRG = x;            // Writing SPBRG Register
        TXSTAbits.SYNC = 0;   // Setting Asynchronous Mode, ie UART
        RCSTAbits.SPEN = 1;   // Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
        TRISCbits.TRISC7 = 1; // Asynchronous serial receive data input (EUSART module).
        TRISCbits.TRISC6 = 1; // Asynchronous serial transmit data output (EUSART module); takes priority over port data. User must configure as output.
        
        IPR1bits.RCIP = 0;    // Set the EUSART receive interrupt to low priority.
        PIE1bits.RCIE = 1;    // Enables the EUSART receive interrupt
        IPR1bits.TXIP = 0;    // Set the EUSART transmit interrupt to low priority.

#ifdef USE_UART_OUT_FIFO        
        InitFifo(&mUartOutMessageBuffer);
#endif       
        InitFifo(&UartInMessageBuffer);
        mpElementBeingSend = NULL;
        mElementBeingSendIndex = 0;
        mElementBeingReceivedIndex = 0;
        memset(&mElementBeingReceived.data[0], '\0', sizeof(mElementBeingReceived.data));
        
        return true;
    }
    
    return false;
}

/**
 * Enable UART reception.
 */
void EnableUartRx()
{
    RCSTAbits.CREN = 1;   // Enables Continuous Reception    
}

/**
 * Enable UART transmition.
 */
void EnableUartTx()
{
    TXSTAbits.TXEN = 1;   // Enables Transmission        
}

/**
 * Disable UART reception and transmition;
 */
void DisableUart()
{
    RCSTAbits.CREN = 0;   // Disables Continuous Reception
    TXSTAbits.TXEN = 0;   // Disables Transmission         
}

/**
 * Send text via UART. String length should be max MAX_MESSAGE_SIZE.
 * @param text, the text to send.
 */
void UartSendString(const char* text)
{
    MessageFIFOElement message;

    uint16_t stringSize = strlen(text);
    if (stringSize > MAX_MESSAGE_SIZE)
    {
        stringSize = MAX_MESSAGE_SIZE;
    }
    
    memcpy(message.data, text, stringSize);
    // Add end of line characters
    strncpy(&message.data[stringSize], "\r\n", 2);
    
#ifdef USE_UART_OUT_FIFO    
    mUartOutMessageBuffer.Add(&mUartOutMessageBuffer, &message);
#else
    if (mpElementBeingSend == NULL)
    {
        memcpy(&mElementBeingSend, &message, sizeof(message));        
        mpElementBeingSend = &mElementBeingSend;
    }
    else
    {
#warning Implement Error overflow
    }
#endif        
    
    PIE1bits.TXIE = 1; // Enables the EUSART transmit interrupt
}

void UartSendBytes(const uint8_t *buffer, const uint8_t size)
{
#ifndef USE_UART_OUT_FIFO
    char hexValue[2] = "\0\0";
    
    // Bytes will be send as HEX characters. So 1 byte takes 2 bytes to send.
    if (size < (MAX_MESSAGE_SIZE / 2))
    {
        for (int index = 0; index < size; index++)
        {
            itoa(hexValue, buffer[index], 16);
            
            if (hexValue[1] != '\0')
            {
                mElementBeingSend.data[index * 2] = hexValue[0];
                mElementBeingSend.data[index * 2 + 1] = hexValue[1];
            }
            else
            {
                mElementBeingSend.data[index * 2] = '0';
                mElementBeingSend.data[index * 2 + 1] = hexValue[0];
            }
        }
        
        mElementBeingSend.data[size] = '\r';
        mElementBeingSend.data[size+1] = '\n';
    }
#endif
}

/**
 * Send and receive data via UART.
 */
void HandleUartInterrupts()
{
    if (RC1IE) HandleRxInterrupt();
    if (TX1IE) HandleTxInterrupt();
}

void HandleRxInterrupt()
{
   if (RCIF)    
   {
       char newCharacter = RCREG;
       bool restart = false;
     
       mElementBeingReceived.data[mElementBeingReceivedIndex] = newCharacter;
      
       // Now find out if this is the end of the command.
       if (newCharacter == '\n')
       {
           if ((mElementBeingReceivedIndex > 0) && (mElementBeingReceived.data[mElementBeingReceivedIndex-1] == '\r'))
           {
                // Yes, end of the command.
                // Only add none-empty messages, to prevent buffer overruns.
                if (strlen(mElementBeingReceived.data) > 2)
                {
                    if (UartInMessageBuffer.HasSpaceAvailable(&UartInMessageBuffer))
                    {
                        UartInMessageBuffer.Add(&UartInMessageBuffer, &mElementBeingReceived);               
                    }
                    else
                    {   
                        BuggyMemory.IsInError = true;
                        BuggyMemory.ErrorCode = errRxFifoBufferOverflow;
                    }
                }
                restart = true;                             
           }
       }
       else
       {
           mElementBeingReceivedIndex++;
           restart = mElementBeingSendIndex > MAX_MESSAGE_SIZE;
       }
       
       if (restart)
       {
           mElementBeingReceivedIndex = 0;
           memset((void*)&mElementBeingReceived.data[0], '\0', sizeof(mElementBeingReceived.data));          
       }
   }
}

void HandleTxInterrupt()
{
    if (TXIF)
    {
#ifdef USE_UART_OUT_FIFO            
        if (mpElementBeingSend == NULL)
        {
            if (mUartOutMessageBuffer.HasDataAvailable(&mUartOutMessageBuffer))
            {
                mpElementBeingSend = mUartOutMessageBuffer.Peek(&mUartOutMessageBuffer);                
            }
        }
#endif
        if (mpElementBeingSend != NULL)
        {
            char nextCharacter = mpElementBeingSend->data[mElementBeingSendIndex];
        
            TXREG = nextCharacter; // Clears the TXIF
            mElementBeingSendIndex++;
                        
            if (nextCharacter == '\n')
            {
                // Done;
                mpElementBeingSend = NULL;
                mElementBeingSendIndex = 0;
#ifdef USE_UART_OUT_FIFO                            
                // Free used buffer.
                mUartOutMessageBuffer.GetNext(&mUartOutMessageBuffer);
#endif                
            }
        }
        else
        {
            // Disable interrupt until message is set in the buffer again.
            PIE1bits.TXIE = 0;
        }
    }    
}