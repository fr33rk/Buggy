/* 
 * File:   Timer.h
 * Author: Freerk
 *
 * Created on 29 oktober 2016, 15:17
 */

#ifndef TIMER_H
#define	TIMER_H

#include "Types.h"

typedef void (*OnTimerInterrupt)(void);

void HandleTimerInterrupt();

void InitMainTimer();

#endif	/* TIMER_H */

