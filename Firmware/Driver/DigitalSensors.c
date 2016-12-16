
#include <pic18f4455.h>

#include "DigitalSensors.h"
#include "Counters.h"
#include "LEDs.h"

bool Button1Down;
bool Button1Clicked;
bool Button2Down;
bool Button2Clicked;

void InitDigitalSensors()
{
    // --- Buttons ---
    TRISBbits.RB4 = 1;
    TRISBbits.RB5 = 1;
    LATB &= ~(0x48);
    
    // --- Line detectors
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    LATB &= ~(0x03);
    
    Button1Down = false;
    Button1Clicked = false;
    Button2Down = false;
    Button2Clicked = false;
    
    // Enable interrupts
    INTCON2bits.RBIP = 0; // RB Port Change Interrupt low priority
    INTCONbits.RBIE = 1; // Enables the RB port change interrupt    
}

void HandleDigitalInterrupts()
{
    // Only RB4:RB7 trigger an interrupt. So change of the Line Detectors does not 
    // trigger an interrupt.
    
    if (INTCONbits.RBIE && INTCONbits.RBIF)
    {
        if (PORTBbits.RB4)
        {
            if (!IsTimerSet(4) || IsTimerExpired(4))
            {
                Button1Down = true;
                Button1Clicked = false;
                ResetTimer(4);
            }
        }
        else if ((!PORTBbits.RB4) && Button1Down)
        {
            Button1Down = false;
            Button1Clicked = true;            
            SetTimer(4, 250);
        }
        
        if (PORTBbits.RB5)
        {
            if (IsTimerExpired(5))
            {
                Button2Down = true;
                Button2Clicked = false;
                ResetTimer(5);
            }
        }
        else if ((!PORTBbits.RB5) && Button2Down)
        {
            Button2Down = false;
            Button2Clicked = true;            
            SetTimer(5, 250);
        }
        
        INTCONbits.RBIF = 0;
    }
}