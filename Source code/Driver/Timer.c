#include "Timer.h"
#include "BuggyConfig.h"

OnTimerInterrupt HandleTimerInterrupt_0;
OnTimerInterrupt HandleTimerInterrupt_1;
/*
OnTimerInterrupt HandleTimerInterrupt_2;
OnTimerInterrupt HandleTimerInterrupt_3;
OnTimerInterrupt HandleTimerInterrupt_4;
OnTimerInterrupt HandleTimerInterrupt_5;
*/

static uint16_t mTmr1Preset;

/**
 * Timer1 interrupt handler.
 */
void HandleTimerInterrupt()
{
    TMR1 = mTmr1Preset;
    
    if (HandleTimerInterrupt_0 != NULL)
        HandleTimerInterrupt_0();
    
    if (HandleTimerInterrupt_1 != NULL)
        HandleTimerInterrupt_1();
    /*
    if (HandleTimerInterrupt_2 != NULL)
        HandleTimerInterrupt_2();
    
    if (HandleTimerInterrupt_3 != NULL)
        HandleTimerInterrupt_3();
    
    if (HandleTimerInterrupt_4 != NULL)
        HandleTimerInterrupt_4();
    
    if (HandleTimerInterrupt_5 != NULL)
        HandleTimerInterrupt_5();
    */
    TMR1IF = 0;
}

/**
 * Initialize the main timer (Timer1).
 */
void InitMainTimer()
{
    // Timer will fire every ms:
    // interval = (_XTAL_FREQ / 4) / 1 (pre-scaler) * (65535 - offset)
    // 1ms = (48000000 / 1000) / 4 / 1 (64535 - 12000)
    
    T1CONbits.RD16 = 1;    // Enables register read/write of Timer1 in one 16-bit operation
    T1CONbits.T1CKPS = 0;  // 1:1 Prescale value
    T1CONbits.T1OSCEN = 0; // Timer1 oscillator is shut off
    T1CONbits.T1SYNC = 1;  // Do not synchronize external clock input
    T1CONbits.TMR1CS = 0;  // Internal clock (FOSC/4)
    
    mTmr1Preset = 65535 - 12000;
    
    TMR1 = mTmr1Preset;
    
    PIR1bits.TMR1IF = 0;   // Clear interrupt flag
    PIE1bits.TMR1IE = 1;   // Enable timer 1 interrupt.
    
    T1CONbits.TMR1ON = 1;  // Enable timer.
}
