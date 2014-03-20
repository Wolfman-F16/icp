/*
 * usb.c
 *
 * Copyright: (c) 2012 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

#include "usb.h"
#include "usbdrv.h"
#include "usbconfig.h"
#include "oddebug.h"
/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

/**
HID Report Descriptor as in original USB specification (HID Descriptor Tool)
*/
#include "icp.h"

/* ------------------------------------------------------------------------- */

/**
 * USB function setup
*/
uint8_t usbFunctionSetup(uint8_t data[8])
{
  usbRequest_t    *rq = (void *)data;

  usbMsgPtr = reportBuffer;
  /* check for class request type */
  if( (rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {
    DBG1(0x50, &rq->bRequest, 1);   /* debug output: print our request */
    if(rq->bRequest == USBRQ_HID_GET_REPORT) {
      /* wValue: ReportType (highbyte), ReportID (lowbyte) */
      /* we only have one report type, so don't look at wValue */
      return sizeof(reportBuffer);
    } else {
      if(rq->bRequest == USBRQ_HID_SET_REPORT) {
        if (rq->wLength.word == 1) { /* We expect one byte reports */
          return 0xFF; /* Call usbFunctionWrite with data */
        }
      } else {
        if(rq->bRequest == USBRQ_HID_GET_IDLE) {
#if KEYREPEAT > 0
          usbMsgPtr = &idleRate;
          return 1;
#endif
        } else {
          if(rq->bRequest == USBRQ_HID_SET_IDLE) {
#if KEYREPEAT > 0
            idleRate = rq->wValue.bytes[1];
#endif
          } else {
            if(rq->bRequest == USBRQ_HID_GET_PROTOCOL) {
              if (rq->wValue.bytes[1] < 1) {
                protocolVer = rq->wValue.bytes[1];
              }
            } else {
              if(rq->bRequest == USBRQ_HID_SET_PROTOCOL) {
                usbMsgPtr = &protocolVer;
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
