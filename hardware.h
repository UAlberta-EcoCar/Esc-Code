#ifndef HARDWARE_H
#define HARDWARE_H

// CAN Bus Connections and Baud Rate
const int CAN_INT = 10;
const int BR = 9600; //set Baud Rate - 115200 doesn't work

// Set Servo Pin
const int servo_pin = 23; //Set servo pin

// Board LED's
const int led1 = 10; //set LED pins
const int led2 = 11;
const int led3 = 12;

// Encoder Control Pins
const int encoder_pin = 16;
const int encoder_pin2 = 17;
const int encoder_pin3 = 15;


//Motor Spec's
const int wheel_diam = 444; //Wheel diameter in mm's
const int gear_rat = 28; //Pre set gear ratio

#endif
