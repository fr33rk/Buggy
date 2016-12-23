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
#include "DigitalSensors.h"

// Add global variables here.
extern MessageFIFOBuffer UartInMessageBuffer;

// Add local variables here.
enum MainState
{
    Start,
    Initializing,
    Operational,
    Error
} mMainState;

// Add function prototypes here.
void ProcessMessages();

/**
 * Handler for the high priority interrupts.
 */
void interrupt HighPrioInterrupt(void)
{
    if (TMR1IE && TMR1IF)
    {
        HandleTimerInterrupt();
    }   
}

/**
 * Handler for the low priority interrupts.
 */
void interrupt low_priority LowPrioInterrupt(void)
{
    HandleUartInterrupts();
    HandleAdInterrupts();
    HandleDigitalInterrupts();
}

/**
 * Main program loop.
 */
void main(void)
{
    mMainState = Start;

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