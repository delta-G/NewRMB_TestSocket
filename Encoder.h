/*

Encoder.h  --  runs on 1284P and handles motor encoders of my robot
     Copyright (C) 2017  David C.

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

#ifndef ENCODER_H_
#define ENCODER_H_

#include "Arduino.h"

#include "Defines.h"


void setupPCint();


int32_t getLeftMotorCount();
int32_t getRightMotorCount();

void setTickCallback(void(*aLeftCallback)(boolean), void(*aRightCallback)(boolean));


#endif /* ENCODER_H_ */
