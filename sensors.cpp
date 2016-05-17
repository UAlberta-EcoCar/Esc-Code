#include "sensors.h"

uint16_t Sensors::mcurrent(int curr_sens_pin) {
  /*
   * curr_val = (analogvalue - zero'ing_factor)/linearity_factor
   */
  curr_val = (analogRead(curr_sens_pin) - 303)/2.71;
}

//int enc1_val, int enc1, int enc_inc, int enc1_count, int enc1_avg, int count, int enc1_hold, int wheel_diam, int gear_rat, uint16_t runtime, uint16_t velocity
uint16_t Sensors::mspeed(int enc1_count, int enc_inc, int enc1_avg, int enc1_val, int enc1_hold, int count, int wheel_diam, int gear_rat, uint16_t runtime, uint16_t speedtimer) {
  enc1_val = 0;
  enc1_count++;

  for (enc_inc = 0; enc_inc<enc1_avg; enc_inc++) {
    enc1_val = enc1_val + digitalRead(enc1);
  }
  if (enc1_val > enc1_avg/2) {
    if (enc1_hold == 0) {
      count++;
      enc1_hold = 1;
    }
  }
  else {
    enc1_hold = 0;
  }

  if (count > 63 || enc1_count > 4000) {
    velocity = (count*3600)*(3.14*wheel_diam)/(gear_rat*7*(millis()-runtime));
    count = 0;
    enc1_count = 0;
    runtime = millis();
    if (millis() - speedtimer > 500) {
      Serial.print("Velocity: ");
      Serial.println(velocity);
      speedtimer = millis();
    }
  }
  return velocity;
}

/* Attempt to use interrupt's for measuring velocity
BEFORE VOID SETUP IN .ino
  int enc1;
  volatile int enc_inc;

IN VOID setup
  pinMode(pin, OUTPUT); //ASSUMING THIS
  attachInterrupt(digitalPinToInterrupt(enc1), encoder_counter, FALLING);


  void Sensors::mspeed(uint16_t velocity) {

  void encoder_counter() {
  enc_inc++;
}
}
  */
