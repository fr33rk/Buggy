/*==============================================================================
File				: DI.Common.Driver.LED.c
Author(s)			: W.F. Bus (wilkob@deltainstruments.com)
					  M Land (martinl@deltainstruments.com)
Copyright (C)		: Delta Instruments B.V 2010                   
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

// Includes form compiler directory.
#if defined(__PIC24H__)
#include <p24Hxxxx.h>

#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>

#else
#error Wrong device is being used.

#endif

// Includes from project directory.
#include "DI.Common.Driver.LED.h"

// Add local variables here.
#if defined(VALVE_UNIT_4P_REV0)

#define ToggleStatusLedGreen {LATAbits.LATA0 = ~LATAbits.LATA0;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATAbits.LATA0 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATAbits.LATA0 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATAbits.LATA1 = ~LATAbits.LATA1;}  // Toggles the red status LED.
#define SetStatusLedRed {LATAbits.LATA1 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATAbits.LATA1 = 0;}  // Turns off the red status LED.


#elif defined(VALVE_UNIT_4P_REV1)

#define ToggleStatusLedGreen {LATAbits.LATA10 = ~LATAbits.LATA10;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATAbits.LATA10 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATAbits.LATA10 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATBbits.LATB13 = ~LATBbits.LATB13;}  // Toggles the red status LED.
#define SetStatusLedRed {LATBbits.LATB13 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATBbits.LATB13 = 0;}  // Turns off the red status LED.


#elif defined(VALVE_UNIT_8P_REV0)

#define ToggleStatusLedGreen {LATGbits.LATG13 = ~LATGbits.LATG13;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATGbits.LATG13 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATGbits.LATG13 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATGbits.LATG12 = ~LATGbits.LATG12;}  // Toggles the red status LED.
#define SetStatusLedRed {LATGbits.LATG12 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATGbits.LATG12 = 0;}  // Turns off the red status LED.


#elif defined(HOMOGENIZER_UNIT)

#define ToggleStatusLedGreen {LATDbits.LATD1 = ~LATDbits.LATD1;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATDbits.LATD1 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATDbits.LATD1 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATDbits.LATD0 = ~LATDbits.LATD0;}  // Toggles the red status LED.
#define SetStatusLedRed {LATDbits.LATD0 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATDbits.LATD0 = 0;}  // Turns off the red status LED.


#elif defined(MOTOR_UNIT)

#define ToggleStatusLedGreen {LATCbits.LATC8 = ~LATCbits.LATC8;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATCbits.LATC8 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATCbits.LATC8 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATCbits.LATC9 = ~LATCbits.LATC9;}  // Toggles the red status LED.
#define SetStatusLedRed {LATCbits.LATC9 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATCbits.LATC9 = 0;}  // Turns off the red status LED.


#elif defined(TEMPERATURE_UNIT_4P)

#define ToggleStatusLedGreen {LATCbits.LATC4 = ~LATCbits.LATC4;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATCbits.LATC4 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATCbits.LATC4 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATCbits.LATC3 = ~LATCbits.LATC3;}  // Toggles the red status LED.
#define SetStatusLedRed {LATCbits.LATC3 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATCbits.LATC3 = 0;}  // Turns off the red status LED.


#elif defined(TEMPERATURE_UNIT_5P)

#define ToggleStatusLedGreen {LATCbits.LATC2 = ~LATCbits.LATC2;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATCbits.LATC2 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATCbits.LATC2 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATCbits.LATC1 = ~LATCbits.LATC1;}  // Toggles the red status LED.
#define SetStatusLedRed {LATCbits.LATC1 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATCbits.LATC1 = 0;}  // Turns off the red status LED.


#elif defined(LPU_ENVIRONMENT_UNIT) || defined(SPU_ENVIRONMENT_UNIT) || defined(SPU_CP_UNIT)

#define ToggleStatusLedGreen {LATAbits.LATA7 = ~LATAbits.LATA7;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATAbits.LATA7 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATAbits.LATA7 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATAbits.LATA10 = ~LATAbits.LATA10;}  // Toggles the red status LED.
#define SetStatusLedRed {LATAbits.LATA10 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATAbits.LATA10 = 0;}  // Turns off the red status LED.


#elif defined(CONDUCTANCE_UNIT)

#define ToggleStatusLedGreen {LATAbits.LATA4 = ~LATAbits.LATA4;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATAbits.LATA4 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATAbits.LATA4 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATBbits.LATB4 = ~LATAbits.LATB4;}  // Toggles the red status LED.
#define SetStatusLedRed {LATBbits.LATB4 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATBbits.LATB4 = 0;}  // Turns off the red status LED.


#elif defined(BASEPLATE_REV0)

#define ToggleStatusLedGreen {LATCbits.LATC5 = ~LATCbits.LATC5;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATCbits.LATC5 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATCbits.LATC5 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATCbits.LATC4 = ~LATCbits.LATC4;}  // Toggles the red status LED.
#define SetStatusLedRed {LATCbits.LATC4 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATCbits.LATC4 = 0;}  // Turns off the red status LED.


#elif defined(BASEPLATE_REV1)

#define ToggleStatusLedGreen {LATCbits.LATC9 = ~LATCbits.LATC9;}  // Toggles the green status LED.
#define SetStatusLedGreen {LATCbits.LATC9 = 1;}  // Turns on the green status LED.
#define ClearStatusLedGreen {LATCbits.LATC9 = 0;}  // Turns off the green status LED.
	
#define ToggleStatusLedRed {LATCbits.LATC8 = ~LATCbits.LATC8;}  // Toggles the red status LED.
#define SetStatusLedRed {LATCbits.LATC8 = 1;}  // Turns on the red status LED.
#define ClearStatusLedRed {LATCbits.LATC8 = 0;}  // Turns off the red status LED.

#else
#error Module or Module unit is not specified as preprocessor in the build options.	

#endif

volatile enmLEDState CurrentLEDState;
unsigned int LED_Off = 0;
unsigned int LED_On = 0;

// Add function prototypes here.
void continuousOrange(void);
void blinkOrangeFast(void);
void blinkOrangeSlow(void);
void continuousGreen(void);
void blinkGreenFast(void);
void blinkGreenSlow(void);
void continuousRed(void);
void blinkRedFast(void);
void blinkRedSlow(void);

/*==============================================================================
Function name	: setLEDState               			
Description		: Set the status of the LED. Like the color and duration the LED 
				  is on or off.
								
Parameters		: enmLEDState: The LED state.
Returns			: None.                                               
==============================================================================*/
void setLEDState(enmLEDState aLEDState)
{
	switch(aLEDState)
	{
		case ContinuousOrange:
			if(CurrentLEDState != ContinuousOrange)
			{
				SetStatusLedGreen;
				SetStatusLedRed;
			}
			CurrentLEDState = ContinuousOrange;
			break;
		
		case BlinkOrangeFast:
			if(CurrentLEDState != BlinkOrangeFast)
			{
				SetStatusLedGreen;
				SetStatusLedRed;
				
				LED_On = 250;
				LED_Off = 500;
			}
			CurrentLEDState = BlinkOrangeFast;
			break;
			
		case BlinkOrangeSlow:
			if(CurrentLEDState != BlinkOrangeSlow)
			{
				SetStatusLedGreen;
				SetStatusLedRed;
				
				LED_On = 250;
				LED_Off = 1000;
			}
			CurrentLEDState = BlinkOrangeSlow;
			break;

		case ContinuousGreen:
			if(CurrentLEDState != ContinuousGreen)
			{
				ClearStatusLedRed;
				SetStatusLedGreen;
			}
			CurrentLEDState = ContinuousGreen;
			break;

		case BlinkGreenFast:
			if(CurrentLEDState != BlinkGreenFast)
			{
				SetStatusLedGreen;
				ClearStatusLedRed;
				
				LED_On = 250;
				LED_Off = 500;
			}
			CurrentLEDState = BlinkGreenFast;
			break;
		
		case BlinkGreenSlow:
			if(CurrentLEDState != BlinkGreenSlow)
			{
				ClearStatusLedRed;
				SetStatusLedGreen;
				
				LED_On = 250;
				LED_Off = 1000;
			}
			CurrentLEDState = BlinkGreenSlow;
			break;

		case ContinuousRed:
			if(CurrentLEDState != ContinuousRed)
			{
				ClearStatusLedGreen;
				SetStatusLedRed;
			}
			CurrentLEDState = ContinuousRed;
			break;
			
		case BlinkRedFast:
			if(CurrentLEDState != BlinkRedFast)
			{
				ClearStatusLedGreen;
				SetStatusLedRed;
				
				LED_On = 250;
				LED_Off = 500;
			}
			CurrentLEDState = BlinkRedFast;
			break;

		case BlinkRedSlow:
			if(CurrentLEDState != BlinkRedSlow)
			{
				ClearStatusLedGreen;
				SetStatusLedRed;
				
				LED_On = 250;
				LED_Off = 1000;
			}
			CurrentLEDState = BlinkRedSlow;
			break;
		
		default:
			break;
	}
}

/*==============================================================================
Function name	: UpdateLEDState               			
Description		: Sets the LED on and off and sets the richt collor for the state. 
				  This function is best called by a interrupt timer. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void updateLEDState(void)
{
	switch(CurrentLEDState)
	{
		case ContinuousOrange:
			continuousOrange();
			break;
		
		case BlinkOrangeFast:
			blinkOrangeFast();
			break;
			
		case BlinkOrangeSlow:
			blinkOrangeSlow();
			break;

		case ContinuousGreen:
			continuousGreen();
			break;

		case BlinkGreenFast:
			blinkGreenFast();
			break;
		
		case BlinkGreenSlow:
			blinkGreenSlow();
			break;

		case ContinuousRed:
			continuousRed();
			break;

		case BlinkRedFast:
			blinkRedFast();
			break;
			
		case BlinkRedSlow:
			blinkRedSlow();
			break;
		
		default:
			break;
	}		
}

/*==============================================================================
Function name	: continuousOrange               			
Description		: The LED is continuously orange. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void continuousOrange(void)
{
	SetStatusLedRed;
	SetStatusLedGreen;
}

/*==============================================================================
Function name	: blinkOrangeFast               			
Description		: The LED is blinking orange fast. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void blinkOrangeFast(void)
{
	if(LED_On != 0)
	{
		LED_On--;
	}
	else if(LED_On == 0)
	{
		ClearStatusLedRed;
		ClearStatusLedGreen;
		if(LED_Off != 0)
		{
			LED_Off--;
		}
		else if(LED_Off == 0)
		{
			LED_On = 250;
			LED_Off = 500;
			SetStatusLedGreen;
			SetStatusLedRed;
		}
	}
}

/*==============================================================================
Function name	: blinkOrangeSlow               			
Description		: The LED is blinking orange slow. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void blinkOrangeSlow(void)
{
	if(LED_On != 0)
	{
		LED_On--;
	}
	else if(LED_On == 0)
	{
		ClearStatusLedRed;
		ClearStatusLedGreen;
		if(LED_Off != 0)
		{
			LED_Off--;
		}
		else if(LED_Off == 0)
		{
			LED_On = 250;
			LED_Off = 1000;
			SetStatusLedGreen;
			SetStatusLedRed;
		}
	}
}

/*==============================================================================
Function name	: continuousGreen               			
Description		: The LED is continuously green. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void continuousGreen(void)
{
	SetStatusLedGreen;
}

/*==============================================================================
Function name	: blinkGreenFast               			
Description		: The LED is blinking green fast. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void blinkGreenFast(void)
{
	if(LED_On != 0)
	{
		LED_On--;
	}
	else if(LED_On == 0)
	{
		ClearStatusLedGreen;
		if(LED_Off != 0)
		{
			LED_Off--;
		}
		else if(LED_Off == 0)
		{
			LED_On = 250;
			LED_Off = 500;
			SetStatusLedGreen;
		}
	}
}

/*==============================================================================
Function name	: blinkGreenSlow               			
Description		: The LED is blinking green slow. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void blinkGreenSlow(void)
{
	if(LED_On != 0)
	{
		LED_On--;
	}
	else if(LED_On == 0)
	{
		ClearStatusLedGreen;
		if(LED_Off != 0)
		{
			LED_Off--;
		}
		else if(LED_Off == 0)
		{
			LED_On = 250;
			LED_Off = 1000;
			SetStatusLedGreen;
		}
	}
}

/*==============================================================================
Function name	: continuousRed               			
Description		: The LED is continuously red. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void continuousRed(void)
{
	SetStatusLedRed;
}

/*==============================================================================
Function name	: blinkRedFast               			
Description		: The LED is blinking red fast. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void blinkRedFast(void)
{
	if(LED_On != 0)
	{
		LED_On--;
	}
	else if(LED_On == 0)
	{
		ClearStatusLedRed;
		if(LED_Off != 0)
		{
			LED_Off--;
		}
		else if(LED_Off == 0)
		{
			LED_On = 250;
			LED_Off = 500;
			SetStatusLedRed;
		}
	}
}

/*==============================================================================
Function name	: blinkRedSlow               			
Description		: The LED is blinking red slow. 
								
Parameters		: None.
Returns			: None.                                               
==============================================================================*/
void blinkRedSlow(void)
{
	if(LED_On != 0)
	{
		LED_On--;
	}
	else if(LED_On == 0)
	{
		ClearStatusLedRed;
		if(LED_Off != 0)
		{
			LED_Off--;
		}
		else if(LED_Off == 0)
		{
			LED_On = 250;
			LED_Off = 1000;
			SetStatusLedRed;
		}
	}
}
