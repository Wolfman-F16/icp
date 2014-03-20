/*
 * usbjoy.h
 *
 * Copyright: (c) 2012 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

#ifndef USBJOY_H_
#define USBJOY_H_

#include <inttypes.h>

/****************************   DEFINITIONS         **************************/
#define USB_INT         	PD3

#define SPI_MOSI        	PB3
#define SPI_MISO        	PB4
#define SPI_SCK         	PB5

#define MUX_A 				PB0
#define MUX_B   			PB1
#define MUX_C  				PB2

#define PWM                 PB3

#define TX                  PD1

// PORT C is input for ADC

// PORT D is input for Keys and has USB interrupt, Pin7 is output

#define NR_OF_AXIS 	5

/****************************   ENUMS & STRUCTS     **************************/
typedef struct {
	unsigned dataRdy:1;
	unsigned adcChn:3;
	unsigned tmrRdy:1;
	unsigned usbRdy:1;
	unsigned brtCtl:1;
	unsigned symOff:1;
} flags_t;

/****************************   GLOBAL VARIABLES    **************************/
flags_t flags;
uint8_t axis[NR_OF_AXIS];
uint8_t btns[8];

/****************************   FUNCTION DECLARATIONS ************************/
void 		initIO(void);
void 		getAdcData(void);
uint8_t     getBtnData(void);
void        processSymOn(void);

#endif /* USBJOY_H_ */
