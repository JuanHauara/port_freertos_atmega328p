#ifndef __ADC_H__
#define __ADC_H__

#include <avr/io.h>


// Registro ADCSRA
#define SINGLE_CONVERSION 0b00000000

#ifndef __AVR_ATmega8__
	#define AUTO_TRIGGER 0b00100000
#else
	#define FREE_RUNNING 0b00100000  // solo ATmega8
#endif

#define INTERRUPT 0b00001000

typedef enum adcPrescaler : uint8_t
{
	PRESCALER_DIV_2 = 1,
	PRESCALER_DIV_4,
	PRESCALER_DIV_8,
	PRESCALER_DIV_16,
	PRESCALER_DIV_32,
	PRESCALER_DIV_64,
	PRESCALER_DIV_128
} adcPrescaler_t;

// Registro ADCSRB
#ifndef __AVR_ATmega8__
typedef enum autoTriggerSource : uint8_t
{
	FREE_RUNNING_MODE = 0,
	ANALOG_COMPARATOR,
	EXTERNAL_INTERRUPT_REQUEST,
	TIMER0_COMPARE_MATCH_A,
	TIMER0_OVERFLOW,
	TIMER0_COMPARE_MATCH_B,
	TIMER1_OVERFLOW,
	TIMER1_CAPTURE_EVENT,
} autoTriggerSource_t;
#endif

// Registro ADMUX
#define VREF_PIN_AREF 0b00000000
#define VREF_AVCC 0b01000000

#if defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)
	#define VREF_INTERNAL_1V1 0b10000000
#endif

#if defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)||defined(__AVR_ATmega8__)
	#define VREF_INTERNAL_2V56 0b11000000
#elif defined(__AVR_ATmega328P__)
	#define VREF_INTERNAL_1V1 0b11000000
#endif

#if defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)
typedef enum adcChannel : uint8_t
{
	ADC0 = 0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	ADC8,
	ADC9,
	ADC10,
	ADC11,
	ADC12,
	ADC13,
	ADC14,
	ADC15,
	DIF_ADC0_ADC0_10X,
	DIF_ADC1_ADC0_10X,
	DIF_ADC0_ADC0_200X,
	DIF_ADC1_ADC0_200X,
	DIF_ADC2_ADC2_10X,
	DIF_ADC3_ADC2_10X,
	DIF_ADC2_ADC2_200X,
	DIF_ADC3_ADC2_200X,
	DIF_ADC0_ADC1,
	DIF_ADC1_ADC1,
	DIF_ADC2_ADC1,
	DIF_ADC3_ADC1,
	DIF_ADC4_ADC1,
	DIF_ADC5_ADC1,
	DIF_ADC6_ADC1,
	DIF_ADC7_ADC1,
	DIF_ADC0_ADC2,
	DIF_ADC1_ADC2,
	DIF_ADC2_ADC2,
	DIF_ADC3_ADC2,
	DIF_ADC4_ADC2,
	DIF_ADC5_ADC2,
	BGAP_1V1,
	GND
} adcChannel_t;
#endif

#ifdef __AVR_ATmega328P__
typedef enum adcChannel : uint8_t
{
	ADC0 = 0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	TEMPERATURE_SENSOR,
	BGAP_1V1,
	GND
} adcChannel_t;
#endif

#ifdef __AVR_ATmega8__
typedef enum adcChannel : uint8_t
{
	ADC0 = 0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	BGAP_1V3,
	GND
} adcChannel_t;
#endif

class Adc
{
	public:		
		void init(uint8_t vref, adcPrescaler_t prescaler, uint8_t mode);
		#ifndef __AVR_ATmega8__
			void init(uint8_t vref, adcPrescaler_t prescaler, uint8_t mode, autoTriggerSource_t autoTriggerSource);
		#endif
		
		uint16_t read(adcChannel_t adcChannel);
};

#endif