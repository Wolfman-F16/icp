/*
 * timer.h
 *
 *  Created on: 04.10.2009
 *      Author: Wolfman
 */

#ifndef TIMER_ATMEGA_H_
#define TIMER_ATMEGA_H_

#include <avr/io.h>

#if (defined __AVR_ATmega48__)
#define TCCR0   TCCR0B
#define TIMSK   Error: TIMSK must be explicitly defined. E.g. TIMSK2
#define OCR0    OCR0A
#define TIFR    TIFR0
#define TCCR2   TCCR2B
#define OCR2    OCR2A
#endif

/****************************   STRUCTS & ENUMS     **************************/
typedef enum
{
  MAX_TIME = 0x0000,    // 4.19 seconds at 16 MHz and prescaler 1024
  ONE_SECOND = 0x3D09
} time_16bit_e ;

typedef enum
{
	TIMER_NORMAL,
	TIMER_COMPARE,
	TIMER_FAST_PWM,
	TIMER_PWM,
} timerMode_e;

typedef enum
{
	TIMER_EXT_CLOCK_RISE,
	TIMER_EXT_CLOCK_FALL,
	TIMER_PRESCALE_1024,
	TIMER_PRESCALE_256,
	TIMER_PRESCALE_64,
	TIMER_PRESCALE_8,
	TIMER_PRESCALE_1,
	TIMER_PRESCALE_128 = 0x10,
	TIMER_PRESCALE_32,
	TIMER_OFF
} timerPrescale_e;

/****************************   FUNCTION DECLARATIONS ************************/
void initTimer0(timerPrescale_e, timerMode_e);
void initTimer1(timerPrescale_e, timerMode_e);
void initTimer2(timerPrescale_e, timerMode_e);

#if (defined __AVR_ATmega16__) || (defined __AVR_ATmega8515__) || (defined __AVR_ATmega48__)
void setTimer0(uint8_t);
#endif
void setTimer1(time_16bit_e);
void setTimer2(uint8_t);

/****************************   INLINE FUNCTIONS    **************************/



#endif /* TIMER_ATMEGA_H_ */
