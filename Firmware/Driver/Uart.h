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

void EnableUartRx();
void EnableUartTx();

void DisableUart();

void UartSendString(const char* text);
void UartSendBytes(const uint8_t *buffer, const uint8_t size);

void HandleUartInterrupts();

#endif	/* UART_H */

