#include "ADC.h"


void Adc::init(uint8_t vref, adcPrescaler_t prescaler, uint8_t mode)
{
	/*
	  *Registro ADMUX:
		
		-vref: VREF_PIN_AREF, VREF_AVCC, VREF_INTERNAL_1V1, VREF_INTERNAL_2V56.
	  
	  *Registro ADCSRA:
	  
		-Activa el ADC.
	  
		-prescaler: Setea el ADC clock con el prescaler adecuado. PRESCALER_DIV_2, PRESCALER_DIV_4, PRESCALER_DIV_8, PRESCALER_DIV_16, 
					PRESCALER_DIV_32, PRESCALER_DIV_64 o PRESCALER_DIV_128.
					ADC_clock = F_CPU / prescaler y 50KHz < ADC_clock < 200KHz.
	  
		-mode: Setea el modo de trabajo del ADC. SINGLE_CONVERSION, AUTO_TRIGGER, FREE_RUNNING (ATmega8), INTERRUPT.
			   Se pueden combinar distintos flags, por ejemplo: SINGLE_CONVERSION | INTERRUPT o AUTO_TRIGGER | INTERRUPT.
	*/
	
	ADMUX = vref;
	ADCSRA = (1<<ADEN) | mode | prescaler;
}

#ifndef __AVR_ATmega8__
void Adc::init(uint8_t vref, adcPrescaler_t prescaler, uint8_t mode, autoTriggerSource_t autoTriggerSource)
{
	/*
	  *Registro ADMUX:
	  
		-vref: VREF_PIN_AREF, VREF_AVCC, VREF_INTERNAL_1V1, VREF_INTERNAL_2V56.
	  
	  *Registro ADCSRA:
	  
		-Activa el ADC.
	  
		-prescaler: Setea el ADC clock con el prescaler adecuado. PRESCALER_DIV_2, PRESCALER_DIV_4, PRESCALER_DIV_8, PRESCALER_DIV_16, 
					PRESCALER_DIV_32, PRESCALER_DIV_64 o PRESCALER_DIV_128.
				    ADC_clock = F_CPU / prescaler y 50KHz < ADC_clock < 200KHz.
	  
		-mode: Setea el modo de trabajo del ADC. SINGLE_CONVERSION, AUTO_TRIGGER, FREE_RUNNING (ATmega8), INTERRUPT.
			   Se pueden combinar distintos flags, por ejemplo: SINGLE_CONVERSION | INTERRUPT o AUTO_TRIGGER | INTERRUPT.
			
		-autoTriggerSource: Trigger para iniciar una conversión ADC, ver datasheet. Cualquiera de las opciones en 
							'typedef enum autoTriggerSource'.
	*/
	
	ADMUX = vref;
	ADCSRA = (1<<ADEN) | mode | prescaler;
	ADCSRB = autoTriggerSource;
}
#endif

uint16_t Adc::read(adcChannel_t adcChannel)
{
	#if defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)
	switch (adcChannel)
	{
		// ADC0 - ADC7
		case ADC0:
			ADMUX = (ADMUX & 0xE0);
			ADCSRB &= ~(1<<MUX5);
			break;
			
		case ADC1:
			ADMUX = (ADMUX & 0xE0) | 1;
			ADCSRB &= ~(1<<MUX5);
			break;
			
		case ADC2:
			ADMUX = (ADMUX & 0xE0) | 2;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case ADC3:
			ADMUX = (ADMUX & 0xE0) | 3;
			ADCSRB &= ~(1<<MUX5);
			break;
			
		case ADC4:
			ADMUX = (ADMUX & 0xE0) | 4;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case ADC5:
			ADMUX = (ADMUX & 0xE0) | 5;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case ADC6:
			ADMUX = (ADMUX & 0xE0) | 6;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case ADC7:
			ADMUX = (ADMUX & 0xE0) | 7;
			ADCSRB &= ~(1<<MUX5);
			break;
			
		// ADC8 - ADC15
		case ADC8:
			ADMUX = (ADMUX & 0xE0) | 0;
			ADCSRB |= (1<<MUX5);
			break;
		
		case ADC9:
			ADMUX = (ADMUX & 0xE0) | 1;
			ADCSRB |= (1<<MUX5);
			break;
		
		case ADC10:
			ADMUX = (ADMUX & 0xE0) | 2;
			ADCSRB |= (1<<MUX5);
			break;
		
		case ADC11:
			ADMUX = (ADMUX & 0xE0) | 3;
			ADCSRB |= (1<<MUX5);
			break;
		
		case ADC12:
			ADMUX = (ADMUX & 0xE0) | 4;
			ADCSRB |= (1<<MUX5);
			break;
		
		case ADC13:
			ADMUX = (ADMUX & 0xE0) | 5;
			ADCSRB |= (1<<MUX5);
			break;
		
		case ADC14:
			ADMUX = (ADMUX & 0xE0) | 6;
			ADCSRB |= (1<<MUX5);
			break;
		
		case ADC15:
			ADMUX = (ADMUX & 0xE0) | 7;
			ADCSRB |= (1<<MUX5);
			break;
			
		// Modo diferencial con ganancia
		case DIF_ADC0_ADC0_10X:
			ADMUX = (ADMUX & 0xE0) | 8;
			ADCSRB &= ~(1<<MUX5);
			break;
			
		case DIF_ADC1_ADC0_10X:
			ADMUX = (ADMUX & 0xE0) | 9;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC0_ADC0_200X:
			ADMUX = (ADMUX & 0xE0) | 10;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC1_ADC0_200X:
			ADMUX = (ADMUX & 0xE0) | 11;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC2_ADC2_10X:
			ADMUX = (ADMUX & 0xE0) | 12;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC3_ADC2_10X:
			ADMUX = (ADMUX & 0xE0) | 13;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC2_ADC2_200X:
			ADMUX = (ADMUX & 0xE0) | 14;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC3_ADC2_200X:
			ADMUX = (ADMUX & 0xE0) | 15;
			ADCSRB &= ~(1<<MUX5);
			break;
			
		// Modo diferencial sin ganancia
		case DIF_ADC0_ADC1:
			ADMUX = (ADMUX & 0xE0) | 16;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC1_ADC1:
			ADMUX = (ADMUX & 0xE0) | 17;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC2_ADC1:
			ADMUX = (ADMUX & 0xE0) | 18;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC3_ADC1:
			ADMUX = (ADMUX & 0xE0) | 19;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC4_ADC1:
			ADMUX = (ADMUX & 0xE0) | 20;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC5_ADC1:
			ADMUX = (ADMUX & 0xE0) | 21;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC6_ADC1:
			ADMUX = (ADMUX & 0xE0) | 22;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC7_ADC1:
			ADMUX = (ADMUX & 0xE0) | 23;
			ADCSRB &= ~(1<<MUX5);
			break;
			
		case DIF_ADC0_ADC2:
			ADMUX = (ADMUX & 0xE0) | 24;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC1_ADC2:
			ADMUX = (ADMUX & 0xE0) | 25;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC2_ADC2:
			ADMUX = (ADMUX & 0xE0) | 26;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC3_ADC2:
			ADMUX = (ADMUX & 0xE0) | 27;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC4_ADC2:
			ADMUX = (ADMUX & 0xE0) | 28;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case DIF_ADC5_ADC2:
			ADMUX = (ADMUX & 0xE0) | 29;
			ADCSRB &= ~(1<<MUX5);
			break;
			
		case BGAP_1V1:
			ADMUX = (ADMUX & 0xE0) | 30;
			ADCSRB &= ~(1<<MUX5);
			break;
		
		case GND:
			ADMUX = (ADMUX & 0xE0) | 31;
			ADCSRB &= ~(1<<MUX5);
			break;
			
		default:
			return 0;
			break;
	}
	#elif defined(__AVR_ATmega328P__)
	switch (adcChannel)
	{
		case ADC0:
			ADMUX = (ADMUX & 0xF0);
			break;
		
		case ADC1:
			ADMUX = (ADMUX & 0xF0) | 1;
			break;
		
		case ADC2:
			ADMUX = (ADMUX & 0xF0) | 2;
			break;
		
		case ADC3:
			ADMUX = (ADMUX & 0xF0) | 3;
			break;
		
		case ADC4:
			ADMUX = (ADMUX & 0xF0) | 4;
			break;
		
		case ADC5:
			ADMUX = (ADMUX & 0xF0) | 5;
			break;
		
		case ADC6:
			ADMUX = (ADMUX & 0xF0) | 6;
			break;
		
		case ADC7:
			ADMUX = (ADMUX & 0xF0) | 7;
			break;
		
		case TEMPERATURE_SENSOR:
			ADMUX = (ADMUX & 0xF0) | 8;
			break;
		
		case BGAP_1V1:
			ADMUX = (ADMUX & 0xF0) | 14;
			break;
			
		case GND:
			ADMUX = (ADMUX & 0xF0) | 15;
			break;
		
		default:
			return 0;
			break;
	}
	#elif defined(__AVR_ATmega8__)
	switch (adcChannel)
	{
		case ADC0:
			ADMUX = (ADMUX & 0xF0) | 0;
			break;
		
		case ADC1:
			ADMUX = (ADMUX & 0xF0) | 1;
			break;
		
		case ADC2:
			ADMUX = (ADMUX & 0xF0) | 2;
			break;
		
		case ADC3:
			ADMUX = (ADMUX & 0xF0) | 3;
			break;
		
		case ADC4:
			ADMUX = (ADMUX & 0xF0) | 4;
			break;
		
		case ADC5:
			ADMUX = (ADMUX & 0xF0) | 5;
			break;
		
		case ADC6:
			ADMUX = (ADMUX & 0xF0) | 6;
			break;
		
		case ADC7:
			ADMUX = (ADMUX & 0xF0) | 7;
			break;
				
		case BGAP_1V3:
			ADMUX = (ADMUX & 0xF0) | 14;
			break;
		
		case GND:
			ADMUX = (ADMUX & 0xF0) | 15;
			break;
		
		default:
			return 0;
			break;
	}
	#endif
	
	ADCSRA |= (1<<ADSC);  // Comienza la conversión
	while (ADCSRA & (1<<ADSC)) {}  // Espera a que finalice la conversión. El bit ADSC se pone en 0 automáticamente cuando finaliza.
	
	return ADC;
}
