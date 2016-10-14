/*==============================================================================
File				: DI.Common.Driver.Clock.h
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

#ifndef DI_COMMON_DRIVER_CLOCK_H
#define DI_COMMON_DRIVER_CLOCK_H

// Includes form compiler directory.
#if defined(__PIC24H__)
#include <p24Hxxxx.h>

#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>

#else
#error Wrong device is being used.

#endif

#if defined(FCY_40)
// The uC runs at 40 MIPS.
#define FCY 40000000
	
#else
#error: No device operation speed is specified as preproccesor macro.

#endif

// Define used to initialize the clock frequency of the I2C.
#define I2C_FREQUENCY 400000

/* Specify the frequency of the clock input if the MCU. The range of the frequency
	is 2-33MHz with a resolution of 1MHz.*/
#if defined(SPU_FLUID_MODULE) || defined(BASEPLATE_REV1) || defined (OPTICS_CONTROL_MODULE) || defined(TEMPERATURE_UNIT_5P)
#define CLOCK_FREQUENCY 4

#elif defined(VALVE_UNIT_4P_REV1) || defined(LIQUID_HANDLER) || defined(TEMPERATURE_UNIT_4P) || defined(MOTOR_UNIT) || defined(BASEPLATE_REV0)
#define CLOCK_FREQUENCY 8

#elif defined(VALVE_UNIT_4P_REV0)
#define CLOCK_FREQUENCY 40

#else
#error: No module or unit type is specified as preproccesor macro.
#endif

// Function prototypes.

/*==============================================================================
Function:		initSystemClock             				
Description:	Configures the PLL oscillator circuit of the controller which
				will be operate at 40MIPS.

Parameters: 	unsigned char aFrequency: The frequency of the oscillator
				in [MHz]. The range of the frequency is 2-33MHz with a 
				resolution of 1MHz.
Returns:		None.                                                       
==============================================================================*/
void initSystemClock(unsigned char aFrequency);

#endif
