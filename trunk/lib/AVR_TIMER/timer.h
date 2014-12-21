/*
 * timer.h
 *
 *  Created on: 30.09.2012
 *      Author: Wolfman
 */


#if (defined __AVR_ATmega16__)
#include "timer_atmega.h"
#endif
#if (defined __AVR_ATmega48__)
#include "timer_atmega.h"
#endif
#if (defined __AVR_ATmega8__)
#include "timer_atmega.h"
#endif
#if (defined __AVR_AT90S8515__)
#include "timer_at90s8515.h"
#endif

