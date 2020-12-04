/*

 NewRMB_TestSocket.h and NewRMB_TestSocket.cpp  --  test code for new version of RobotMainBrain hardware
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

#ifndef _NewRMB_TestSocket_H_
#define _NewRMB_TestSocket_H_
#include "Arduino.h"
#include <StreamParser.h>
#include "Motor.h"
#include "Encoder.h"

#include "MCP23S09.h"

void setup();
void loop();
void heartbeat();

void leftTick(boolean);
void rightTick(boolean);

void handleSerial(char*);

void printMcpRegisters();

#endif /* _NewRMB_TestSocket_H_ */
