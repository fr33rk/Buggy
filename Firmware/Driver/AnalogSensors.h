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
    All = 0xFF
} AnalogSensor;

void InitAnalogSensors();

void HandleAdInterrupts();

uint16_t ReadSensor(AnalogSensor sensor);

void StartUpdateAnalogSensors();

uint16_t GetLastReading(AnalogSensor sensor);

#endif	/* ANALOGSENSORS_H */

