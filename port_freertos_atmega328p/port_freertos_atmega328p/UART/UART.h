#ifndef __UART_h__
#define __UART_h__

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "Millis.h"

// Opciones
// ------------------------
// Tamaño del buffer Rx de cada puerto.
#define SERIAL_BUFF_LEN  40      // micros con un puerto UART.
#define SERIAL0_BUFF_LEN 337     // micros con más de un puerto UART.
#define SERIAL1_BUFF_LEN 337
#define SERIAL2_BUFF_LEN 337
#define SERIAL3_BUFF_LEN 337

// Micros con más de un puerto UART: Compilar soporte para puerto.
#define USE_UART0
#define USE_UART1
#define USE_UART2
#define USE_UART3
// ------------------------

#ifndef DEC
#define DEC 10
#endif

#ifndef HEX
#define HEX 16
#endif

#ifndef BIN
#define BIN 2
#endif

#define BAUD_CALC(x) F_CPU/16/x-1		 // para baud rate < 57600
#define DOUBLE_BAUD_CALC(x) F_CPU/8/x-1  // para baud rate = 57600

// Clase abstracta con métodos virtuales puros, todas las demás clases derivan de esta clase.
class UartBase
{
	public:
		uint8_t *rxBuffer;
		
		char * lltoa(int64_t val, char *cstring, int radix);
		// ---------
		void txBytes(uint8_t *arrayBytes, uint16_t len);
		// ---------
		void txUint16(uint16_t n, uint8_t base = DEC);
		void txInt16(int16_t n, uint8_t base = DEC);
		// ---------
		void print(char l);
		void print(char *cstring);
		void print(bool bit);
		void print(uint8_t n, uint8_t base = DEC);
		void print(uint16_t n, uint8_t base = DEC);
		void print(int8_t n, uint8_t base = DEC);
		void print(int16_t n, uint8_t base = DEC);
		void print(uint32_t n, uint8_t base = DEC);
		void print(int32_t n, uint8_t base = DEC);
		void print(int64_t n, uint8_t base = DEC);
		void print(float n, uint8_t prec = 2);
		// ---------
		void println(char l);
		void println(char *cstring);
		void println(bool bit);
		void println(uint8_t n, uint8_t base = DEC);
		void println(uint16_t n, uint8_t base = DEC);
		void println(int8_t n, uint8_t base = DEC);
		void println(int16_t n, uint8_t base = DEC);
		void println(uint32_t n, uint8_t base = DEC);
		void println(int32_t n, uint8_t base = DEC);
		void println(int64_t n, uint8_t base = DEC);
		void println(float n, uint8_t prec = 2);
		// ---------
		void print_P(const char *cstring);
		void println_P(const char *cstring);
		// ---------
		void printnewline(uint8_t numLn = 1);
		void printspace(uint8_t numSpace = 1);
		
		// Métodos virtuales puros -> las clases derivadas deben implementarlos si o si.
		virtual void init(uint16_t ubrr) = 0;
		virtual void txByte(uint8_t n) = 0;
		virtual uint16_t available(void) = 0;
		virtual bool getFlagByteReceived(void) = 0;
		virtual void clearFlagByteReceived(void) = 0;
		virtual void resetIndexRxBuffer(void) = 0;
		virtual bool bufferIsFull(void) = 0;
		virtual uint16_t receiveBytes(uint8_t byteTimeOut) = 0;
};

// Micros con un solo puerto UART
#if defined(__AVR_ATmega8__)||defined(__AVR_ATmega8P__)||defined(__AVR_ATmega16__)\
||defined(__AVR_ATmega16A__)||defined(__AVR_ATmega32__)||defined(__AVR_ATmega32A__)\
||defined(__AVR_ATmega8A__)||defined(__AVR_ATmega8L__)\
||defined(__AVR_ATmega48__)||defined(__AVR_ATmega48P__)||defined(__AVR_ATmega48PA__)||defined(__AVR_ATmega48PB__)\
||defined(__AVR_ATmega88__)||defined(__AVR_ATmega88P__)||defined(__AVR_ATmega88PA__)||defined(__AVR_ATmega88PB__)\
||defined(__AVR_ATmega168__)||defined(__AVR_ATmega168P__)||defined(__AVR_ATmega168PA__)||defined(__AVR_ATmega168PB__)\
||defined(__AVR_ATmega328__)||defined(__AVR_ATmega328P__)
	
	class Uart : public UartBase
	{
		private:
			static volatile uint8_t _rxBuffer[SERIAL_BUFF_LEN];
			static volatile uint16_t index;
			static volatile bool flagByteReceived;
		
		public:
			void init(uint16_t ubrr);
			void txByte(uint8_t n);
			static void rxIsrFunction(void);  // Esta función se ejecuta desde la rutina de interrupción por Rx.
			uint16_t available(void);
			bool getFlagByteReceived(void);
			void clearFlagByteReceived(void);
			void resetIndexRxBuffer(void);
			bool bufferIsFull(void);
			uint16_t receiveBytes(uint8_t byteTimeOut);
	};
	
#else  // Micros con más de un puerto UART
		
	#ifdef USE_UART0
	class Uart0 : public UartBase
	{	
		private:
			static volatile uint8_t _rxBuffer[SERIAL0_BUFF_LEN];
			static volatile uint16_t index;
			static volatile bool flagByteReceived;
					
		public:	
			void init(uint16_t ubrr);
			void txByte(uint8_t n);
			static void rxIsrFunction(void);  // Esta función se ejecuta desde la rutina de interrupción por Rx.
			uint16_t available(void);
			bool getFlagByteReceived(void);
			void clearFlagByteReceived(void);
			void resetIndexRxBuffer(void);
			bool bufferIsFull(void);
			uint16_t receiveBytes(uint8_t byteTimeOut);
	};
	#endif
	
	#ifdef USE_UART1
	class Uart1 : public UartBase
	{
		private:
			static volatile uint8_t _rxBuffer[SERIAL1_BUFF_LEN];
			static volatile uint16_t index;
			static volatile bool flagByteReceived;
		
		public:
			void init(uint16_t ubrr);
			void txByte(uint8_t n);
			static void rxIsrFunction(void);  // Esta función se ejecuta desde la rutina de interrupción por Rx.
			uint16_t available(void);
			bool getFlagByteReceived(void);
			void clearFlagByteReceived(void);
			void resetIndexRxBuffer(void);
			bool bufferIsFull(void);
			uint16_t receiveBytes(uint8_t byteTimeOut);
	};
	#endif
	
	#ifdef USE_UART2
	class Uart2 : public UartBase
	{
		private:
			static volatile uint8_t _rxBuffer[SERIAL2_BUFF_LEN];
			static volatile uint16_t index;
			static volatile bool flagByteReceived;
		
		public:
			void init(uint16_t ubrr);
			void txByte(uint8_t n);
			static void rxIsrFunction(void);  // Esta función se ejecuta desde la rutina de interrupción por Rx.
			uint16_t available(void);
			bool getFlagByteReceived(void);
			void clearFlagByteReceived(void);
			void resetIndexRxBuffer(void);
			bool bufferIsFull(void);
			uint16_t receiveBytes(uint8_t byteTimeOut);
	};
	#endif
	
	#ifdef USE_UART3
	class Uart3 : public UartBase
	{
		private:
			static volatile uint8_t _rxBuffer[SERIAL3_BUFF_LEN];
			static volatile uint16_t index;
			static volatile bool flagByteReceived;
		
		public:
			void init(uint16_t ubrr);
			void txByte(uint8_t n);
			static void rxIsrFunction(void);  // Esta función se ejecuta desde la rutina de interrupción por Rx.
			uint16_t available(void);
			bool getFlagByteReceived(void);
			void clearFlagByteReceived(void);
			void resetIndexRxBuffer(void);
			bool bufferIsFull(void);
			uint16_t receiveBytes(uint8_t byteTimeOut);
	};
	#endif
		
#endif

#endif
