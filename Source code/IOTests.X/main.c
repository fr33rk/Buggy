/*
 * File:   main.c
 * Author: Freerk
 *
 * Created on 17 oktober 2016, 21:27
 */


#include <xc.h>
#include "BuggyConfig.h"
#include "LEDs.h"
#include "Types.h"
#include "uart.h"

enum MainState
{
    Initializing,
    Operational,
    Error
} mMainState;

void main(void) 
{
    while (true)
    {
        switch (mMainState)
        {
            case Initializing:
                InitializeLeds();
                if (!InitializeUart(57600))
                {
                    mMainState = Error;
                }
                else
                {
                    SetLED(0, true);
                    mMainState = Operational;
                }
                break;
                
            case Operational:
                SetLED(1, true);
                UartSendString("Who is the man?");
                break;
                
            case Error:
                SetLED(7, true);
            
        }
    }
    
}
