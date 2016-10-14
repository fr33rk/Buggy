/*==============================================================================
File:					DI.Common.Driver.Timer.h
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

#ifndef DI_COMMON_DRIVER_TIMER_H
#define DI_COMMON_DRIVER_TIMER_H

// Forwarded function prototypes.
typedef void (*OnTimer1Interrupt)(void);

/*==============================================================================
Function:		InitMainTimer               			
Description:	Initialize timer 1 and configures the interrupt of this timer.				
Remarks:		The interrupt priority level is set to 2.								
Parameters:		unsigned int aPeriod: Period of the timer in [ms].
Returns:		None.
==============================================================================*/
void InitMainTimer(unsigned int aPeriod);

#endif
