#include <PIC18F4455.h>
#include <string.h>
#include "Uart.h"
#include "BuggyConfig.h"
#include "MessageFIFOBuffer.h"

MessageFIFOBuffer mUartOutMessageBuffer;
MessageFIFOElement *mElementBeingSend;
uint8_t mElementBeingSendIndex;

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
        return true;
    }

    InitFifo(&mUartOutMessageBuffer);
    mElementBeingSend = NULL;
    mElementBeingSendIndex = 0;

    return false;
}

void UartWrite(char data)
{
    while (!TRMT)
    {
    }
    TXREG = data;
}

void UartSendString(const char* text)
{
    MessageFIFOElement message;
    memcpy(message.data, text, strlen(text));
    mUartOutMessageBuffer.Add(&mUartOutMessageBuffer, &message);
}

void TrySendAndReceive()
{
    if (TRMT)
    {
        if (mElementBeingSend == NULL)
        {
            if (mUartOutMessageBuffer.HasDataAvailable(&mUartOutMessageBuffer))
            {
                MessageFIFOElement *nextElement;
                nextElement = mUartOutMessageBuffer.GetNext();
                memcpy(mElementBeingSend->data, nextElement->data, sizeof (nextElement->data));
            }
        }

        if (mElementBeingSend != NULL)
        {
            if (mElementBeingSend[mElementBeingSendIndex] == '\0')
            {
                // Done;
                mElementBeingSend
            }
            TXREG = mElementBeingSend.
        }
    }

    for (int i = 0; text[i] != '\0'; i++)
    {
        UartWrite(text[i]);
    }
}
