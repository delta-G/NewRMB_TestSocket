/*

 MCP23S09.h and MCP23S09.cpp   --  Control code for MCP23S09 pin expander
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

/*
*             MCP23S09 expander xp0
 *
 *                                   +---\/---+
 *                             VDD  1|        |18 VSS
 *                              NC  2|        |17 NC
 *                              CS  3|        |16 GP7
 *                             SCK  4|        |15 GP6
 *                            MOSI  5|        |14 GP5
 *                            MISO  6|        |13 GP4
 *                           RESET  7|        |12 GP3
 *                       INTERRUPT  8|        |11 GP2
 *                             GP0  9|        |10 GP1
 *                                   +--------+
 *
 */


#ifndef MCP23S09_H_
#define MCP23S09_H_

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
#define ODR 2       // Open Drain for INT pin  0-Active driver (INTPOL sets polarity) 1-Open Drain (Overrides INTPOL)
#define INTPOL 1    // Polarity of INT pin 0-Active LOW  1-Active HIGH
#define INTCC 0     // Interrupt Clearing Control  0-Read GPIO to clear interrupt  1-Read INTCAP to clear interrupt
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


class MCP23S09 {

private:
	uint8_t CSpin;

public:
	MCP23S09(uint8_t aCSpin):CSpin(aCSpin){};

	void init();

	void writeRegister(uint8_t aReg, uint8_t aVal);
	uint8_t readRegister(uint8_t aReg);
	void writeIO(uint8_t aVal);
	uint8_t readIO();
	void writePin(uint8_t aPin, uint8_t aVal);
	uint8_t readPin(uint8_t aPin);
	void setPinMode(uint8_t aPin, uint8_t aMode);
	void setPullup(uint8_t aPin, boolean aSetting);


};




#endif /* MCP23S09_H_ */
