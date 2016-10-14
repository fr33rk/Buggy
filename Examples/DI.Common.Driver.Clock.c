/*==============================================================================
File				: DI.Common.Driver.Clock.c
Author(s)			: M Land (martinl@deltainstruments.com)
Copyright (C)		: Delta Instruments B.V 2009/2010                   
Date				: 29/04/2011                                        
Firmware Version	: 0.1                                              	
							                                                
Environment			: MPLAB IDE											
Environment Version	: 8.63.00.00										
Compiler			: MPLAB C30        	                            	
Compiler Version	: 3.22                                             	
							                                                
Description			: 
				                                    			            
Todo				:	                                                
				                                    			            
Change Log			:	                                                			                                    			            
==============================================================================*/

// Includes from compiler directory.


// Includes from project directory.
#include "DI.Common.Driver.Clock.h"

/*==============================================================================
Function:		initSystemClock             				
Description:	Configures the PLL oscillator circuit of the controller which
				will be operate at 40MIPS.

Parameters: 	unsigned char aFrequency: The frequency of the oscillator
				in [MHz]. The range of the frequency is 2-33MHz with a 
				resolution of 1MHz.
Returns:		None.                                                       
==============================================================================*/
void initSystemClock(unsigned char aFrequency)
{
	// VCO input range = 0.8 - 8MHz. 		VCO input = Fin / N1.	
	// VCO output range = 100 - 200MHz. 	VCO output = VCO input * M.
	// Fosc must be 80Mhz for 40 MIPS.		Fosc =  VCO output / N2.
	// Fcy = Fosc/2.

#if defined(VALVE_UNIT_4P_REV0)
	//	Fin = 40MHz.	
	//	M = PLLFBD + 2.
	PLLFBD = 18;
	//	N1 = PLLPRE + 2.
	CLKDIVbits.PLLPRE = 3;	
#else
	//	Fin = 1MHz.	
	//	M = PLLFBD + 2.
	PLLFBD = 158;
	//	N1 = PLLPRE + 2.
	CLKDIVbits.PLLPRE = aFrequency - 2;
#endif

	//	N2 = PLLPOST + 2.
	CLKDIVbits.PLLPOST = 0;
	// Clock switch to incorporate PLL
	__builtin_write_OSCCONH(0x03);
	// Start clock switching to incorporate PLL.
	__builtin_write_OSCCONL(0x01);	
	// Wait for Clock switch to occur			
	while(OSCCONbits.COSC != 0b011);
	// Wait for PLL to lock
	while(OSCCONbits.LOCK!=1);
}
