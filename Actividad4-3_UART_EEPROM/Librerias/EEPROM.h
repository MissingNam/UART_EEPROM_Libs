/*
 * IncFile1.h
 *
 * Created: 18/3/2026 12:41:27
 *  Author: jhare
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>

unsigned char EEPROM_read(unsigned int);
void EEPROM_write(unsigned int, unsigned char);

unsigned char EEPROM_read(unsigned int uiAdress)
{
	while(EECR & (1<<EEPE));
	
	EEAR = uiAdress;
	EECR |= (1<<EERE);
	return EEDR;
}

void EEPROM_write(unsigned int uiAddress, unsigned char data)
{
	while(EECR & (1<<EEPE));
	
	EEAR = uiAddress;
	EEDR = data;
	EECR |= (1<<EEMPE);
	EECR |= (1<<EEPE);
}

void EEPROM_update(unsigned int uiAddress, unsigned char data)
{
	while(EECR & (1<<EEPE));
	char last = EEPROM_read(uiAddress);
	if(data != last)
	{
		EEPROM_write(uiAddress,data);
	}
}

#endif /* EEPROM_H_ */