/*
 * File:   main.c
 * Author: Freerk
 *
 * Created on 17 oktober 2016, 21:27
 */

#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include "BuggyConfig.h"
#include "LEDs.h"
#include "Types.h"
#include "Uart.h"
#include "Timer.h"
#include "MessageFIFOBuffer.h"

extern OnTimerInterrupt HandleTimerInterrupt_0;

enum MainState
{
    Initializing,
    Operational,
    Error
} mMainState;

bool initialize()
{
    InitializeLeds();
    InitMainTimer();
    if (!InitializeUart(57600))
    {
        return false;
    } 
   
    HandleTimerInterrupt_0 = UpdateLedState;

    // Disable USB
    PIE2bits.USBIE = 0;
    
    // Enable interrupts
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;   // Global interrupt enable.

    return true;
}

void interrupt HighPrioInterrupt(void)
{
    if (TMR1IE && TMR1IF)
    {
        HandleTimerInterrupt();
    }
}


void main(void)
{
    mMainState = Initializing;
    
    while (true)
    {
        switch (mMainState)
        {
            case Initializing:
                if (initialize())
                {
                    UartSendString("IOTest v0.0.2");
                    SetLedState(0, BlinkSlow);
                    SetLedState(1, BlinkFast);
                    
                    mMainState = Operational;
                    SetLed(3);  
                    
                    char tmpBuffer[4];
                    UartSendStringWithParam("Test", itoa(tmpBuffer, 0x21, 16));                    
                    UartSendStringWithParam("PIE1", itoa(tmpBuffer, PIE1, 16));
                    UartSendStringWithParam("PIE2", itoa(tmpBuffer, PIE2, 16));
                }
                else
                {
                    mMainState = Error;
                }                                
                break;

            case Operational:
                //UpdateLedState();
                //DelayMs(1);
                SetLed(4);
                TrySendAndReceive();
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
                SetLed(5);

        }
    }

}
