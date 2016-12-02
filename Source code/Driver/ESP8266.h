/* 
 * File:   ESP8266.h
 * Author: Freerk
 *
 * Created on 20 november 2016, 11:56
 */

#ifndef ESP8266_H
#define	ESP8266_H

#include "Types.h"

bool InitializeEspStateMachine();

void InitInitializeEspStateMachine();

bool StartInitializeEspStateMachine();

bool ProcessConnectionInfo(const char *message);

#endif	/* ESP8266_H */

