#include <pic18f4455.h>
#include <string.h>

#include "Uart.h"
#include "BuggyConfig.h"

void TrySend();
void TryReceive();

static MessageFIFOBuffer mUartOutMessageBuffer;
MessageFIFOBuffer UartInMessageBuffer;

static MessageFIFOElement *mpElementBeingSend;
static uint8_t mElementBeingSendIndex;
static MessageFIFOElement mElementBeingReceived;
static uint8_t mElementBeingReceivedIndex;

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


        InitFifo(&mUartOutMessageBuffer);
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
 * Enable URAT reception and transmition.
 */
void EnableUart()
{
    RCSTAbits.CREN = 1;   // Enables Continuous Reception
    TXSTAbits.TXEN = 1;   // Enables Transmission    
}

/**
 * Send text via UART. Stringlength should be max MAX_MESSAGE_SIZE.
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
    mUartOutMessageBuffer.Add(&mUartOutMessageBuffer, &message);
}

/**
 * Send and receive data via UART.
 */
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
           if ((mElementBeingReceivedIndex > 0) && (mElementBeingReceived.data[mElementBeingReceivedIndex-1] == '\r'))
           {
               // Yes, end of the command.
               UartInMessageBuffer.Add(&UartInMessageBuffer, &mElementBeingReceived);               
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

void TrySend()
{
    if (TRMT)
    {
        if (mpElementBeingSend == NULL)
        {
            if (mUartOutMessageBuffer.HasDataAvailable(&mUartOutMessageBuffer))
            {
                mpElementBeingSend = mUartOutMessageBuffer.Peek(&mUartOutMessageBuffer);                
            }
        }

        if (mpElementBeingSend != NULL)
        {
            char nextCharacter = mpElementBeingSend->data[mElementBeingSendIndex];
        
            TXREG = nextCharacter;
            mElementBeingSendIndex++;
                        
            if (nextCharacter == '\n')
            {
                // Done;
                mpElementBeingSend = NULL;
                mElementBeingSendIndex = 0;
                // Free used buffer.
                mUartOutMessageBuffer.GetNext(&mUartOutMessageBuffer);
            }
        }
    }    
}

/**
 * Send a text with one argument.
 * @param text, the text to send
 * @param param. the param to add.
 * @returns True, when the text/param combination fitted in one message.
 */
bool UartSendStringWithParam(const char* text, const char *param)
{
    if (strlen(text) + strlen(param) + 1 < MAX_MESSAGE_SIZE)
    {
        char message[MAX_MESSAGE_SIZE];
        strcpy(message, text);
        strcat(message, ",");
        strcat(message, param);
        UartSendString(message);
        return true;
    }
    return false;
}