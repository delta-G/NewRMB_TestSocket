/*

 MCP3008.h and MCP3008.cpp   --  Control code for MCP3008 10-bit ADC
 Copyright (C) 2020  David C.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#include "MCP3008.h"

void MCP3008::init(){
	pinMode(CS_pin, OUTPUT);
	digitalWrite(CS_pin, HIGH);
}

uint16_t MCP3008::read(uint8_t aPin){
	digitalWrite(CS_pin, LOW);
	SPDR = 1;  // start bit with 7 leading 0's
	while(!(SPSR & (1 << SPIF)));
	SPDR = ((1 << 7) | (aPin << 4));
	while(!(SPSR & (1 << SPIF)));
	uint16_t retval = (SPDR & 3);  // only two LSB are relevant
	SPDR = 0;
	while(!(SPSR & (1 << SPIF)));
	retval = (retval << 8) + SPDR;
	digitalWrite(CS_pin, HIGH);
	return retval;
}




