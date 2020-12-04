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

#ifndef MCP23S08_H_
#define MCP23S08_H_

#include "Arduino.h"
//#include <SPI.h>

/*****************************
 *
 * Registers
 *
 ******************************/

#define IODIRA 0x00  // IO Direction register IO7 - IO0  1-INPUT 0-OUTPUT
#define IPOLA  0x01  // IO Polarity  0-pin same as logic  1-pin reverse of logic
#define GPINTENA 0x02  // Pin change interrupt enable 0-disable 1-enable
#define DEFVALA 0x03  // Default value sets value to compare against for interrupt if enabled
#define INTCONA 0x04  //Interrupt control  0-pin compared to previous value  1-pin compared to DEFVALA

/*****************************************/
/****  IO CONTROL REGISTER WITH BITS  ****/
#define IOCON 0x05  // IO Control Register // See bit descriptions
#define SEQOP 5     // Sequential operation 0-address pointer increments  1-address pointer does not increment
#define DISSLW 4    // Slew for SDA pin on I2C models  // unused on SPI models
#define HAEN 3  	// Hardware Address enable (SPI models only always 1 on I2C chips) 1-Enables hardware adress pins  0-Disables
#define ODR 2       // Open Drain for INT pin  0-Active driver (INTPOL sets polarity) 1-Open Drain (Overrides INTPOL)
#define INTPOL 1    // Polarity of INT pin 0-Active LOW  1-Active HIGH
/***************************************/
/***************************************/

#define GPPUA 0x06  // Sets pull-up resistors  0-disabled  1-enabled
#define INTFA 0x07  // Interrupt Flag Register  0-Interrupt not pending  1-Pin caused interrupt
#define INTCAPA 0x08  // Interrupt Capture - Captured GPIO at time of last interrupt
#define GPIOA 0x09   // GPIO Port register  0-Logic LOW  1-Logic HIGH (Write to this writes to OLAT)
#define OLATA 0x0A  // Output Latches  -  Write to this register to write an output



/*****************************
 *
 * To write a register send first pull CS LOW then
 * Send address byte 0x40 for write or 0x41 for read
 * Then the register address and then the data
 *
 ****************************/


class MCP23S08 {

private:
	uint8_t CSpin;
	uint8_t hardwareAddress;

public:
	MCP23S08(uint8_t aCSpin):CSpin(aCSpin), hardwareAddress(255){};
	MCP23S08(uint8_t aCSpin, uint8_t aHWadd):CSpin(aCSpin), hardwareAddress(aHWadd){};

	void init();
	void setHardwareAddress(uint8_t);
	uint8_t getHardwareAddress();

	uint8_t getControlByte(boolean writeMode);

	void writeRegister(uint8_t aReg, uint8_t aVal);
	uint8_t readRegister(uint8_t aReg);
	void writeIO(uint8_t aVal);
	uint8_t readIO();
	void writePin(uint8_t aPin, uint8_t aVal);
	uint8_t readPin(uint8_t aPin);
	void setPinMode(uint8_t aPin, uint8_t aMode);
	void setPullup(uint8_t aPin, boolean aSetting);


};




#endif /* MCP23S08_H_ */
