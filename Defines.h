/*

Robot Main Brain  --  runs on 1284P and handles onboard control of my robot
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

#ifndef DEFINES_H_
#define DEFINES_H_

#include <RobotSharedDefines.h>


/*
 *                           ATMEGA1284P
 *
 *
 *                                   +---\/---+
                xp0 Reset (D 0) PB0 1|        |40 PA0 (AI 0 / D24)     battery
                xp0 CS    (D 1) PB1 2|        |39 PA1 (AI 1 / D25)     M1FB
                xp0 INT   (D 2) PB2 3|        |38 PA2 (AI 2 / D26)     M2FB
                 M1D2 ~   (D 3) PB3 4|        |37 PA3 (AI 3 / D27)
                 M2D2 ~   (D 4) PB4 5|        |36 PA4 (AI 4 / D28)
                     MOSI (D 5) PB5 6|        |35 PA5 (AI 5 / D29)
                     MISO (D 6) PB6 7|        |34 PA6 (AI 6 / D30)    Gimbal Tilt
                      SCK (D 7) PB7 8|        |33 PA7 (AI 7 / D31)    Gimbal Pan
                                RST 9|        |32 AREF
                               VCC 10|        |31 GND
                               GND 11|        |30 AVCC
                             XTAL2 12|        |29 PC7 (D 23)          Motor Encoder
                             XTAL1 13|        |28 PC6 (D 22)          Motor Encoder
                     RX0 (D 8) PD0 14|        |27 PC5 (D 21) TDI      Motor Encoder
                     TX0 (D 9) PD1 15|        |26 PC4 (D 20) TDO      Motor Encoder
               RX1/INT0 (D 10) PD2 16|        |25 PC3 (D 19) TMS      M1IN2
               TX1/INT1 (D 11) PD3 17|        |24 PC2 (D 18) TCK      M1IN1
              HeartBeat (D 12) PD4 18|        |23 PC1 (D 17) SDA      M2IN2
               trig PWM (D 13) PD5 19|        |22 PC0 (D 16) SCL      M2IN1
          ICP1 echo PWM (D 14) PD6 20|        |21 PD7 (D 15) PWM      xp1 CS
                                     +--------+
 *
 *
 *
 *             MCP23S09 expander xp0
 *
 *                                   +---\/---+
 *                            VDD   1|        |18 VSS
 *                              NC  2|        |17 NC
 *                             CS   3|        |16 GP7   Arm Enable
 *                              SCK 4|        |15 GP6   Sonar Enable
 *                            MOSI  5|        |14 GP5   M1SF Status Flag
 *                            MISO  6|        |13 GP4   M2SF Status Flag
 *                           RESET  7|        |12 GP3
 *                       INTERRUPT  8|        |11 GP2   xp1 CS
 *      Motor Controller Enable GP0 9|        |10 GP1   xp1 RESET
 *                                   +--------+
 *
 *
 *             MCP23S09 expander xp1
 *
 *                                   +---\/---+
 *                            VDD   1|        |18 VSS
 *                              NC  2|        |17 NC
 *                             CS   3|        |16 GP7
 *                              SCK 4|        |15 GP6
 *                            MOSI  5|        |14 GP5
 *                            MISO  6|        |13 GP4
 *                           RESET  7|        |12 GP3  Headlight
 *                       INTERRUPT  8|        |11 GP2  Camera Enable
 *                Radio Enable  GP0 9|        |10 GP1  Auxiliary Power Enable
 *                                   +--------+
 *
 *
 *
 */

#define RIGHT_MOTOR_DIRECTION_PIN_1 16
#define RIGHT_MOTOR_DIRECTION_PIN_2 17
#define LEFT_MOTOR_DIRECTION_PIN_1 18
#define LEFT_MOTOR_DIRECTION_PIN_2 19


#define RIGHT_MOTOR_ENABLE_PIN 3
#define LEFT_MOTOR_ENABLE_PIN 4

#define RIGHT_MOTOR_FEEDBACK_PIN A2
#define LEFT_MOTOR_FEEDBACK_PIN A1

//#define GIMBAL_PAN_SERVO_PIN 12
//#define GIMBAL_TILT_SERVO_PIN 13
//
//#define PING_SENSOR_PIN 14

//#define HEADLIGHT_PIN 15

//#define CAM_ENABLE 28
//#define ARM_ENABLE 29
//#define COM_POWER_ENABLE 30

#define HEARTBEAT_PIN 12

#define BATTERY_PIN A0




#define NUMBER_BATTERY_READINGS_TO_AVERAGE 30




#endif /* DEFINES_H_ */
