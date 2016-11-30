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

typedef struct BUGGYMESSAGE
{
    // Word 0
    CommandId Command : 7;     // Command ID
    uint8_t RTR : 1;         // Must be dominant (0) for data frames and recessive (1) for remote request frames
    
    // Word 1
    uint8_t DataSize : 4;    // No of bytes used in the Data array.
    uint8_t Unused : 4;      // Unused
    
    // Word 2..12
    uint8_t Data[10];        // Data
} BuggyMessage;

#endif	/* BUGGYMESSAGE_H */

