/*
 * main.c
 *
 * Copyright: (c) 2012 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

#ifndef F_CPU
#error F_CPU not defined
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "main.h"
#include "usbconfig.h"
#include "oddebug.h"
#include "usbdrv.h"
#include "usb.h"
#include "usbjoy.h"
#include "timer.h"
#include "adc.h"


int main(void) {
                                                        /* Watchdog setup   */
	wdt_enable(WDTO_2S);
	                                                    /* GPIO setup       */
	initIO();
	                                                    /* Timer setup      */
	                                                    /* can't use interrupts because of USB time */
	                                                    /* criticality, so only polling interrupt   */
	setTimer1(0xBC);	                                /* flags using timer 1 for 2ms trigger time */
	initTimer1(TIMER_PRESCALE_64,TIMER_COMPARE);        /* setup for 2 ms                           */
	TIMSK &= ~(1 << OCIE1A);                            /* disable interrupt on timer 1, cause only */
	                                                    /* interested in irq flag                   */
	setTimer2(0);
	initTimer2(TIMER_PRESCALE_1, TIMER_PWM);       /* setup for backlight PWM at ~6kHz         */
	                                                    /* Analog setup     */
	initAdc(ADC_AVCC | ADC_ISR_EN);
	                                                    /* USB setup	    */
	odDebugInit();
	usbInit();

	PORTD &= ~(1 << USB_CFG_DMINUS_BIT);                /* reset PORTD to default state */

	for (uint8_t i = 0; i < REPORT_BUFFER_SIZE; i++) {  /* clear reportBuffer           */
		reportBuffer[i] = 0;
	}

	flags.dataRdy = 1;

	sei();

	BEGIN_ENDLESS_LOOP                                  /* main event loop */

		wdt_reset();
		usbPoll();

		if(flags.usbRdy == 1) {
			if(TIFR & (1 << OCF1A)) {
				TIFR |= (1 << OCF1A);
				if(flags.tmrRdy == 0) {
					flags.tmrRdy = 1;
					getAdcData();						/* get ADC data */
					                                    /* post process adc data for sym button on */
					processSymOn();

                    if(flags.brtCtl) {

                    } else {
                        setTimer2(axis[4]);             /* set new backlight brightness */
                    }
				} else {
					flags.tmrRdy = 0;
					getBtnData();						/* get button data */
				}

				flags.dataRdy = 1;
			}
		}

		if (flags.dataRdy && usbInterruptIsReady()) {
			flags.dataRdy = 0;
			                                            /* use last key and not current key status in */
            buildReport();                              /* order to avoid lost changes in key status. */
			usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
			flags.usbRdy = 1;
		}

	END_ENDLESS_LOOP

	return 0;
}
