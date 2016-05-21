#include <Arduino.h>
#include "hardware.h"
#include "esc.h"
#include <FLEXCAN.h>
#include <kinetis_flexcan.h>

volatile byte pulses;
uint32_t total_pulses;
float speed;

uint8_t led_toggle = 0;

uint32_t Serial_timer;
unsigned long timeold;
uint32_t Dyno_timer;

int throttle_val = 10;
int rawIn = 10;
float minPedalVoltage = 140.0;
int maxPedalVoltage = 1010;

float WHEELCIRC;

int radius = 0.444;

Esc myEsc;

FlexCAN CANTx(500000);
static CAN_message_t msg;

void rpm_fun(){
 pulses++;
 total_pulses++;
 if(led_toggle == 0){
  digitalWrite(led1,HIGH);
  led_toggle = 1;
 }
 else{
  digitalWrite(led1,LOW);
  led_toggle = 0;
 }
}

void setup(){
	pinMode(led1,OUTPUT);
	pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);

	Serial.begin(9600);
  delay(1000);

  //pins must be set to input before interrupt is attached
  pinMode(encoder_pin3, INPUT);
  pinMode(encoder_pin2, INPUT);
  pinMode(encoder_pin, INPUT);
  attachInterrupt(encoder_pin, rpm_fun, RISING);
  pulses = 0;
  WHEELCIRC = 2 * PI * radius;

  myEsc.begin();
  delay(15000);
	timeold = millis();
  Dyno_timer = millis();

	CANTx.begin();
}

void loop(){
 if (millis() - Serial_timer > 100)
 {
  Serial.flush();
  Serial.print((float)millis() / 1000);
  Serial.print(",");
  Serial.print(speed);
  Serial.print(",");
  Serial.println(total_pulses/7);
 }
 if (pulses >= 100) {
   //Update RPM every 20 counts, increase this for better RPM resolution,
   //decrease for faster update

   // calculate the revolutions per minute
   speed = pulses;

   speed = speed * 1000;
   speed = speed / (float)(millis() - timeold);
   speed = speed * 60 / 7;

   timeold = millis();
   pulses = 0;
 }

 	rawIn = analogRead(A11);
	//int throttleVoltage = ((rawIn * 33)) / 10230;
	throttle_val = ((rawIn - minPedalVoltage) / (maxPedalVoltage - minPedalVoltage)) * 180;
	Serial.print("Raw In: ");
	Serial.println(rawIn);
	Serial.println("Throttle Value: ");
	Serial.println(throttle_val);

	if (throttle_val <= 180 && throttle_val >= 0){
		myEsc.write(throttle_val);
	}
	else if (throttle_val > 180){
		myEsc.write(180);
	}
	else{
		myEsc.write(0);
	}
}
