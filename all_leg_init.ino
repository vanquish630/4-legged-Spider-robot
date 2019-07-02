

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
}
void loop() {
  


delay(1000);

//leg 1
  pwm.setPWM(0, 0, 480);
  pwm.setPWM(1, 0, 230);
  pwm.setPWM(2, 0, 228 );
//leg 4
  pwm.setPWM(3, 0, 425);
  pwm.setPWM(4, 0, 223);
  pwm.setPWM(5, 0, 275 );
 //leg 3
  pwm.setPWM(6, 0, 266);
  pwm.setPWM(7, 0, 437);
  pwm.setPWM(8, 0, 425 );
  //leg 2
  pwm.setPWM(9, 0, 244);
  pwm.setPWM(10, 0, 459);
  pwm.setPWM(11, 0, 425 );

delay(2000);
  //leg 1
  pwm.setPWM(0, 0, 600);
  pwm.setPWM(1, 0, 230);
  pwm.setPWM(2, 0, 228 );
//leg 4
  pwm.setPWM(3, 0, 335);
  pwm.setPWM(4, 0, 223);
  pwm.setPWM(5, 0, 275 );
 //leg 3
  pwm.setPWM(6, 0, 150);
  pwm.setPWM(7, 0, 437);
  pwm.setPWM(8, 0, 425 );
  //leg 2
  pwm.setPWM(9, 0, 350);
  pwm.setPWM(10, 0, 459);
  pwm.setPWM(11, 0, 425 );
}
