#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

class Sensors {
public:

  Sensors() {};
  uint16_t mcurrent(int curr_sens_pin);
  uint16_t mspeed(int enc1_count, int enc_inc, int enc1_avg, int enc1_val, int enc1_hold, int count, int wheel_diam, int gear_rat, uint16_t runtime, uint16_t speedtimer);
  uint16_t pinger();

private:
  int enc1;
  int curr_sens_pin;
  int16_t speedtimer;
  int enc1_val;
  int enc_inc;
  int enc1_count;
  int enc1_avg;
  int count;
  int enc1_hold;
  uint16_t runtime;
  int wheel_diam;
  int gear_rat;
  uint16_t curr_val;
  uint16_t velocity;

};
#endif
