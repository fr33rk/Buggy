/* 
 * File:   AnalogSensors.h
 * Author: deleeufn
 *
 * Created on 06 December 2016, 07:35
 */

#ifndef ANALOGSENSORS_H
#define	ANALOGSENSORS_H

#include "Types.h"

void InitAnalogSensors();

typedef enum ANALOG_SENSOR
{
    DistanceLeft,
    DistanceFront,
    DistanceRight,
    Microphone,
    Light,
} AnalogSensor;

uint16_t ReadSensor(AnalogSensor sensor);

#endif	/* ANALOGSENSORS_H */

