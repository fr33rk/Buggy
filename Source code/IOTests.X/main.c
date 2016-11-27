/*
 * File:   main.c
 * Author: Freerk
 *
 * Created on 17 oktober 2016, 21:27
 */

#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include "LEDs.h"
#include "Timer.h"
#include "Stm.Initialize.h"
#include "Uart.h"

enum MainState
{
    Start,
    Initializing,
    Operational,
    Error
} mMainState;

void interrupt HighPrioInterrupt(void)
{
    if (TMR1IE && TMR1IF)
    {
        HandleTimerInterrupt();
    }   
}

void interrupt low_priority LowPrioInterrupt(void)
{
    if (RC1IE)
    {
        TryReceive();
    }
}

void main(void)
{
    mMainState = Start;
    
    while (true)
    {
        if (mMainState > Operational)
        {
            TrySend();            
        }
        
        switch (mMainState)
        {
            case Start:
                InitInitializeStateMachine();
                StartInitializeStateMachine();
                mMainState = Initializing;
                break;
 
            case Initializing:
                if (!InitializeStateMachine())
                {
                    mMainState = Operational;
                }
                break;

            case Operational:
                
                break;
                
            case Error:
                SetLedState(0, ContinuesOn);
        }
    }
}
