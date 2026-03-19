/*
 * Actividad4-3_UART_EEPROM.c
 *
 * Created: 18/3/2026 12:48:45
 * Author : jhare
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "Librerias/EEPROM.h"
#include "Librerias/UART.h"

bool RxFlag = false;
uint8_t dato = 0;
volatile char rxBuffer[10];
volatile uint8_t i = 0;

void actualiceLeds();

int main(void)
{
	UART_init(103,8,DISABLED,MONOBIT,ENABLED,ENABLED);
	DDRD |= 0b11111100; // D7 a D2 output
	DDRB |= 0b00000011; // B1 y B0 output
	sei();
	
	dato = EEPROM_read(0);
	actualiceLeds();
	
	UART_string("Send a number that in binary forms what you want \n\r");
	UART_string("For example 3 will turn on the last two leds \n\r");
	
	
    while (1) 
    {
		if(RxFlag)
		{
			cli();
			dato = atoi((char*)rxBuffer);
			EEPROM_update(0,dato);
			RxFlag = false;
			sei();
			actualiceLeds();
			
		}
    }
}

ISR(USART_RX_vect)
{
	char c = UDR0;

	if(c == '\n' || c == '\r')
	{
		rxBuffer[i] = '\0';
		i = 0;
		RxFlag = true;
	}
	else if(i < sizeof(rxBuffer)-1)
	{
		rxBuffer[i++] = c;
	} else {
		i = 0;
	}
}


void actualiceLeds()
{
	int bit;

	// LED0
	bit = (dato>>0) & 1;
	if(bit){
		PORTB |= (1<<1);
		UART_string("LED0 ON, ");
		}else{
		PORTB &= ~(1<<1);
		UART_string("LED0 OFF, ");
	}

	// LED1
	bit = (dato>>1) & 1;
	if(bit){
		PORTB |= (1<<0);
		UART_string("LED1 ON, ");
		}else{
		PORTB &= ~(1<<0);
		UART_string("LED1 OFF, ");
	}

	// LED2
	bit = (dato>>2) & 1;
	if(bit){
		PORTD |= (1<<7);
		UART_string("LED2 ON, ");
		}else{
		PORTD &= ~(1<<7);
		UART_string("LED2 OFF, ");
	}

	// LED3
	bit = (dato>>3) & 1;
	if(bit){
		PORTD |= (1<<6);
		UART_string("LED3 ON, ");
		}else{
		PORTD &= ~(1<<6);
		UART_string("LED3 OFF, ");
	}

	// LED4
	bit = (dato>>4) & 1;
	if(bit){
		PORTD |= (1<<5);
		UART_string("LED4 ON, ");
		}else{
		PORTD &= ~(1<<5);
		UART_string("LED4 OFF, ");
	}

	// LED5
	bit = (dato>>5) & 1;
	if(bit){
		PORTD |= (1<<4);
		UART_string("LED5 ON, ");
		}else{
		PORTD &= ~(1<<4);
		UART_string("LED5 OFF, ");
	}

	// LED6
	bit = (dato>>6) & 1;
	if(bit){
		PORTD |= (1<<3);
		UART_string("LED6 ON, ");
		}else{
		PORTD &= ~(1<<3);
		UART_string("LED6 OFF, ");
	}

	// LED7
	bit = (dato>>7) & 1;
	if(bit){
		PORTD |= (1<<2);
		UART_string("LED7 ON \n\r");
		}else{
		PORTD &= ~(1<<2);
		UART_string("LED7 OFF \n\r");
	}
}
