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
    cmdUnknown        = 0x00,
    cmdVersionReq     = 0x02,
    cmdVersion        = 0x03,
    cmdReset          = 0x04,
    cmdResetDone      = 0x05,
    cmdSensorReq      = 0x06,
    cmdSensorResult   = 0x07,
    cmdSteerMotor     = 0x08,
    cmdSteerMotorDone = 0x09,
    cmdSendError      = 0x0A        
} CommandId;


typedef enum ERROR_CODES
{
    errRxFifoBufferOverflow = 0x01,      
    errInvalidMessageSize = 0x02,            
} ErrorCode;

#endif	/* BUGGYCOMMANDS_H */

