#include <Arduino.h>
#include "hardware.h"
#include "esc.h"

volatile byte pulses;
uint32_t total_pulses;
float speed;

uint8_t led_toggle = 0;
void rpm_fun()
{
 pulses++;
 total_pulses++;
 if(led_toggle == 0){
  digitalWrite(led1,HIGH);
  led_toggle = 1;
 }
 else
 {
  digitalWrite(led1,LOW);
  led_toggle = 0;
 }
}

uint32_t Serial_timer;
unsigned long timeold;
uint32_t Dyno_timer;

float WHEELCIRC;

int radius = 0.444;

Esc myEsc;

void setup()
{
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
  
 Serial.begin(9600);
 delay(1000);

 //pins must be set to input before interrupt is attached
 pinMode(encoder_pin3, INPUT);
 pinMode(encoder_pin2, INPUT);
 pinMode(encoder_pin, INPUT);
 attachInterrupt(encoder_pin2, rpm_fun, RISING);
 pulses = 0;
 WHEELCIRC = 2 * PI * radius; 
 
 myEsc.begin();
 delay(15000);
  timeold = millis();
  Dyno_timer = millis();
 myEsc.write(170);
}

void loop()
{
  myEsc.write(50);
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
 if(millis() - Dyno_timer > 50000)
 {
  myEsc.write(0);
 }
 if(millis() - Dyno_timer > 80000)
 {
  while(1)
  {
    myEsc.write(0);
  }
 }
}

