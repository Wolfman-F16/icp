/*
 * key.h
 *
 * Copyright: (c) 2012 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 *
 *  REQUIRED DEFINITIONS
 *  ALL_KEYS            // consist of KEY_0 .. KEY_n
 *  KEY_0 .. KEY_n      // numbered 0..n
 *  MAX_KEY = KEY_n
 *  KEY_PORT_OUT        // output port
 *  NR_OF_KEYROWS       // number of input pins
 *  REPEAT_MASK
 *  REPEAT_START
 *  REPEAT_NEXT
 */

#ifndef KEY_H_
#define KEY_H_

#include "usbjoy.h"

#include <avr/io.h>
#include <stdint.h>


/****************************   GLOBAL VARIABLES    **************************/
typedef struct
{
  unsigned dirtyFlag:1;
  unsigned readKeys:1;
} keyState_t;


extern  uint8_t key_state[];      // debounced and inverted key state:
                                        // bit = 1: key pressed
extern  uint8_t key_press[];      // key press detect
extern  uint8_t key_rpt[];        // key long press and repeat
extern  uint8_t currentKeyRow;

volatile keyState_t keyState;

/****************************   FUNCTION DECLARATIONS ************************/
uint8_t get_key_short   ( uint8_t key_mask );
uint8_t get_key_long    ( uint8_t key_mask );
void    readKeys        (void);

/****************************   INLINE FUNCTIONS    **************************/
/**
 * switches to next key row
 */
static inline void switchToNextKeyRow()
{
  currentKeyRow++;
  if(currentKeyRow > MAX_KEY) {
    //reset to zero
    currentKeyRow = KEY_0;
  }
  // pull current row low
  KEY_PORT_OUT |= ALL_KEYS;                  // erase key rows
  KEY_PORT_OUT &= ~(1 << currentKeyRow);     // set current row low
}

/****************************     ISR FUNCTIONS     **************************/
/**
 * Interrupt service routine. Call this in a timer interrupt for triggering
 * call of readKeys() in main loop.
 */
static inline void isrKey()
{
  keyState.readKeys = 1;
}

#endif /* KEY_H_ */
