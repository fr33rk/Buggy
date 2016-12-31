/* 
 * File:   Message.h
 * Author: deleeufn
 *
 * Created on 28 November 2016, 07:33
 */

#ifndef BUGGYMESSAGE_H
#define	NUGGYMESSAGE_H

#include "Types.h"
#include "BuggyCommands.h"
#include "AnalogSensors.h"

#define BUGGY_MESSAGE_SIZE 15

typedef union
{
    struct
    {
        // Word 0
        uint8_t RTR : 1;         // Must be dominant (0) for data frames and recessive (1) for remote request frames
        uint8_t Command : 7;

        // Words 1 and 2
        uint16_t TaskId;
        
        // Word 3
        uint8_t Error : 1;
        uint8_t DataSize : 2;    // No of bytes used in the Data array.
        uint8_t Unused : 5;      // Unused

        // Word 4..14
        uint8_t Data[11];        // Data
    };
    uint8_t AsBuffer[BUGGY_MESSAGE_SIZE];
} BuggyMessage;

void CreateVersionMessage(BuggyMessage *pmessage, uint16_t taskId);
void CreateSensorResultMessage(BuggyMessage *pMessage, AnalogSensor sensor, uint16_t value, uint16_t taskId);

void ReceiveMessage(const uint8_t *message);

#endif	/* BUGGYMESSAGE_H */

