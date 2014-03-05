/*
 * usb.h
 *
 *  Created on: 01.05.2013
 *      Author: Wolfman
 */

#ifndef USB_H_
#define USB_H_

#include <inttypes.h>

#include "usbconfig.h"

#define REPORT_BUFFER_SIZE  8
#if REPORT_BUFFER_SIZE > 8
#error Report size must not exceed 8 bytes for low-speed devices. Use Report IDs for split data package tx
#endif

/****************************   GLOBAL VARIABLES    **************************/
/*
struct {
 	 byte X
 	 byte Y
 	 byte I
 	 byte J
 	 byte btn 1-8
 	 byte btn 9-16
 	 byte btn 17-24
 	 byte btn 25-32
 	 }
*/
static uint8_t  reportBuffer[REPORT_BUFFER_SIZE];  /* buffer for HID reports */

static uint8_t  protocolVer = 1;                   /* 0 is the boot protocol,*/
                                                   /* 1 is report protocol   */
extern char     usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH];

/****************************   FUNCTION DECLARATIONS ************************/
uint8_t usbFunctionSetup(uint8_t[] );

#endif /* USB_H_ */
