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
    Operational,
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
        SetLedState(0, true);
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
                    UartSendString("IOTest v0.0.1");
                    SetLedState(0, BlinkSlow);
                    SetLedState(1, BlinkFast);
                    
                    mMainState = Operational;
                }
                else
                {
                    mMainState = Error;
                }                                
                break;

            case Operational:
                UpdateLedState();
                DelayMs(1);
//                TrySendAndReceive();
//                
//                if (UartInMessageBuffer.HasDataAvailable(&UartInMessageBuffer))
//                {
//                    mMainState = EchoCommand;
//                }
//                
                break;
            
//            case EchoCommand:
//                SetLedState(1, false);
//                
//                element = UartInMessageBuffer.GetNext(&UartInMessageBuffer);
//                UartSendString(element.data);
//                
//                mMainState = WaitOnCommand;
//                break;
                
            case Error:
                SetLedState(7, true);

        }
    }

}
