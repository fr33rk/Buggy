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

typedef union BUGGYMESSAGE
{
    struct
    {
        // Word 0
        uint8_t Command : 7;
        uint8_t RTR : 1;         // Must be dominant (0) for data frames and recessive (1) for remote request frames

        uint16_t TaskId;
        
        // Word 1
        uint8_t Error : 1;
        uint8_t DataSize : 4;    // No of bytes used in the Data array.
        uint8_t Unused : 3;      // Unused

        // Word 2..12
        uint8_t Data[10];        // Data
    };
    uint8_t AsBuffer[14];
} BuggyMessage;

void CreateVersionMessage(BuggyMessage *pmessage);

void ReceiveMessage(const uint8_t *message)

#endif	/* BUGGYMESSAGE_H */

