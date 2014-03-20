/*
 * key.c
 *
 *  Created on: 01.01.2010
 *      Author: Wolfman
 *
 *  circuit layout and port programming must be as follows
 *  input pull-up                   output
 *  DDRx = 0, PORTx = 1     -|>|-   DDRy = 1, PORTy = 0
 *  if more than 1 output row exists, only one PORT pin may be set low at one time
 *
 * NOTE:
 * to make this useful for momentary push buttons, deletion of button state must be prevented
 * so a pushed button always signals 1, while releasing stops signaling 1.
 * therefore, query of buttons must use a separate state variable
 */

#include "key.h"
#include <avr/interrupt.h>

uint8_t key_state[NR_OF_KEYROWS];   // debounced and inverted key state:
                                    // bit = 1: key pressed
uint8_t key_press[NR_OF_KEYROWS];   // key press detect
uint8_t key_rpt[NR_OF_KEYROWS];     // key long press and repeat
uint8_t currentKeyRow;              // current key row pulled low


/****************************   PRIVATE FUNCTION DECLARATIONS ****************/
uint8_t get_key_rpt     ( uint8_t key_mask );
uint8_t get_key_press   ( uint8_t key_mask );

/*
 check if a key has been pressed. Each pressed key is reported
 only once
 */
uint8_t get_key_press(uint8_t key_mask)
{
  cli();
  // read and clear atomic !
  key_mask &= key_press[currentKeyRow]; // read key(s)
//  key_press[currentKeyRow] ^= key_mask; // clear key(s) with XOR operation
  sei();
  return key_mask;
}

/*
 check if a key has been pressed long enough such that the
 key repeat functionality kicks in. After a small setup delay
 the key is reported being pressed in subsequent calls
 to this function. This simulates the user repeatedly
 pressing and releasing the key.
 */
uint8_t get_key_rpt(uint8_t key_mask)
{
  cli();
  // read and clear atomic !
  key_mask &= key_rpt[currentKeyRow];   // read key(s)
  key_rpt[currentKeyRow] ^= key_mask;   // clear key(s)
  sei();
  return key_mask;
}

/**
 * returns 1 for pressed buttons or flipped switches. release is not signaled!
 * \return  normal key press data
 */

uint8_t get_key_short(uint8_t key_mask)
{
  cli();
  // read key state and key press atomic !

  return get_key_press(~key_state[currentKeyRow] & key_mask);
}

/**
 * \return  repeated key press data
 */
uint8_t get_key_long(uint8_t key_mask)
{
  return get_key_press(get_key_rpt(key_mask));
}

/*
 * reads key inputs. This function has to be called periodically, before calling any of
 * get_key_short() or get_key_long().
 */
void readKeys()
{
  static uint8_t ct0[NR_OF_KEYROWS];
  static uint8_t ct1[NR_OF_KEYROWS];
  static uint8_t rpt[NR_OF_KEYROWS];
  uint8_t temp;

  // apply key mask to input
  temp = KEY_PORT_IN;

  temp = key_state[currentKeyRow] ^ temp; // key changed ?
  // reset or count ct0
  ct0[currentKeyRow] = ~(ct0[currentKeyRow] & temp);
  // reset or count ct1
  ct1[currentKeyRow] = ct0[currentKeyRow] ^ (ct1[currentKeyRow] & temp);
  temp &= ct0[currentKeyRow] & ct1[currentKeyRow]; // count until roll over ?
  key_state[currentKeyRow] ^= temp; // then toggle debounced state
  key_press[currentKeyRow] |= key_state[currentKeyRow] & temp; // 0->1: key press detect

  if ((key_state[currentKeyRow] & REPEAT_MASK) == 0) { // check repeat function
    rpt[currentKeyRow] = REPEAT_START; // start delay
  }
  if (--rpt[currentKeyRow] == 0) {
    rpt[currentKeyRow] = REPEAT_NEXT; // repeat delay
    key_rpt[currentKeyRow] |= key_state[currentKeyRow] & REPEAT_MASK;
  }
  switchToNextKeyRow();
}
