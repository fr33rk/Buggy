/*==============================================================================
File:					DI.Common.Driver.Timer.c
Owner:					M Land
Author(s):				M Land (martinl@deltainstruments.com)
											
Copyright (C): 			Delta Instruments B.V 2011                   
Date: 					08/06/2011                                        
Firmware Version:		0.0                                              	
							                                                
Environment:			MPLAB IDE											
Environment Version:	8.63.00.00										
Compiler:				MPLAB C30        	                            	
Compiler Version:		3.12                                             	
							                                                
Description:					
				                                    			            
Remarks:				                                         
Todo:                                                
				                                    			            
Change Log:
				                                    			            
==============================================================================*/

// Includes from compiler directory.
#include <stdio.h>

// Includes from project directory.
#include "DI.Common.Driver.Timer.h"
#include "DI.Common.Driver.Clock.h"

// Forwarded function prototypes.
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);

/*==============================================================================
Function:		HandleTimer1Interrupt_x
Description:	Available function pointers.
Parameters:		
Returns:		
==============================================================================*/
OnTimer1Interrupt HandleTimer1Interrupt_1;
OnTimer1Interrupt HandleTimer1Interrupt_2;
OnTimer1Interrupt HandleTimer1Interrupt_3;
OnTimer1Interrupt HandleTimer1Interrupt_4;
OnTimer1Interrupt HandleTimer1Interrupt_5;
OnTimer1Interrupt HandleTimer1Interrupt_6;

/*==============================================================================
Function:		_T1Interrupt               			
Description:	This timer interrupt is called by timer 1.
Parameters:		None.
Returns:		None.
==============================================================================*/
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
	IFS0bits.T1IF = 0;
	
	if(HandleTimer1Interrupt_1 != NULL)
		HandleTimer1Interrupt_1();

	if(HandleTimer1Interrupt_2 != NULL)
		HandleTimer1Interrupt_2();
	
	if(HandleTimer1Interrupt_3 != NULL)
		HandleTimer1Interrupt_3();
		
	if(HandleTimer1Interrupt_4 != NULL)
		HandleTimer1Interrupt_4();

	if(HandleTimer1Interrupt_5 != NULL)
		HandleTimer1Interrupt_5();
	
	if(HandleTimer1Interrupt_6 != NULL)
		HandleTimer1Interrupt_6();	
}

/*==============================================================================
Function:		InitMainTimer               			
Description:	Initialize timer 1 and configures the interrupt of this timer.				
Remarks:		The interrupt priority level is set to 2.								
Parameters:		unsigned int aPeriod: Period of the timer in [ms].
Returns:		None.
==============================================================================*/
void InitMainTimer(unsigned int aPeriod)
{
	float timerPeriod;
	
	T1CONbits.TON = 0;		// Stops 16-bit Timer.
	T1CONbits.TSIDL = 0;	// Continue module operation in Idle mode.
	T1CONbits.TGATE = 0;	// Gated time accumulation disabled.
	T1CONbits.TCKPS = 2;	// Timer Input Clock Prescale Select bits (1:64).
	T1CONbits.TSYNC = 0;	// Timer is not synchronized with an external clock input.
	T1CONbits.TCS = 0;		// Internal clock (FCY).
		
	// Calculate the value for the period register.
	timerPeriod = (float) aPeriod / ((1 / (float)FCY) * 64000);
	
	TMR1 = 0; // Clear timer register.
	PR1 = (unsigned int)timerPeriod; // Load the period value;
	
	IPC0bits.T1IP = 0b010;	// Set Timer interrupt priority level to 2.
	IFS0bits.T1IF = 0;		// Clear Timer interrupt flag.
	IEC0bits.T1IE = 1;		// Enable Timer interrupt.
	
	T1CONbits.TON = 1;		// Starts 16-bit Timer.
}
