/* 
 * File:   LEDs.h
 * Author: Freerk
 *
 * Created on 3 oktober 2016, 21:16
 */

#ifndef LEDS_H
#define	LEDS_H

#include "Types.h"

void InitializeLeds();

bool IsLEDSet(uint8_t index);

void SetLED(uint8_t index, bool state);

void SetByteValueInLED(uint8_t value);

#endif	/* LEDS_H */

