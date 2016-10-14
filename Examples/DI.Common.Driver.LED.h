/*==============================================================================
File				: DI.Common.Driver.LED.h
Author(s)			: W.F. Bus (wilkob@deltainstruments.com)
Copyright (C)		: Delta Instruments B.V 2009/2010                   
Date				: 06/01/2010                                        
Firmware Version	: 0.1                                              	
							                                                
Environment			: MPLAB IDE											
Environment Version	: 8.50.00.00										
Compiler			: MPLAB C30        	                            	
Compiler Version	: 3.22                                             	
							                                                
Description			: LED control.
				                                    			            
Todo				:	                                                
				                                    			            
Change Log			:	                                                			                                    			            
==============================================================================*/
#ifndef DI_COMMON_LED_H
#define DI_COMMON_LED_H

// Add includes here.

// Add global variables here.
typedef enum
{
	ContinuousOrange = 0x0,
	ContinuousGreen = 0x1,
	ContinuousRed = 0x2,
	BlinkOrangeFast = 0x3,
	BlinkGreenFast = 0x4,
	BlinkRedFast = 0x5,
	BlinkOrangeSlow = 0x6,
	BlinkGreenSlow = 0x7,
	BlinkRedSlow = 0x8,	
} enmLEDState;

// Add function prototypes here.

/*==============================================================================
Function name	: setLEDState               			
Description		: Set the status of the LED. Like the color and duration the LED 
				  is on or off.
								
Parameters		: enmLEDState: The LED state.
Returns			: None.                                               
==============================================================================*/
void setLEDState(enmLEDState aLEDState);

/*==============================================================================
Function name	: UpdateLEDState               			
Description		: Sets the LED on and off and sets the richt collor for the state. 
				  This function is best called by a interrupt timer. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void updateLEDState(void);

#endif
