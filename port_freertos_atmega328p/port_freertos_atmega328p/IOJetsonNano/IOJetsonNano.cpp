#include "IOJetsonNano.h"

void ioInit(void)
{
	// Salidas
	DDRD |= (1<<PD6);
	DDRB |= (1<<PB2);
	DDRB |= (1<<PB3);
	DDRB |= (1<<PB1);
	DDRD |= (1<<PD7);
	DDRB |= (1<<PB5);
	DDRB |= (1<<LED);
	DDRC |= (1<<soft_serial_tx_rs485);
	
	// Inicializa las salidas
	DO1_OFF;
	DO2_OFF;
	DO3_OFF;
	DO4_OFF;
	DO5_OFF;
	DO6_OFF;
	LED_OFF;
	PORTC |= (1<<pin_re_de_rs485);  // RS485 en modo Tx
	PORTC &= ~(1<<soft_serial_tx_rs485);
	
	// Entradas digitales
	DDRD &= ~(1<<PD2);
	DDRD &= ~(1<<PD5);
	DDRD &= ~(1<<PD3);
	DDRD &= ~(1<<PD4);
	DDRC &= ~(1<<PC0);
	DDRB &= ~(1<<PB4);
	DDRC &= ~(1<<soft_serial_rx_rs485);
}

bool digitalInput(uint8_t pin)
{
	switch (pin)
	{
		case 1:
			return DI1;
			break;

		case 2:
			return DI2;
			break;

		case 3:
			return DI3;
			break;

		case 4:
			return DI4;
			break;

		case 5:
			return DI5;
			break;

		case 6:
			return DI6;
			break;

		default:
			return 0;
			break;
	}
}

void digitalOutput(uint8_t pin, bool state)
{
	switch (pin)
	{
		case 1:
			if (state)
				DO1_ON;
			else
				DO1_OFF;
			break;

		case 2:
			if (state)
				DO2_ON;
			else
				DO2_OFF;
			break;

		case 3:
			if (state)
				DO3_ON;
			else
				DO3_OFF;
			break;

		case 4:
			if (state)
				DO4_ON;
			else
				DO4_OFF;
			break;
		
		case 5:
			if (state)
				DO5_ON;
			else
				DO5_OFF;
			break;

		case 6:
			if (state)
				DO6_ON;
			else
				DO6_OFF;
			break;
		
		default:
			break;
	}
}

bool readDigitalOutput(uint8_t pin)
{
	switch (pin)
	{
		case 1:
			return DO1_STATE;
			break;

		case 2:
			return DO2_STATE;
			break;

		case 3:
			return DO3_STATE;
			break;

		case 4:
			return DO4_STATE;
			break;

		case 5:
			return DO5_STATE;
			break;

		case 6:
			return DO6_STATE;
			break;
		
		default:
			return 0;
			break;
	}
}

float analogInput(Adc *adc, uint8_t analogPin, analogPinType mode)
{
	uint16_t val;
	
	switch (analogPin)
	{
		case 1:
			val = adc->read(ADC6);  // La primera lectura en este canal se descarta.
			val = adc->read(ADC6);
			
			if (mode == TYPE_0_10V)
			{
				return val*10.344917/1024 + 1.43;
			}
			else
			{
				if (mode == TYPE_0_20mA)
				{
					return (val*83.089646/1024)/1024;
				}
			}
			break;

		case 2:
			val = adc->read(ADC7);  // La primera lectura en este canal se descarta.
			val = adc->read(ADC7);
			
			if (mode == TYPE_0_10V)
			{
				return val*10.344917/1024 + 1.525;
			}
			else
			{
				if (mode == TYPE_0_20mA)
				{
					return (val*83.089646/1024)/1024;
				}
			}
			break;

		default:
			break;
	}

	return -1;
}