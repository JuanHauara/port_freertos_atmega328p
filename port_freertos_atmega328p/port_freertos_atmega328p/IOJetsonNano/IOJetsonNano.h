#ifndef __IOJetsonNano_h__
#define __IOJetsonNano_h__

#include <avr/io.h>
#include "ADC.h"


// Salidas
#define pin_re_de_rs485 PC3
#define soft_serial_rx_rs485 PC1
#define soft_serial_tx_rs485 PC2
#define LED PB0

// Entradas analógicas
#define AI1 ADC6
#define AI2 ADC7

enum analogPinType : uint8_t
{
	TYPE_0_10V = 0,
	TYPE_0_20mA,
};

enum state : bool
{
	OFF = false,
	ON = true
};

// Macros para lectura de entradas digitales
#define DI1 (bool)(PIND & (1<<PD2))  // conectada por defecto, ver esquemático.
//#define DI1 (bool)(PIND & (1<<PD3))
//#define DI1 (bool)(PIND & (1<<PD4))
//#define DI1 (bool)(PIND & (1<<PD5))

//#define DI2 (bool)(PIND & (1<<PD2))
//#define DI2 (bool)(PIND & (1<<PD3))
//#define DI2 (bool)(PIND & (1<<PD4))
#define DI2 (bool)(PIND & (1<<PD5))  // conectada por defecto, ver esquemático.

#define DI3 (bool)(PIND & (1<<PD3))
#define DI4 (bool)(PIND & (1<<PD4))
#define DI5 (bool)(PINC & (1<<PC0))
#define DI6 (bool)(PINB & (1<<PB4))

// Macros salidas digitales
#define LED_ON  (PORTB |= (1<<LED))
#define LED_OFF (PORTB &= ~(1<<LED))
#define LED_TOGGLE (PORTB ^= (1<<LED))
#define DO1_ON  (PORTD |= (1<<PD6))
#define DO1_OFF (PORTD &= ~(1<<PD6))
#define DO1_TOGGLE (PORTD ^= (1<<PD6))
#define DO2_ON  (PORTB |= (1<<PB2))
#define DO2_OFF (PORTB &= ~(1<<PB2))
#define DO2_TOGGLE (PORTB ^= (1<<PB2))
#define DO3_ON  (PORTB |= (1<<PB3))
#define DO3_OFF (PORTB &= ~(1<<PB3))
#define DO3_TOGGLE (PORTB ^= (1<<PB3))
#define DO4_ON  (PORTB |= (1<<PB1))
#define DO4_OFF (PORTB &= ~(1<<PB1))
#define DO4_TOGGLE (PORTB ^= (1<<PB1))
#define DO5_ON  (PORTD |= (1<<PD7))
#define DO5_OFF (PORTD &= ~(1<<PD7))
#define DO5_TOGGLE (PORTD ^= (1<<PD7))
#define DO6_ON  (PORTB |= (1<<PB5))
#define DO6_OFF (PORTB &= ~(1<<PB5))
#define DO6_TOGGLE (PORTB ^= (1<<PB5))

// Macros para leer estados de salidas
#define DO1_STATE (bool)(PORTD & (1<<PD6))
#define DO2_STATE (bool)(PORTB & (1<<PB2))
#define DO3_STATE (bool)(PORTB & (1<<PB3))
#define DO4_STATE (bool)(PORTB & (1<<PB1))
#define DO5_STATE (bool)(PORTD & (1<<PD7))
#define DO6_STATE (bool)(PORTB & (1<<PB5))

void ioInit(void);
bool digitalInput(uint8_t pin);
void digitalOutput(uint8_t pin, bool state);
bool readDigitalOutput(uint8_t pin);
float analogInput(Adc *adc, uint8_t analogPin, analogPinType mode);

#endif