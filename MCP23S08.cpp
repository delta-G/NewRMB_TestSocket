/*

 MCP23S08.h and MCP23S08.cpp   --  Control code for MCP23S08 pin expander
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

#include "MCP23S08.h"

void MCP23S08::init() {
	pinMode(CSpin, OUTPUT);
	digitalWrite(CSpin, HIGH);
//	static boolean SPI_setup = false;
//	if (!SPI_setup) {
	pinMode(SCK, OUTPUT); // @suppress("Invalid arguments")
	pinMode(MISO, INPUT); // @suppress("Invalid arguments")
	pinMode(MOSI, OUTPUT); // @suppress("Invalid arguments")

	SPCR = (1 << SPE) | (1 << MSTR);
	SPSR = 0;
//		SPSR = (1 << SPI2X);
//		SPI_setup = true;
//	}
	if (hardwareAddress != 255) {
//		uint8_t oldReg = readRegister(IOCON);
		writeRegister(IOCON, (/*oldReg |*/ (1 << HAEN)));  // For some reason this doesn't work.  Have to set in sketch after they're all up
	}
}

void MCP23S08::writeRegister(uint8_t aReg, uint8_t aVal) {
	digitalWrite(CSpin, LOW);
	SPDR = getControlByte(true);
	while(!(SPSR & (1 << SPIF)));
	SPDR = aReg;
	while(!(SPSR & (1 << SPIF)));
	SPDR = aVal;
	while(!(SPSR & (1 << SPIF)));
	digitalWrite(CSpin, HIGH);
}

uint8_t MCP23S08::readRegister(uint8_t aReg) {
	digitalWrite(CSpin, LOW);
	SPDR = getControlByte(false);
	while(!(SPSR & (1 << SPIF)));
	SPDR = aReg;
	while(!(SPSR & (1 << SPIF)));
	SPDR = 0x00;
	while(!(SPSR & (1 << SPIF)));
	uint8_t retval = SPDR;
	digitalWrite(CSpin, HIGH);
	return retval;
}

void MCP23S08::writeIO(uint8_t aVal) {
	writeRegister(OLATA, aVal);
}
uint8_t MCP23S08::readIO() {
	return readRegister(GPIOA);
}
void MCP23S08::writePin(uint8_t aPin, uint8_t aState) {
	uint8_t val = readRegister(OLATA);
	if(aState){
		val |= (1<<aPin);
	} else {
		val &= ~(1<<aPin);
	}
	writeRegister(OLATA, (val));
}
uint8_t MCP23S08::readPin(uint8_t aPin) {
	uint8_t val = readRegister(GPIOA);
	return !!(val &(1<<aPin));
}

void MCP23S08::setPinMode(uint8_t aPin, uint8_t aMode){
	uint8_t val = readRegister(IODIRA);
	if(aMode == OUTPUT){
		writeRegister(IODIRA, (val & ~(1<<aPin)));
	} else {
		writeRegister(IODIRA, (val | (1<<aPin)));
	}
	// set pull-up resistor if requested
	if(aMode == INPUT_PULLUP){
		setPullup(aPin, true);
	} else {
		setPullup(aPin,  false);
	}
}

void MCP23S08::setPullup(uint8_t aPin, boolean aSetting){
	uint8_t val = readRegister(GPPUA);
	if(aSetting){
		writeRegister(GPPUA, (val | (1<<aPin)));
	} else {
		writeRegister(GPPUA, (val & ~(1<<aPin)));
	}
}



void MCP23S08::setHardwareAddress(uint8_t aHwadd){
	hardwareAddress = aHwadd;
};

uint8_t MCP23S08::getHardwareAddress(){
	uint8_t retval = hardwareAddress;
	return retval;
};

uint8_t MCP23S08::getControlByte(boolean aWriteMode){
	uint8_t retval = 0x40;
	if (hardwareAddress != 255) {
		retval |= (hardwareAddress << 1);
	}
	if(!aWriteMode){
		retval |= 1;
	}
	return retval;
};
