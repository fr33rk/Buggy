/* 
 * File:   Commands.h
 * Author: Freerk
 *
 * Created on 23 oktober 2016, 19:41
 */

#ifndef COMMANDS_H
#define	COMMANDS_H

#include "Types.h"

typedef enum _CommandType
{
    cmdLed,
    cmdReset
} CommandType;

typedef struct _Command
{
    CommandType Type;
    int16_t Params[8];
    bool Request;
} Command;


#endif	/* COMMANDS_H */

