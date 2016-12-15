/* 
 * File:   DigitalSensors.h
 * Author: deleeufn
 *
 * Created on 14 December 2016, 07:39
 */

#ifndef DIGITALSENSORS_H
#define	DIGITALSENSORS_H

#include "Types.h"

bool Button1Down;
bool Button1Clicked;
bool Button2Down;
bool Button2Clicked;

void InitDigitalSensors();
void HandleDigitalInterrupts();

#endif	/* DIGITALSENSORS_H */

