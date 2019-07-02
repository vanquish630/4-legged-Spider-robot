

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
  
//leg 1
  pwm.setPWM(0, 0, 350);
  delay(50);
  pwm.setPWM(1, 0, 335);
  delay(50);
  pwm.setPWM(2, 0, 325 );
  delay(50);
//leg 4
  pwm.setPWM(3, 0, 335);
  delay(50);
  pwm.setPWM(4, 0, 350);
  delay(50);
  pwm.setPWM(5, 0, 375 );
  delay(50);
 //leg 3
  pwm.setPWM(6, 0, 375);
  delay(50);
  pwm.setPWM(7, 0, 325);
  delay(50);
  pwm.setPWM(8, 0, 320 );
  delay(50);
  //leg 2
  pwm.setPWM(9, 0, 350);
  delay(50);
  pwm.setPWM(10, 0, 335);
  delay(50);
  pwm.setPWM(11, 0, 315 );
  delay(50);
  
  

}
