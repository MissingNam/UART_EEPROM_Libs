/*
 * UART.h
 *
 * Created: 18/3/2026 12:09:20
 *  Author: jhare
 */ 


#ifndef UART_H_
#define UART_H_

#define DISABLED 0
#define ENABLED 1
#define ENABLE_EVEN 1
#define ENABLE_ODD 2

#define MONOBIT 0
#define PAIRBIT 1

void UART_init();
unsigned char UART_read();
void UART_write(unsigned char);
void UART_string(char*);


void UART_init(int baudRate, int dataSize, int parityMode, int stopBits, int TXint, int RXint)
{
	UCSR0A |= (0<<U2X0); // velocidad doble OFF
	UCSR0A |= (0<<MPCM0); // multicore off
	UCSR0B |= (1<<TXEN0); // Tx Enable
	UCSR0B |= (1<<RXEN0); // Rx Enable
	UCSR0B |= (1<<UDRIE0); // Data register empty
	UCSR0B |= (TXint<<TXCIE0); // TX complete int 
	UCSR0B |= (RXint<<RXCIE0); // Rx complete int
	UCSR0C |= (0<<UMSEL01) | (0<<UMSEL00); // asincrono
	UCSR0C |= (PAIRBIT<<USBS0); // stop bit 1 bit = 0
	UCSR0C |= (0<<UCPOL0); // asincrono
	UBRR0 = baudRate; // 103 usual
	
	// configuracion de tamaño de byte
	switch(dataSize)
	{
		case 5:
			UCSR0C |= (0<<UCSZ01) | (0<<UCSZ00); // 5bits
			break;
		case 6:
			UCSR0C |= (0<<UCSZ01) | (1<<UCSZ00); // 6bits
			break;
		case 7:
			UCSR0C |= (1<<UCSZ01) | (0<<UCSZ00); // 7bits
			break;
		case 8:
			UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); // 8bits
			break;
		case 9:
			UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00); // 9bits
			UCSR0B |= (1<<UCSZ02);
			break;
		default:
			break;	
	}
	
	switch(parityMode)
	{
		case DISABLED:
			UCSR0C |= (0<<UPM01) | (0<<UPM00); // no paridad
			break;
		case ENABLE_EVEN:
			UCSR0C |= (1<<UPM01) | (0<<UPM00); // paridad par
			break;
		case ENABLE_ODD:
			UCSR0C |= (1<<UPM01) | (1<<UPM00); // no imparidad
			break;
		default:
			UCSR0C |= (0<<UPM01) | (0<<UPM00); // no paridad
		break;
	}
	
	
	
}

unsigned char UART_read()
{
	if(UCSR0A&(1<<RXC0))
	{
		return UDR0;
	}
	return 0;
}

void UART_write(unsigned char data)
{
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0 = data;
}

void UART_string(char* string)
{
	while(*string != 0)
	{
		UART_write(*string);
		string++;
	}
}

unsigned char UART_readChar()
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
	
}

void UART_readString(char *buffer, uint8_t maxLenght)
{
	uint8_t i = 0;
	char c = 0;
	while(i < maxLenght-1)
	{
		c = UART_readChar();
		if(c == '\n' || c == '\r')
		break;
		
		buffer[i++] = c;
	}
	buffer[i] = '\0';
}




#endif /* UART_H_ */