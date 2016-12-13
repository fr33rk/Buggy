/*
 * File:   main.c
 * Author: Freerk
 *
 * Created on 17 oktober 2016, 21:27
 */

#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include "ESP8266.h"
#include "Uart.h"
#include "Timer.h"
#include "LEDs.h"
#include "Stm.Initialize.h"
#include "Stm.Operational.h"
#include "AnalogSensors.h"

extern MessageFIFOBuffer UartInMessageBuffer;

enum MainState
{
    Start,
    Initializing,
    Operational,
    Error
} mMainState;

void ProcessMessages();

void interrupt HighPrioInterrupt(void)
{
    if (TMR1IE && TMR1IF)
    {
        HandleTimerInterrupt();
    }   
}

void interrupt low_priority LowPrioInterrupt(void)
{
    HandleUartInterrupts();
    HandleAdInterrupts();
}

void main(void)
{
    mMainState = Start;
    
#ifdef SIMULATED
    MessageFIFOElement element;
#endif
    
    while (true)
    {
        if (mMainState >= Operational)
        {
            OperationalEspStateMachine();
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
                    InitOperationalStateMachine();
                    StartOperationalStateMachine();
                    mMainState = Operational;
                }
                break;

            case Operational:
                if (!OperationalStateMachine())
                {
                    mMainState = Error;
                }
                break;
                
            case Error:
                SetLedState(0, ContinuesOn);
        }
    }
}