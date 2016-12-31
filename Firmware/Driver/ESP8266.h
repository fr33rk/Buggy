/* 
 * File:   ESP8266.h
 * Author: Freerk
 *
 * Created on 20 november 2016, 11:56
 */

#ifndef ESP8266_H
#define	ESP8266_H

#include "Types.h"

typedef void (*OnReceivedData)(const uint8_t *);

bool InitializeEspStateMachine();

void InitInitializeEspStateMachine();

bool StartInitializeEspStateMachine();

bool OperationalEspStateMachine();

void SendMessage(const char *message);

void SendBuffer(const uint8_t *buffer, const uint8_t size);

uint8_t GetIpAddress();

#endif	/* ESP8266_H */

