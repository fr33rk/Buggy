/* 
 * File:   BuggyCommands.h
 * Author: deleeufn
 *
 * Created on 28 November 2016, 07:57
 */

#ifndef BUGGYCOMMANDS_H
#define	BUGGYCOMMANDS_H

typedef enum COMMANDID
{
    cmdVersion = 0x01,
    
} CommandId;


typedef enum ERROR_CODES
{
    errRxFifoBufferOverflow,
} ErrorCode;

#endif	/* BUGGYCOMMANDS_H */
