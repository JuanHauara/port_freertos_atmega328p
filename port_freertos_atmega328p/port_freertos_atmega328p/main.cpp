#include <avr/io.h>
#include <util/delay.h>
#include "FreeRTOS.h"
#include "task.h"
#include "IOJetsonNano.h"
#include "UART.h"
#include "Millis.h"


Uart uart;


static void vLEDBlink_task(void * pvParameters) 
{
	uint16_t * parameters = (uint16_t *) pvParameters;
	uint8_t pin = (uint8_t)parameters[0];
	uint16_t delay_ms = parameters[1];
	
	TickType_t xNextWakeTime = xTaskGetTickCount();
	const int delayTime = delay_ms / portTICK_PERIOD_MS;
	
	while (1)
	{
		if (pin == 5)
		{
			uart.println_P(PSTR("task 1"));
		}
		else if (pin == 6)
		{
			uart.println_P(PSTR("task 2"));
		}
		
		if (readDigitalOutput(pin))
		{
			digitalOutput(pin, false);
		} 
		else
		{
			digitalOutput(pin, true);
		}
		vTaskDelayUntil(&xNextWakeTime, delayTime);
	}
}


int main(void)
{	
	ioInit();
	
	init_millis();
	
	//Uart uart;
	uart.init(BAUD_CALC(9600));
	
	Adc adc;
	adc.init(VREF_PIN_AREF, PRESCALER_DIV_128, SINGLE_CONVERSION);
	
	uart.println_P(PSTR("iniciando.."));
	// Secuencia de inicio de los LEDs.
	for (uint8_t i = 0; i < 3; i++)
	{
		//wdt_reset();
		for (uint8_t i = 0; i < 2; i++)
		{
			DO5_ON;
			DO6_ON;
			LED_ON;
			_delay_ms(80);
			DO5_OFF;
			DO6_OFF;
			LED_OFF;
			_delay_ms(100);
		}
		
		_delay_ms(600);
	}
	
	uart.println_P(PSTR("Hello world!"));
	
	uint16_t config_1[] = {5, 300};
	uint16_t config_2[] = {6, 1000};
	
	xTaskCreate(vLEDBlink_task, "LED Blink", configMINIMAL_STACK_SIZE, (void *) config_1, 1, NULL);
	xTaskCreate(vLEDBlink_task, "LED Other Blink", configMINIMAL_STACK_SIZE, (void *) config_2, 1, NULL);

	vTaskStartScheduler();
	
	while (1) 
	{
	}
}

