/* 
 * File:   LEDs.h
 * Author: Freerk
 *
 * Created on 3 oktober 2016, 21:16
 */

#ifndef LEDS_H
#define	LEDS_H
#include "Types.h"

typedef enum
{
    ContinuesOff,    
    ContinuesOn,    
    BlinkSlow,
    BlinkFast
} enmLedState;

void InitializeLeds();

void SetLedState(uint8_t index, enmLedState state);

void UpdateLedState();

void SetByteValueInLed(uint8_t value);

void ClearByteValueInLed();

#endif	/* LEDS_H */

