/* 
 * File:   AnalogSensors.h
 * Author: deleeufn
 *
 * Created on 06 December 2016, 07:35
 */

#ifndef ANALOGSENSORS_H
#define	ANALOGSENSORS_H

#include "Types.h"

typedef enum ANALOG_SENSOR
{
    DistanceLeft = 0,
    DistanceFront,
    DistanceRight,
    Microphone,
    Light,
} AnalogSensor;

void InitAnalogSensors();

void HandleAdInterrupts();

uint16_t ReadSensor(AnalogSensor sensor);

void StartUpdateAnalogSensors();

#endif	/* ANALOGSENSORS_H */

