/* 
 * File:   Speaker.h
 * Author: Freerk
 *
 * Created on 5 oktober 2016, 21:42
 */

#ifndef SPEAKER_H
#define	SPEAKER_H

#include "Types.h"

void EnableSpeaker();

void Beep(uint16_t duration);

#define DefaultBeep Beep(500);

#endif	/* SPEAKER_H */

