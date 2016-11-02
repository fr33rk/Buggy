/* 
 * File:   uart.h
 * Author: Freerk
 *
 * Created on 17 oktober 2016, 22:00
 */

#ifndef UART_H
#define	UART_H

#include "Types.h"
#include "MessageFIFOBuffer.h"

bool InitializeUart(const uint32_t baudrate);

void UartSendString(const char* text);

bool UartSendStringWithParam(const char* text, const char *param);

void TrySendAndReceive();

#endif	/* UART_H */

