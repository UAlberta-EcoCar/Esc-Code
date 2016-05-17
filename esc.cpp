#include "esc.h"
#include "hardware.h"

void Esc::begin() {
  _esc = new Servo();

  //Initilize ESC
	//Serial.println("Initializing ESC");
  digitalWrite(led2,HIGH);
	_esc->attach(servo_pin); //ESC needs a low high low signal to turn on
	delay(500);
	_esc->write(0);
	delay(500);
	_esc->write(180);
	delay(500);
	_esc->write(0);
	delay(1000);
	//Serial.println("Electronic Speed Controller Initialization Successful");
  digitalWrite(led2,LOW);
}


void Esc::write(uint16_t throttle) {
  /*
   *Alice code: for use when the throttle or a potentiometer is attached
   *
   *throttle_val = ((throttle - zero'ing_factor)*motor_maxvalue/calculated_value_to_set_max_desired_servo_value)
   */
  _esc->write(throttle);

}


