/* 
 * File:   Counters.h
 * Author: deleeufn
 *
 * Created on 25 November 2016, 10:27
 */

#ifndef COUNTERS_H
#define	COUNTERS_H

void UpdateGeneralCounter();

void InitCounters();

bool SetTimer(uint8_t counterNo, uint32_t duration);

bool ResetTimer(uint8_t counterNo);

bool IsTimerSet(uint8_t counterNo);

bool IsTimerExpired(uint8_t counterNo);

#endif	/* COUNTERS_H */

