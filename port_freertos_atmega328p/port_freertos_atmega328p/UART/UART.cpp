#include "UART.h"

// Clase abstracta con métodos virtuales puros, todas las demás clases derivan de esta clase.
char * UartBase::lltoa(int64_t val, char *cstring, int radix) 
{
	/*
		Convierte un número int64_t en un cstring.
		Igual que ltoa() pero con int64_t.
	*/
	
	bool neg;
	char c;
	uint8_t i, k, dig;

	// Null terminator
	cstring[0] = '\0';

	// Only proceed for valid radix
	if ( (radix >= 2) && (radix <= 36) ) 
	{
		// Sign only for base 10
		if ( (radix == 10) && (val < 0) ) 
		{
			neg = true;
			val = -val;
		}
		else 
		{
			neg = false;
		}

		// Convert in reverse order
		i = 1;
		do 
		{
			dig = (uint64_t)val % radix;
			val = (uint64_t)val / radix;
			
			if (dig < 10) 
			{
				cstring[i++] = dig + '0';
			}
			else 
			{
				cstring[i++] = dig - 10 + 'A';
			}
		} while (val);

		// Negative
		if (neg) 
		{
			cstring[i] = '-';
		}
		else 
		{
			i--;
		}

		// Forward order
		k = 0;
		while (k < i) 
		{
			c = cstring[k];
			cstring[k] = cstring[i];
			cstring[i] = c;
			k++;
			i--;
		}
	}

	return cstring;
}
// ---------
void UartBase::txBytes(uint8_t *arrayBytes, uint16_t len)
{
	/*
			Envia un arreglo de Bytes por el puerto serie.
			Es una función bloqueante.
			 
			Dado que esta función generalmente se utiliza para protocolos de
			comunicaciones que usan el puerto UART, es aconsejable deshabilitar
			las interrupciones mientras se está transmitiendo buffer.
		*/
		
	cli();
		
	for (uint16_t i = 0; i < len; i++)
	{
		txByte(arrayBytes[i]);
	}
		
	sei();
}
// ---------
void UartBase::txUint16(uint16_t n, uint8_t base)
{
	/*
			Envia un número uint16_t por el puerto serie y 
			la base puede ser DEC, HEX o BIN.
		 
			Es una función bloqueante.
	*/
		
	char buff[17];
	utoa(n, buff, base);
	print(buff);
}
	
void UartBase::txInt16(int16_t n, uint8_t base)
{
	/*
			Envia un número int16_t por el puerto serie y 
			la base puede ser DEC, HEX o BIN.
		 
			Es una función bloqueante.
	*/
		
	char buff[17];
	itoa(n, buff, base);
	print(buff);
}
// ---------
void UartBase::print(char l)
{
	txByte(l);
}

void UartBase::print(char *cstring)
{
	/*
			Envia un string C terminado en caracter nulo '\0'
			por el puerto serie.
			 
			Es una función bloqueante.
		*/
	 
	uint16_t i = 0;
	while (cstring[i] != '\0')
	{
		txByte(cstring[i]);
		i++;
	}
}

void UartBase::print(bool bit)
{
	if (bit)
		txByte('1');
	else
		txByte('0');
}

void UartBase::print(uint8_t n, uint8_t base)
{
	/*
			Envia un número uint8_t por el puerto serie y 
			la base puede ser DEC, HEX o BIN.
		 
			Es una función bloqueante.
	*/
		
	txUint16(n, base);
}

void UartBase::print(uint16_t n, uint8_t base)
{
	/*
			Envia un número uint16_t por el puerto serie y 
			la base puede ser DEC, HEX o BIN.
		 
			Es una función bloqueante.
	*/
	
	txUint16(n, base);
}

void UartBase::print(int8_t n, uint8_t base)
{
	/*
			Envia un número int8_t por el puerto serie y 
			la base puede ser DEC, HEX o BIN.
		 
			Es una función bloqueante.
	*/
		
	txInt16(n, base);
}	
	
void UartBase::print(int16_t n, uint8_t base)
{
	/*
			Envia un número int16_t por el puerto serie y 
			la base puede ser DEC, HEX o BIN.
		 
			Es una función bloqueante.
	*/
		
	txInt16(n, base);
}
		
void UartBase::print(uint32_t n, uint8_t base)
{
	/*
			Envia un número uint32_t por el puerto serie y 
			la base puede ser DEC, HEX o BIN.
		 
			Es una función bloqueante.
	*/
		
	char buff[33];
	ultoa(n, buff, base);
	print(buff);
}
	
void UartBase::print(int32_t n, uint8_t base)
{
	/*
			Envia un número int32_t por el puerto serie y 
			la base puede ser DEC, HEX o BIN.
		 
			Es una función bloqueante.
	*/
		
	char buff[33];
	ltoa(n, buff, base);
	print(buff);
}
		
void UartBase::print(int64_t n, uint8_t base)
{		
	/*
			Envia un número int64_t por el puerto serie y 
			la base puede ser DEC, HEX o BIN.
		 
			Es una función bloqueante.
	*/
		
	char buff[65];
	lltoa(n, buff, base);
	print(buff);
}
	
void UartBase::print(float n, uint8_t prec)
{
	/*
		Envia un número float por el puerto, prec indica
		la cantidad de números decimales.
		 
		Es una función bloqueante.
	*/
		
	char buff[41];
	dtostrf(n, 4, prec, buff);
	print(buff);
}
// ---------
void UartBase::println(char l)
{
	txByte(l);
	printnewline();
}

void UartBase::println(char *cstring)
{
	print(cstring);
	printnewline();
}

void UartBase::println(bool bit)
{
	print(bit);
	printnewline();
}

void UartBase::println(uint8_t n, uint8_t base)
{
	print(n, base);
	printnewline();
}
	
void UartBase::println(uint16_t n, uint8_t base)
{
	print(n, base);
	printnewline();
}
	
void UartBase::println(int8_t n, uint8_t base)
{
	print(n, base);
	printnewline();
}
	
void UartBase::println(int16_t n, uint8_t base)
{
	print(n, base);
	printnewline();
}
	
void UartBase::println(uint32_t n, uint8_t base)
{
	print(n, base);
	printnewline();
}
	
void UartBase::println(int32_t n, uint8_t base)
{
	print(n, base);
	printnewline();
}
	
void UartBase::println(int64_t n, uint8_t base)
{
	print(n, base);
	printnewline();
}
	
void UartBase::println(float n, uint8_t prec)
{
	print(n, prec);
	printnewline();
}
// ---------
void UartBase::print_P(const char *cstring)
{
	/*
		Envia un string C almacenado en memoria de programa
		por el puerto serie.
			
		Es una función bloqueante.
	*/
	
	uint8_t n;
	do
	{
		n = pgm_read_byte(cstring);
		txByte(n);
		cstring++;
	}while (n != '\0');
}
	
void UartBase::println_P(const char *cstring)
{
	print_P(cstring);
	printnewline();
}
// ---------
void UartBase::printnewline(uint8_t numLn)
{
	for (uint8_t i = 0; i < numLn; i++)
	{
		txByte('\n');
	}
}

void UartBase::printspace(uint8_t numSpace)
{
	for (uint8_t i = 0; i < numSpace; i++)
	{
		txByte(' ');
	}
}

#if defined(__AVR_ATmega8__)||defined(__AVR_ATmega8P__)||defined(__AVR_ATmega16__)   \
||defined(__AVR_ATmega16A__)||defined(__AVR_ATmega32__)||defined(__AVR_ATmega32A__)  \
||defined(__AVR_ATmega8A__)||defined(__AVR_ATmega8L__)
	
	// Clase UART para ATmega8, ATmega8P, ATmega8A...
	// Variables estáticas
	volatile uint8_t Uart::_rxBuffer[SERIAL_BUFF_LEN];
	volatile uint16_t Uart::index;
	volatile bool Uart::flagByteReceived = false;
	volatile bool uart_bufferFull;  // Variable global
		
	void Uart::init(uint16_t ubrr)
	{	
		/*
		 * Inicializa el hardware del puerto UART y devuelve un puntero
		 * al buffer Rx.
		 */
	
		// Set baud rate. Datasheet pag. 222.
		UBRRH = (uint8_t)(ubrr>>8);
		UBRRL = (uint8_t)ubrr;
				
		if (ubrr == 16)
		{
			UCSRA |= (1<<U2X);  // baud rate = 57600. Datasheet pag. 219.
		}
		else
		{
			UCSRA &= ~(1<<U2X);  // baud rate < 57600.
		}
	
		// Enable Rx interrupts and enable receiver and transmitter. Datasheet pag. 220.
		UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
	
		// Set frame format: 8data, 1stop bit. Datasheet pag. 221.
		UCSRC = (1<<UCSZ1)|(1<<UCSZ0);
		
		rxBuffer = (uint8_t *)_rxBuffer;
		
		sei();  // Activa las interrupciones globales.
	}
	
	void Uart::txByte(uint8_t n)
	{
		/*
		 * Envia un Byte por el puerto serie.
		 * 
		 * Es una función bloqueante.
		 */
	
		// Wait for empty transmit buffer
		while ( !(UCSRA & (1<<UDRE)) ) {};
	
		UDR = n;  // Put data into buffer, sends the data
	}
	
	void Uart::rxIsrFunction(void)  // Función estática para rutina de servicio de interrupción de UART Rx.
	{
		if (Uart::index < SERIAL_BUFF_LEN)   // Si no se ha llenado el buffer Rx serial.
		{
			Uart::_rxBuffer[Uart::index] = UDR;  // Lee el Byte recibido y lo guarda en el buffer.
			Uart::index++;
			uart_bufferFull = false;
		}
		else  // Si el buffer está lleno.
		{
			uint8_t dummy;
			while (UCSRA & (1<<RXC)) dummy = UDR;  // Vacía UDR para poder recibir el próximo mensaje.
			uart_bufferFull = true;
		}
		
		Uart::flagByteReceived = true;
	}
	
	ISR(USART_RXC_vect)
	{		
		Uart::rxIsrFunction();
	}
	
	uint16_t Uart::available(void)
	{
		/*
		 * Indica cuando se han recibido Bytes.
		 * Los Bytes recibidos se encuentran en el buffer Rx.
		 */
		return Uart::index;
	}
	
	bool Uart::getFlagByteReceived(void)
	{
		return Uart::flagByteReceived;
	}
	
	void Uart::clearFlagByteReceived(void)
	{
		Uart::flagByteReceived = false;
	}
	
	void Uart::resetIndexRxBuffer(void)
	{
		cli();
		Uart::index = 0;  // Debe resetearse el index del buffer luego de leerlo.
		uart_bufferFull = false;
		sei();
	}
		
	bool Uart::bufferIsFull(void)
	{
		return uart_bufferFull;
	}

#elif defined(__AVR_ATmega48__)||defined(__AVR_ATmega48P__)||defined(__AVR_ATmega48PA__)||defined(__AVR_ATmega48PB__)  \
||defined(__AVR_ATmega88__)||defined(__AVR_ATmega88P__)||defined(__AVR_ATmega88PA__)||defined(__AVR_ATmega88PB__)	   \
||defined(__AVR_ATmega168__)||defined(__AVR_ATmega168P__)||defined(__AVR_ATmega168PA__)||defined(__AVR_ATmega168PB__)  \
||defined(__AVR_ATmega328__)||defined(__AVR_ATmega328P__)
	
	// Clase UART para ATmega328, ATmega328P...
	// Variables estáticas
	volatile uint8_t Uart::_rxBuffer[SERIAL_BUFF_LEN];
	volatile uint16_t Uart::index;
	volatile bool Uart::flagByteReceived = false;
	volatile bool uart_bufferFull;  // Variable global
		
	void Uart::init(uint16_t ubrr)
	{	
		/*
		 * Inicializa el hardware del puerto UART y devuelve un puntero
		 * al buffer Rx.
		 */
	
		// Set baud rate. Datasheet pag. 222.
		UBRR0H = (uint8_t)(ubrr>>8);
		UBRR0L = (uint8_t)ubrr;

		if (ubrr == 16)
		{
			UCSR0A |= (1<<U2X0);  // baud rate = 57600. Datasheet pag. 219.
		}
		else
		{
			UCSR0A &= ~(1<<U2X0);  // baud rate < 57600.
		}
	
		// Enable Rx interrupts and enable receiver and transmitter. Datasheet pag. 220.
		UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
		// Set frame format: 8data, 1stop bit. Datasheet pag. 221.
		UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
		
		rxBuffer = (uint8_t *)_rxBuffer;
		
		sei();  // Activa las interrupciones globales.
	}
	
	void Uart::txByte(uint8_t n)
	{
		/*
		 * Envia un Byte por el puerto serie.
		 * 
		 * Es una función bloqueante.
		 */
	
		// Wait for empty transmit buffer
		while ( !(UCSR0A & (1<<UDRE0)) ) {};
	
		UDR0 = n;  // Put data into buffer, sends the data
	}
	
	void Uart::rxIsrFunction(void)  // Función estática para rutina de servicio de interrupción de UART Rx.
	{
		if (Uart::index < SERIAL_BUFF_LEN)   // Si no se ha llenado el buffer Rx serial.
		{
			Uart::_rxBuffer[Uart::index] = UDR0;  // Lee el Byte recibido y lo guarda en el buffer.
			Uart::index++;
			uart_bufferFull = false;
		}
		else  // Si el buffer está lleno.
		{
			uint8_t dummy;
			while (UCSR0A & (1<<RXC0)) dummy = UDR0;  // Vacía UDR0 para poder recibir el próximo mensaje.
			uart_bufferFull = true;
		}
		
		Uart::flagByteReceived = true;
	}
	
	ISR(USART_RX_vect)
	{		
		Uart::rxIsrFunction();
	}
	
	uint16_t Uart::available(void)
	{
		/*
		 * Indica cuando se han recibido Bytes.
		 * Los Bytes recibidos se encuentran en el buffer Rx.
		 */
		return Uart::index;
	}
	
	bool Uart::getFlagByteReceived(void)
	{
		return Uart::flagByteReceived;
	}
	
	void Uart::clearFlagByteReceived(void)
	{
		Uart::flagByteReceived = false;
	}

	void Uart::resetIndexRxBuffer(void)
	{
		cli();
		Uart::index = 0;  // Debe resetearse el index del buffer luego de leerlo.
		uart_bufferFull = false;
		sei();
	}
		
	bool Uart::bufferIsFull(void)
	{
		return uart_bufferFull;
	}
	
	uint16_t Uart::receiveBytes(uint8_t byteTimeOut)
	{
		/*
			Función bloqueante para recibir Bytes e implementar un protocolo de comunicación como DNP3 o Modbus.
		*/
			
		if (Uart::flagByteReceived)  // si recibió el primer Byte
		{
			Uart::flagByteReceived = false;
			uint32_t ti = millis();  // reinicia el timer de Byte time out
			while ((millis() - ti) < byteTimeOut)  // y sigue esperando por más Bytes
			{
				if (Uart::flagByteReceived)  // al recibir otro Byte, reinicia inmediatamente el timer de Byte time out
				{
					Uart::flagByteReceived = false;
					uint32_t ti = millis();  // reinicia el timer de Byte time out
				}
			}
				
			uint16_t n = Uart::index;
			resetIndexRxBuffer();
			return n;
		}
		else
		{
			return 0;
		}
	}
	
#endif

#if defined(__AVR_ATmega644__)||defined(__AVR_ATmega644P__)||defined(__AVR_ATmega644PA__)  \
||defined(__AVR_ATmega1284__)||defined(__AVR_ATmega1284P__)||defined(__AVR_ATmega128__)	   \
||defined(__AVR_ATmega128A__)||defined(__AVR_ATmega64__)||defined(__AVR_ATmega64A__)	   \
||defined(__AVR_ATmega1281__)||defined(__AVR_ATmega2561__)||defined(__AVR_ATmega640__)	   \
||defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)||defined(__AVR_ATmega164P__)	   \
||defined(__AVR_ATmega324P__)||defined(__AVR_ATmega324A__)||defined(__AVR_ATmega324PA__)   \
||defined(__AVR_ATmega324PB__)
		
	// Clase Uart0
	#ifdef USE_UART0
		// Variables estáticas
		volatile uint8_t Uart0::_rxBuffer[SERIAL0_BUFF_LEN];
		volatile uint16_t Uart0::index;
		volatile bool Uart0::flagByteReceived = false;
		volatile bool uart0_bufferFull;  // Variable global
				
		void Uart0::init(uint16_t ubrr)
		{	
			/*
				* Inicializa el hardware del puerto UART y devuelve un puntero
				* al buffer Rx.
				*/
	
			// Set baud rate. Datasheet pag. 222.
			UBRR0H = (uint8_t)(ubrr>>8);
			UBRR0L = (uint8_t)ubrr;
			
			if (ubrr == 16)
			{
				UCSR0A |= (1<<U2X0);  // baud rate = 57600. Datasheet pag. 219.
			}
			else
			{
				UCSR0A &= ~(1<<U2X0);  // baud rate < 57600.
			}
	
			// Enable Rx interrupts and enable receiver and transmitter. Datasheet pag. 220.
			UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
			// Set frame format: 8data, 1stop bit. Datasheet pag. 221.
			UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
		
			rxBuffer = (uint8_t *)_rxBuffer;
		
			sei();  // Activa las interrupciones globales.
		}
	
		void Uart0::txByte(uint8_t n)
		{
			/*
				* Envia un Byte por el puerto serie.
				* 
				* Es una función bloqueante.
				*/
	
			// Wait for empty transmit buffer
			while ( !(UCSR0A & (1<<UDRE0)) ) {};
	
			UDR0 = n;  // Put data into buffer, sends the data
		}
	
		void Uart0::rxIsrFunction(void)  // Función estática para rutina de servicio de interrupción de UART Rx.
		{
			if (Uart0::index < SERIAL0_BUFF_LEN)   // Si no se ha llenado el buffer Rx serial.
			{
				Uart0::_rxBuffer[Uart0::index] = UDR0;  // Lee el Byte recibido y lo guarda en el buffer.
				Uart0::index++;
				uart0_bufferFull = false;
			}
			else  // Si el buffer está lleno.
			{
				uint8_t dummy;
				while (UCSR0A & (1<<RXC0)) dummy = UDR0;  // Vacía UDR0 para poder recibir el próximo mensaje.
				uart0_bufferFull = true;
			}
			
			Uart0::flagByteReceived = true;
		}
	
		ISR(USART0_RX_vect)
		{		
			Uart0::rxIsrFunction();
		}
	
		uint16_t Uart0::available(void)
		{
			/*
			 * Indica cuando se han recibido Bytes.
			 * Los Bytes recibidos se encuentran en el buffer Rx.
			 */
			return Uart0::index;
		}

		bool Uart0::getFlagByteReceived(void)
		{
			return Uart0::flagByteReceived;
		}
		
		void Uart0::clearFlagByteReceived(void)
		{
			Uart0::flagByteReceived = false;
		}

		void Uart0::resetIndexRxBuffer(void)
		{
			cli();
			Uart0::index = 0;  // Debe resetearse el index luego de leer el buffer Rx.
			uart0_bufferFull = false;
			sei();
		}
	
		bool Uart0::bufferIsFull(void)
		{
			return uart0_bufferFull;
		}
	
		uint16_t Uart0::receiveBytes(uint8_t byteTimeOut)
		{
			/*
				Función bloqueante para recibir Bytes e implementar un protocolo de comunicación como DNP3 o Modbus.
			*/
			
			if (Uart0::flagByteReceived)  // si recibió el primer Byte
			{
				Uart0::flagByteReceived = false;
				uint32_t ti = millis();  // reinicia el timer de Byte time out
				while ((millis() - ti) < byteTimeOut)  // y sigue esperando por más Bytes
				{
					if (Uart0::flagByteReceived)  // al recibir otro Byte, reinicia inmediatamente el timer de Byte time out
					{
						Uart0::flagByteReceived = false;
						uint32_t ti = millis();  // reinicia el timer de Byte time out
					}
				}
				
				uint16_t n = Uart0::index;
				resetIndexRxBuffer();
				return n;
			}
			else
			{
				return 0;
			}
		}
	#endif
	
	#ifndef __AVR_ATmega644__
		// Clase Uart1
		#ifdef USE_UART1
			// Variables estáticas
			volatile uint8_t Uart1::_rxBuffer[SERIAL1_BUFF_LEN];
			volatile uint16_t Uart1::index;
			volatile bool Uart1::flagByteReceived = false;
			volatile bool uart1_bufferFull;  // Variable global
		
			void Uart1::init(uint16_t ubrr)
			{
				/*
				 * Inicializa el hardware del puerto UART y devuelve un puntero
				 * al buffer Rx.
				 */
	
				// Set baud rate. Datasheet pag. 222.
				UBRR1H = (uint8_t)(ubrr>>8);
				UBRR1L = (uint8_t)ubrr;
				
				if (ubrr == 16)
				{
					UCSR1A |= (1<<U2X1);  // baud rate = 57600. Datasheet pag. 219.
				}
				else
				{
					UCSR1A &= ~(1<<U2X1);  // baud rate < 57600.
				}
				
				// Enable Rx interrupts and enable receiver and transmitter. Datasheet pag. 220.
				UCSR1B = (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
	
				// Set frame format: 8data, 1stop bit. Datasheet pag. 221.
				UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);
			
				rxBuffer = (uint8_t *)_rxBuffer;
	
				sei();  // Activa las interrupciones globales.
			}
	
			void Uart1::txByte(uint8_t n)
			{
				/*
				 * Envia un Byte por el puerto serie.
				 * 
				 * Es una función bloqueante.
				 */
	
				// Wait for empty transmit buffer
				while ( !(UCSR1A & (1<<UDRE1)) ) {};
	
				UDR1 = n;  // Put data into buffer, sends the data
			}
	
			void Uart1::rxIsrFunction(void)  // Función estática para rutina de servicio de interrupción de UART Rx.
			{
				if (Uart1::index < SERIAL1_BUFF_LEN)   // Si no se ha llenado el buffer Rx serial.
				{
					Uart1::_rxBuffer[Uart1::index] = UDR1;  // Lee el Byte recibido y lo guarda en el buffer.
					Uart1::index++;
					uart1_bufferFull = false;
				}
				else  // Si el buffer está lleno.
				{
					uint8_t dummy;
					while (UCSR1A & (1<<RXC1)) dummy = UDR1;  // Vacía UDR1 para poder recibir el próximo mensaje.
					uart1_bufferFull = true;
				}
				
				Uart1::flagByteReceived = true;
			}
		
			ISR(USART1_RX_vect)
			{		
				Uart1::rxIsrFunction();
			}
		
			uint16_t Uart1::available(void)
			{
				/*
				 * Indica cuando se han recibido Bytes.
				 * Los Bytes recibidos se encuentran en el buffer Rx.
				 */
				return Uart1::index;
			}
			
			bool Uart1::getFlagByteReceived(void)
			{
				return Uart1::flagByteReceived;
			}
		
			void Uart1::clearFlagByteReceived(void)
			{
				Uart1::flagByteReceived = false;
			}
		
			void Uart1::resetIndexRxBuffer(void)
			{
				cli();
				Uart1::index = 0;  // Debe resetearse el index del buffer luego de leerlo.
				uart1_bufferFull = false;
				sei();
			}
		
			bool Uart1::bufferIsFull(void)
			{
				return uart1_bufferFull;
			}
			
			uint16_t Uart1::receiveBytes(uint8_t byteTimeOut)
			{
				/*
					Función bloqueante para recibir Bytes e implementar un protocolo de comunicación como DNP3 o Modbus.
				*/
			
				if (Uart1::flagByteReceived)  // si recibió el primer Byte
				{
					Uart1::flagByteReceived = false;
					uint32_t ti = millis();  // reinicia el timer de Byte time out
					while ((millis() - ti) < byteTimeOut)  // y sigue esperando por más Bytes
					{
						if (Uart1::flagByteReceived)  // al recibir otro Byte, reinicia inmediatamente el timer de Byte time out
						{
							Uart1::flagByteReceived = false;
							uint32_t ti = millis();  // reinicia el timer de Byte time out
						}
					}
				
					uint16_t n = Uart1::index;
					resetIndexRxBuffer();
					return n;
				}
				else
				{
					return 0;
				}
			}
		#endif
	#endif  // __AVR_ATmega644__
	
#endif  // defined(__AVR_ATmega644__)||defined(__AVR_ATmega644P__)||defined(__AVR_ATmega644PA__)  \...

#if defined(__AVR_ATmega640__)||defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)||defined(__AVR_ATmega324PB__)
	
	// Clase Uart2
	#ifdef USE_UART2
		// Variables estáticas
		volatile uint8_t Uart2::_rxBuffer[SERIAL2_BUFF_LEN];
		volatile uint16_t Uart2::index;
		volatile bool Uart2::flagByteReceived = false;
		volatile bool uart2_bufferFull;  // Variable global
		
		void Uart2::init(uint16_t ubrr)
		{
			/*
				* Inicializa el hardware del puerto UART y devuelve un puntero
				* al buffer Rx.
				*/
			
			// Set baud rate. Datasheet pag. 222.
			UBRR2H = (uint8_t)(ubrr>>8);
			UBRR2L = (uint8_t)ubrr;
			
			if (ubrr == 16)
			{
				UCSR2A |= (1<<U2X2);  // baud rate = 57600. Datasheet pag. 219.
			}
			else
			{
				UCSR2A &= ~(1<<U2X2);  // baud rate < 57600.
			}
			
			// Enable Rx interrupts and enable receiver and transmitter. Datasheet pag. 220.
			UCSR2B = (1<<RXCIE2)|(1<<RXEN2)|(1<<TXEN2);
	
			// Set frame format: 8data, 1stop bit. Datasheet pag. 221.
			UCSR2C = (1<<UCSZ21)|(1<<UCSZ20);
		
			rxBuffer = (uint8_t *)_rxBuffer;
			
			sei();  // Activa las interrupciones globales.
		}
	
		void Uart2::txByte(uint8_t n)
		{
			/*
				* Envia un Byte por el puerto serie.
				* 
				* Es una función bloqueante.
				*/
	
			// Wait for empty transmit buffer
			while ( !(UCSR2A & (1<<UDRE2)) ) {};
	
			UDR2 = n;  // Put data into buffer, sends the data
		}
	
		void Uart2::rxIsrFunction(void)  // Función estática para rutina de servicio de interrupción de UART Rx.
		{
			if (Uart2::index < SERIAL2_BUFF_LEN)   // Si no se ha llenado el buffer Rx serial.
			{
				Uart2::_rxBuffer[Uart2::index] = UDR2;  // Lee el Byte recibido y lo guarda en el buffer.
				Uart2::index++;
				uart2_bufferFull = false;
			}
			else  // Si el buffer está lleno.
			{
				uint8_t dummy;
				while (UCSR2A & (1<<RXC2)) dummy = UDR2;  // Vacía UDR2 para poder recibir el próximo mensaje.
				uart2_bufferFull = true;
			}
						
			Uart2::flagByteReceived = true;
		}
		
		ISR(USART2_RX_vect)
		{		
			Uart2::rxIsrFunction();
		}
		
		uint16_t Uart2::available(void)
		{
			/*
				* Indica cuando se han recibido Bytes.
				* Los Bytes recibidos se encuentran en el buffer Rx.
				*/
			return Uart2::index;
		}
		
		bool Uart2::getFlagByteReceived(void)
		{
			return Uart2::flagByteReceived;
		}
		
		void Uart2::clearFlagByteReceived(void)
		{
			Uart2::flagByteReceived = false;
		}
		
		void Uart2::resetIndexRxBuffer(void)
		{
			cli();
			Uart2::index = 0;  // Debe resetearse el index del buffer luego de leerlo.
			uart2_bufferFull = false;
			sei();
		}
	
		bool Uart2::bufferIsFull(void)
		{
			return uart2_bufferFull;
		}
		
		uint16_t Uart2::receiveBytes(uint8_t byteTimeOut)
		{
			/*
				Función bloqueante para recibir Bytes e implementar un protocolo de comunicación como DNP3 o Modbus.
			*/
			
			if (Uart2::flagByteReceived)  // si recibió el primer Byte
			{
				Uart2::flagByteReceived = false;
				uint32_t ti = millis();  // reinicia el timer de Byte time out
				while ((millis() - ti) < byteTimeOut)  // y sigue esperando por más Bytes
				{
					if (Uart2::flagByteReceived)  // al recibir otro Byte, reinicia inmediatamente el timer de Byte time out
					{
						Uart2::flagByteReceived = false;
						uint32_t ti = millis();  // reinicia el timer de Byte time out
					}
				}
				
				uint16_t n = Uart2::index;
				resetIndexRxBuffer();
				return n;
			}
			else
			{
				return 0;
			}
		}
	#endif
	
	#ifndef __AVR_ATmega324PB__
		// Clase Uart3
		#ifdef USE_UART3
			// Variables estáticas
			volatile uint8_t Uart3::_rxBuffer[SERIAL3_BUFF_LEN];
			volatile uint16_t Uart3::index;
			volatile bool Uart3::flagByteReceived = false;
			volatile bool uart3_bufferFull;  // Variable global
		
			void Uart3::init(uint16_t ubrr)
			{
				/*
				 * Inicializa el hardware del puerto UART y devuelve un puntero
				 * al buffer Rx.
				 */
	
				// Set baud rate. Datasheet pag. 222.
				UBRR3H = (uint8_t)(ubrr>>8);
				UBRR3L = (uint8_t)ubrr;

				if (ubrr == 16)
				{
					UCSR3A |= (1<<U2X3);  // baud rate = 57600. Datasheet pag. 219.
				}
				else
				{
					UCSR3A &= ~(1<<U2X3);  // baud rate < 57600.
				}
	
				// Enable Rx interrupts and enable receiver and transmitter. Datasheet pag. 220.
				UCSR3B = (1<<RXCIE3)|(1<<RXEN3)|(1<<TXEN3);
	
				// Set frame format: 8data, 1stop bit. Datasheet pag. 221.
				UCSR3C = (1<<UCSZ31)|(1<<UCSZ30);
			
				rxBuffer = (uint8_t *)_rxBuffer;
			
				sei();  // Activa las interrupciones globales.
			}
	
			void Uart3::txByte(uint8_t n)
			{
				/*
				 * Envia un Byte por el puerto serie.
				 * 
				 * Es una función bloqueante.
				 */
	
				// Wait for empty transmit buffer
				while ( !(UCSR3A & (1<<UDRE3)) ) {};
	
				UDR3 = n;  // Put data into buffer, sends the data
			}
	
			void Uart3::rxIsrFunction(void)  // Función estática para rutina de servicio de interrupción de UART Rx.
			{
				if (Uart3::index < SERIAL3_BUFF_LEN)   // Si no se ha llenado el buffer Rx serial.
				{
					Uart3::_rxBuffer[Uart3::index] = UDR3;  // Lee el Byte recibido y lo guarda en el buffer.
					Uart3::index++;
					uart3_bufferFull = false;
				}
				else  // Si el buffer está lleno.
				{
					uint8_t dummy;
					while (UCSR3A & (1<<RXC3)) dummy = UDR3;  // Vacía UDR3 para poder recibir el próximo mensaje.
					uart3_bufferFull = true;
				}
				
				Uart3::flagByteReceived = true;
			}
		
			ISR(USART3_RX_vect)
			{		
				Uart3::rxIsrFunction();
			}
		
			uint16_t Uart3::available(void)
			{
				/*
					* Indica cuando se han recibido Bytes.
					* Los Bytes recibidos se encuentran en el buffer Rx.
					*/
				return Uart3::index;
			}
			
			bool Uart3::getFlagByteReceived(void)
			{
				return Uart3::flagByteReceived;
			}
		
			void Uart3::clearFlagByteReceived(void)
			{
				Uart3::flagByteReceived = false;
			}
		
			void Uart3::resetIndexRxBuffer(void)
			{
				cli();
				Uart3::index = 0;  // Debe resetearse el index del buffer luego de leerlo.
				uart3_bufferFull = false;
				sei();
			}
		
			bool Uart3::bufferIsFull(void)
			{
				return uart3_bufferFull;
			}
			
			uint16_t Uart3::receiveBytes(uint8_t byteTimeOut)
			{
				/*
					Función bloqueante para recibir Bytes e implementar un protocolo de comunicación como DNP3 o Modbus.
				*/
			
				if (Uart3::flagByteReceived)  // si recibió el primer Byte
				{
					Uart3::flagByteReceived = false;
					uint32_t ti = millis();  // reinicia el timer de Byte time out
					while ((millis() - ti) < byteTimeOut)  // y sigue esperando por más Bytes
					{
						if (Uart3::flagByteReceived)  // al recibir otro Byte, reinicia inmediatamente el timer de Byte time out
						{
							Uart3::flagByteReceived = false;
							uint32_t ti = millis();  // reinicia el timer de Byte time out
						}
					}
				
					uint16_t n = Uart3::index;
					resetIndexRxBuffer();
					return n;
				}
				else
				{
					return 0;
				}
			}
		#endif		
	#endif
	
#endif  // defined(__AVR_ATmega640__)||defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)||defined(__AVR_ATmega324PB__)