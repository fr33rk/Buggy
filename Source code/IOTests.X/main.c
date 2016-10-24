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
    WaitOnCommand,
    EchoCommand,
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
    MessageFIFOElement element;
    
    while (true)
    {
        switch (mMainState)
        {
            case Initializing:
                if (initialize())
                {
                    mMainState = WaitOnCommand;
                    UartSendString("IOTest v0.0.1");
                }
                else
                {
                    mMainState = Error;
                }                                
                break;

            case WaitOnCommand:
                SetLED(1, true);
                
                TrySendAndReceive();
                
                if (UartInMessageBuffer.HasDataAvailable(&UartInMessageBuffer))
                {
                    mMainState = EchoCommand;
                }
                
                break;
            
            case EchoCommand:
                SetLED(1, false);
                
                element = UartInMessageBuffer.GetNext(&UartInMessageBuffer);
                UartSendString(element.data);
                
                mMainState = WaitOnCommand;
                break;
                
            case Error:
                SetLED(7, true);

        }
    }

}
