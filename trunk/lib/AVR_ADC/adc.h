/*
 * adc.h
 *
 *  Created on: 01.01.2010
 *      Author: Wolfman
 */

#ifndef ADC_H_
#define ADC_H_
/****************************   INCLUDES              ************************/
#include <avr/io.h>

/****************************   DEFINES               ************************/
#if __AVR_ATmega8__
#define ADATE ADFR
#endif

#define ADC_CHANNEL_MASK	0x1F
#define ADC_SAMPLES 			4u

/****************************   MACROS                ************************/

/****************************   STRUCTS & ENUMS       ************************/
typedef struct {
  unsigned adcChannel :4;
  unsigned dataRdy :1;
  unsigned reserved :2;
  unsigned conversionComplete :1;
} adcStatus_t;

typedef enum {
  ADC_LEFT_ALIGN = 0x20,
  ADC_RIGHT_ALIGN = 0x00,
  ADC_AREF = 0x00,
  ADC_AVCC = 0x40,
  ADC_INTERN = 0xC0,
  ADC_ISR_EN = 0x01

} adcOptions_e;

/****************************   GLOBAL VARIABLES      ************************/
volatile uint16_t currentAdcValue;
volatile adcStatus_t adcStatus;

/****************************   FUNCTION DECLARATIONS ************************/
void    initAdc(adcOptions_e, uint8_t );
void    setNextAdcChannel(void);
void    setAdcChannelNr(uint8_t);
uint8_t getAdcChannelMax(void);
uint16_t get16BitFilteredAdcData(void);
uint8_t get8BitFilteredAdcData(void);
uint8_t get8BitStabilizedAdcData(uint8_t *, const uint8_t);

void    convert8BitAdcAverage(void);
uint8_t get8BitAdcAveragedData(uint8_t channel, uint8_t *adcValue);

void    convert10BitAdcAverage(void);
uint16_t get10BitAdcAveragedData(uint8_t);

/****************************   INLINE FUNCTION       ************************/
/**
 * enables ADC module
 */
static inline void enableAdc(void) {
  ADCSRA |= (1 << ADEN);
}

/**
 * disables ADC module. Saves power.
 */
static inline void disableAdc(void) {
  ADCSRA &= ~(1 << ADEN);
}

/**
 *
 */
static inline void startAdcConversion(void) {
  if (!(ADCSRA & (1 << ADEN))) {
    enableAdc();
  }
  ADCSRA |= (1 << ADSC);
}

/**
 * actively waits for ADC conversion to complete.
 */
static inline void waitAdcConversionComplete() {
  while (ADCSRA & (1 << ADSC)) {
    ;
  }
}

static inline void setFreeRunning(uint8_t isTrue) {
  if (isTrue)
    ADCSRA |= (1 << ADATE);
  else
    ADCSRA &= ~(1 << ADATE);
}

/**
 * sets adc channel.
 */
static inline void setAdcChannel(uint8_t x) {
  ADMUX &= ~ADC_CHANNEL_MASK;
  ADMUX |= (ADC_CHANNEL_MASK & x);
}

#endif /* ADC_H_ */
