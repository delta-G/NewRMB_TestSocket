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

#include "NewRMB_TestSocket.h"

uint8_t heartbeatPin = 12;
unsigned long heartDelay = 500;

StreamParser parser(&Serial, '<', '>', handleSerial);

uint8_t xpander1CSpin = 1;
uint8_t xpander2CSpin = 15;
uint8_t xpander2HwAddy = 3;

MCP23S09 xpander(xpander1CSpin);
MCP23S08 powerXpander(xpander2CSpin, xpander2HwAddy);

uint8_t currentXpander = 0;

Motor motors[2] = { Motor(LEFT_MOTOR_DIRECTION_PIN_1,
LEFT_MOTOR_DIRECTION_PIN_2, LEFT_MOTOR_ENABLE_PIN, false), Motor(
RIGHT_MOTOR_DIRECTION_PIN_1, RIGHT_MOTOR_DIRECTION_PIN_2,
RIGHT_MOTOR_ENABLE_PIN, false) };

void setup() {
	uint8_t mcusr = MCUSR;
	MCUSR = 0;

	pinMode(4, OUTPUT);
	xpander.init();
	powerXpander.init();
	pinMode(heartbeatPin, OUTPUT);

	pinMode(0, OUTPUT);
	digitalWrite(0, HIGH);

	setupPCint();
	setTickCallback(leftTick, rightTick);
	motors[0].init();
	motors[1].init();

	Serial.begin(115200);
	delay(250);
	Serial.println(F("Beginning"));
	Serial.println(F("End of Setup"));
	Serial.println(F("Vers - 30"));
	Serial.println(mcusr, HEX);
}

void loop() {

	heartbeat();
	parser.run();
	motors[0].loop();
	motors[1].loop();

}

void heartbeat() {
	static boolean heartState = false;
	static unsigned long prev = millis();
	unsigned long cur = millis();

	if (cur - prev >= heartDelay) {
		prev = cur;
		heartState = !heartState;
		digitalWrite(heartbeatPin, heartState);
	}
}

void handleSerial(char *p) {
	switch (p[1]) {

//	case 'q':
//		digitalWrite(1, LOW);
//		break;
//	case 'Q':
//		digitalWrite(1, HIGH);
//		break;

	case 'M': {
		uint8_t mot = p[2] - '0';
		switch (p[3]) {
		case '0':
			motors[mot].stop();
			break;
		case '1':
			motors[mot].driveForward();
			break;
		case '-':
			motors[mot].driveBackward();
			break;
		case 'C':
			motors[mot].coast();
			break;
		case 'P': {
			int pwmSpeed = atoi((const char*) p + 4);
			motors[mot].drive(pwmSpeed);
			break;
		}
		case 'S': {
			int setSpeed = atoi((const char*) p + 4);
			motors[mot].setSpeed(setSpeed);
			break;
		}
		}
		break;
	}  // end case 'M'
	case 'I':
		Serial.println(F("Initializing expander"));
		xpander.setPinMode(0, OUTPUT);
		xpander.writePin(0, LOW);

		xpander.setPinMode(1, OUTPUT);
		xpander.writePin(1, LOW);

		xpander.setPinMode(2, OUTPUT);
		xpander.writePin(2, LOW);

		xpander.setPinMode(3, OUTPUT);
		xpander.writePin(3, LOW);

		xpander.setPinMode(4, INPUT);
		xpander.setPinMode(5, INPUT);
		xpander.setPinMode(6, INPUT);
		xpander.setPinMode(7, INPUT);
		Serial.println(F("Expander setup compete."));
		break;

	case 'T':
		Serial.print(F("Ticks L - "));
		Serial.print(motors[0].encoder.getTicks());
		Serial.print(F(" : R - "));
		Serial.print(motors[1].encoder.getTicks());
		Serial.println();
		break;
	case 'S':
		Serial.print(F("Speed L - "));
		Serial.print(motors[0].encoder.getSpeed());
		Serial.print(F(" : R - "));
		Serial.print(motors[1].encoder.getSpeed());
		Serial.println();
		break;

	case 'P':
		printMcpRegisters();
		break;
	case 'p':
		Serial.println(F("Got Pinged"));
		break;
	case 'X':
		if (p[2] == '0') {
			currentXpander = 0;
			Serial.println(F("Xpander-0"));
		} else {
			currentXpander = 1;
			Serial.println(F("Xpander-1"));
		}
		break;
	case '0' ... '7': {
		uint8_t pin = p[1] - '0';
		Serial.print(F("Xpander "));
		Serial.print(currentXpander);
		Serial.print(F(" Pin "));
		Serial.print(pin);
		Serial.print(F(" set to "));
		switch (p[2]) {
		case 'O':
			if (currentXpander == 0) {
				xpander.setPinMode(pin, OUTPUT);
			} else if (currentXpander == 1) {
				powerXpander.setPinMode(pin, OUTPUT);
			}
			Serial.println(F("OUTPUT"));
			break;
		case 'i':
			if (currentXpander == 0) {
				xpander.setPinMode(pin, INPUT);
			} else if (currentXpander == 1) {
				powerXpander.setPinMode(pin, INPUT);
			}
			Serial.println(F("INPUT"));
			break;
		case 'I':
			if (currentXpander == 0) {
				xpander.setPinMode(pin, INPUT_PULLUP);
			} else if (currentXpander == 1) {
				powerXpander.setPinMode(pin, INPUT_PULLUP);
			}
//	    	xpanders[currentXpander].setPinMode(pin, INPUT_PULLUP);
			Serial.println(F("INPUT_PULLUP"));
			break;
		case 'H':
			if (currentXpander == 0) {
				xpander.writePin(pin, HIGH);
			} else if (currentXpander == 1) {
				powerXpander.writePin(pin, HIGH);
			}
//	    	xpanders[currentXpander].writePin(pin, HIGH);
			Serial.println(F("HIGH"));
			break;
		case 'L':
			if (currentXpander == 0) {
				xpander.writePin(pin, LOW);
			} else if (currentXpander == 1) {
				powerXpander.writePin(pin, LOW);
			}
//	    	xpanders[currentXpander].writePin(pin, LOW);
			Serial.println(F("LOW"));
			break;
		case 'R':
			Serial.print(F("Read Xpander "));
			Serial.print(currentXpander);
			Serial.print(F(" Pin "));
			Serial.print(pin);
			Serial.print(F(" - "));
			if (currentXpander == 0) {
				Serial.print(xpander.readPin(pin));
			} else if (currentXpander == 1) {
				Serial.print(powerXpander.readPin(pin));
			}
//	    	Serial.print(xpanders[currentXpander].readPin(pin));
			Serial.println(F(" - "));
			break;
		}
		break;
	}  // end case '0' ... '7'

	default:
		break;
	}
}

void printMcpRegisters() {
	for (int i = 0; i < 11; i++) {
		Serial.print(F("Reg "));
		Serial.print(i, HEX);
		Serial.print(F(" : "));
		if (currentXpander == 0) {
			Serial.print(xpander.readRegister(i), HEX);
		} else if (currentXpander == 1) {
			Serial.print(powerXpander.readRegister(i), HEX);
		}
//		Serial.print(xpanders[currentXpander].readRegister(i), HEX);
		Serial.println(F("  -"));
	}
}

void leftTick(boolean aForw) {
	motors[0].encoder.tick(aForw);
}

void rightTick(boolean aForw) {
	motors[1].encoder.tick(aForw);
}
