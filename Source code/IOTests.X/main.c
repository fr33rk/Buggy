/*
 * File:   main.c
 * Author: Freerk
 *
 * Created on 17 oktober 2016, 21:27
 */


#include <xc.h>
#include <string.h>
#include "BuggyConfig.h"
#include "LEDs.h"
#include "Types.h"
#include "Uart.h"
#include "Timing.h"
#include "MessageFIFOBuffer.h"

enum MainState
{
    Initializing,
    SendMessage,
    WaitUntilMessageIsSend,
    Error
} mMainState;

bool initialize()
{
    InitializeLeds();
    if (!InitializeUart(57600))
    {
        return false;
    } 
    else
    {
        SetLED(0, true);
    }

    return true;
}

void main(void)
{
    while (true)
    {
        switch (mMainState)
        {
            case Initializing:
                if (initialize())
                {
                    mMainState = SendMessage;
                }
                else
                {
                    mMainState = Error;
                }
                break;

            case SendMessage:
                SetLED(1, true);
                UartSendString("Hello world");
                mMainState = WaitUntilMessageIsSend;
                break;
            
            case WaitUntilMessageIsSend:
                TrySendAndReceive();
                break;
                
            case Error:
                SetLED(7, true);

        }
    }

}
