/* 
 * File:   uart.h
 * Author: Freerk
 *
 * Created on 17 oktober 2016, 22:00
 */

#ifndef UART_H
#define	UART_H

#include "Types.h"

bool InitializeUart(const uint32_t baudrate);

void UartSendString(const char* text);

void TrySendAndReceive();

#endif	/* UART_H */
