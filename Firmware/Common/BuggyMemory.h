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

typedef struct BUGGY_MEMORY
{
    bool IsInError;
    ErrorCode ErrorCode;
    
    CommandId NextCommand;
    uint16_t NextTaskId;
    uint8_t *NextCommandParams;
    
} BuggyMemory_T;

BuggyMemory_T BuggyMemory;

#endif	/* BUGGYMEMORY_H */

