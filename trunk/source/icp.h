/*
 * Copyright: (c) 2011 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#include "usbconfig.h"

#if USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH != 53
#error change USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH define to 68 in usbconfig.h
#endif

char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH]
    PROGMEM = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x15, 0x00,                    // LOGICAL_MINIMUM (0)
    0x09, 0x04,                    // USAGE (Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x09, 0x31,                    //     USAGE (X)
    0x09, 0x33,                    //     USAGE (Y)
    0x09, 0x34,                    //     USAGE (RX)
    0x09, 0x35,                    //     USAGE (RY)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x04,                    //     REPORT_COUNT (4)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0xc0,                          //   END_COLLECTION
    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x20,                    //   USAGE_MAXIMUM (Button 32)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x20,                    //   REPORT_COUNT (32)
    0x55, 0x00,                    //   UNIT_EXPONENT (0)
    0x65, 0x00,                    //   UNIT (None)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0xc0                           // END_COLLECTION
};

