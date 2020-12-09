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

#ifndef MCP3008_H_
#define MCP3008_H_

#include "Arduino.h"

class MCP3008 {

private:
	uint8_t CS_pin;

public:
	MCP3008(uint8_t aCSpin):CS_pin(aCSpin){};

	void init();
	uint16_t read(uint8_t aPin);

};


#endif /* MCP3008_H_ */
