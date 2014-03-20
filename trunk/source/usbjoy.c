/*
 * usbjoy.c
 *
 * Copyright: (c) 2012 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "usbjoy.h"
#include "usbconfig.h"
#include "adc.h"

/**
 * initialises hardware ports
 */
void initIO() {
	uint8_t i = 0;
	uint8_t j = 0;
	// ===========   PORT DIRECTION B   ===========
	PORTB = 0;
	DDRB = (1 << MUX_A | 1 << MUX_B | 1 << MUX_C | 1 << PWM);

	// ===========   PORT DIRECTION C   ===========
	// all ADC input

	// ===========   PORT DIRECTION D   ===========
	PORTD |=(1 << USB_CFG_DMINUS_BIT | 1 << USB_CFG_DPLUS_BIT | 1 << USB_INT); 	/* USB 1.1 Device init requires high */
	DDRD |= (1 << USB_CFG_DMINUS_BIT | 1 << USB_CFG_DPLUS_BIT | 1 << USB_INT | 1 << TX);

	while (--j) {                       /* USB Reset by device only required on Watchdog Reset */
		i = 0;
		while (--i)
			;                           /* delay >10ms for USB reset */
	}

	DDRD = (1 << TX);                   /* remove USB reset condition */
	PORTD = 0xF0 |                      /* pull up activate for input pins */
	        (1 << USB_CFG_DMINUS_BIT);  /* seems to be necessary to allow enumeration to be read by USB Hubs */

}

/**
 * read ADC data
 */
void getAdcData() {
	static uint8_t bufIdx[NR_OF_AXIS];
	static uint8_t adcBuffer[NR_OF_AXIS][4];            /* for each axis 4 samples */
	uint8_t currAdc = flags.adcChn;

	if((bufIdx[currAdc] & 0x03) == 0) {
		axis[currAdc] = (adcBuffer[currAdc][1]
		               + adcBuffer[currAdc][2]
							     + adcBuffer[currAdc][3]
							     + (uint8_t)(currentAdcValue>>2)) >> 2;
	} else {
		adcBuffer[currAdc][(bufIdx[currAdc] & 0x03)] = (uint8_t)(currentAdcValue >> 2);
	}
	bufIdx[currAdc]--;
	currentAdcValue = 0;

	currAdc ++;
	if(currAdc >= NR_OF_AXIS) {
		currAdc = 0;
	}
	setAdcChannel(currAdc+1);   /* +1 because first pin is NC */

	flags.adcChn = currAdc;

	startAdcConversion();
}

/**
 * reads button data
 */
uint8_t getBtnData() {

    static uint8_t idx = 0;
    uint8_t input = 0;

    input = (~PIND) & 0xF0;

    if(idx > 6) {
        btns[idx -4] &= 0xF8;
        btns[idx -4] |= input >> 4;
    } else if (idx > 3) {
        btns[idx -4] &= 0xF0;
        btns[idx -4] |= input >> 4;
    } else {
        btns[idx] &= 0x0F;
        btns[idx] |= input;
    }
    idx++;
    idx &= 0x07;

    // switch to next mux channel
    PORTB &= ~0x07;
    PORTB |= idx;

	return 0;
}

void processSymOn() {
    if(axis[1] > 250) {
        flags.symOff = 1;
    } else if (axis[1] < 100 ) {
        btns[3] &= ~0x08;
    } else if (axis[1] < 240 && flags.symOff) {
        flags.symOff = 0;
        btns[3] |= 0x08; /* in_3 and out_7 combination is available */
    }
}
