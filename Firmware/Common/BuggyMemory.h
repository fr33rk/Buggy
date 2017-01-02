/* 
 * File:   BuggyMemory.h
 * Author: deleeufn
 *
 * Created on 06 December 2016, 07:27
 */

#ifndef BUGGYMEMORY_H
#define	BUGGYMEMORY_H

#include "Types.h"
#include "BuggyCommands.h"
#include "BuggyMessage.h"
#include "AnalogSensors.h"

typedef struct BUGGY_MEMORY
{
    uint8_t ResetReason;
    bool IsInError;
    ErrorCode ErrorCode;
    AnalogSensor SensorSelected;
    bool SendSensorUpdates;
    uint16_t SendSensorUpdatesTaskId;
    
    BuggyMessage LastMessage;
    BuggyMessage *pLastMessage;    
} BuggyMemory_T;

BuggyMemory_T BuggyMemory;

void StoreBuggyMessage(uint8_t message);

#endif	/* BUGGYMEMORY_H */

