/*
 * main.h
 *
 * Copyright: (c) 2012 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <avr/pgmspace.h>

#include "usbjoy.h"
#include "usb.h"

/****************************   DEFINITIONS         **************************/
#define REVISION 						$Revision: 200 $

#define BEGIN_ENDLESS_LOOP  for(;;) {
#define END_ENDLESS_LOOP    }
#define TRUE 								1
#define FALSE								0

/****************************   GLOBAL VARIABLES    **************************/


/****************************   FUNCTION DECLARATIONS ************************/

/**
  report builder
  USB Joystick INPUT report structure
  Byte 0:     X-axis
  Byte 1:     2bit X-axis, Y-axis
  Byte 2:     4bit Y-axis, 4 hat
  Byte 3:     btn 1-8
  Byte 4:     btn 9-16
  Byte 5:     btn 17-18
*/
static void buildReport()
{
  reportBuffer[0] = (uint8_t)axis[0];
  reportBuffer[1] = (uint8_t)axis[1];
  reportBuffer[2] = (uint8_t)axis[2];
  reportBuffer[3] = (uint8_t)axis[3];
  reportBuffer[4] = btns[0];
  reportBuffer[5] = btns[1];
  reportBuffer[6] = btns[2];
  reportBuffer[7] = btns[3];
}

#endif /* MAIN_H_ */
