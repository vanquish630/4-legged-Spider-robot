
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include<math.h>
#define pi 3.14
double dtr = pi/180;
double rtd=180/pi;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int Servomin[12];
int Servomax[12];
double theta;
double c=2.5,f=3.8,t=8,a=4; //coxa,femur,tibia,half body length
//double rotmat[3][3]={{cos(theta),-sin(theta),0},{sin(theta),cos(theta),0},{0,0,1}};

double len(double y,double z){
  return sqrt(z*z+(y-c)*(y-c));
}
double a2(double y,double z){ 
  return rtd*atan2(y-c,z);
  }
double a1(double l){ 
  return rtd*acos((l*l+f*f-t*t)/(2*l*f));
  }


double gamma(double x,double y,double bx,double by){
  return rtd*atan2(x-bx,y-bx);
  }
  
double beta(double l){
  return rtd*acos((t*t+f*f-l*l)/(2*t*f));
  }

double zd=7,bx=0,by=0,l1,l2,l3,l4,alpha11,alpha12,alpha13,alpha14,alpha21,alpha22,alpha23,alpha24,alpha1,alpha2,alpha3,alpha4,bta1,bta2,bta3,bta4,g1,g2,g3,g4,yd1,yd2,yd3,yd4;
int xi=9,yi=9,x9=10,y9=0,xe=8,ye=14; //max extend 9,16 or 8,14
double pulselen1,pulselen2,pulselen3,pulselen4;



void setup() {
  
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  delay(10);
  set_leg1(-xi,-yi);
  delay(50);
  set_leg2(-xi,yi);
  delay(50);
  set_leg3(xi,-yi);
  delay(50);
  set_leg4(xi,yi);
  delay(1000);
}



char inpt;
void loop(){
  if (Serial.available() > 0) {
    Serial.println("enter choice");
    inpt = Serial.read();
    if(inpt=='w'){
      walk_forward();
      }
      if(inpt=='u'){
      increase_height();
      }
      if(inpt=='d'){
      decrease_height();
      }
      if(inpt=='r'){
      reset();
      }
    
    }
  
  }


void reset(){
  zd=7;
   delay(10);
  set_leg1(-xi,-yi);
  delay(50);
  set_leg2(-xi,yi);
  delay(50);
  set_leg3(xi,-yi);
  delay(50);
  set_leg4(xi,yi);
  delay(1000);
  }



void walk_forward(){
int stp =0;
for(int i=1;i<12;i++){
stp++;
if(stp>0&&stp<=3){
  switch(stp){
    case 1:
           pwm.setPWM(1,0,195);
           delay(100);
           set_leg1(-xi,-yi);   
           delay(1000);        
           pwm.setPWM(10,0,497); 
           delay(100);          
           set_leg2(-xi,yi); 
           delay(1000);        
          
           pwm.setPWM(7,0,475);
           delay(100);
           set_leg3(x9,-y9);
           delay(1000);        
           
           pwm.setPWM(4,0,180);
           delay(100);
           set_leg4(xe,ye);
           delay(100);
    break;
    case 2:
            //pwm.setPWM(4,0,180);
           delay(100);
           //set_leg4(xe,ye);
           //delay(100);
    break;
    case 3:
    delay(100);
    Serial.println("move body");
    body_forward1();
    delay(100);
   // stp=0;
    break;
    }
  }
else if(stp>3&&stp<=6){
  switch(stp){
    case 4:
           pwm.setPWM(1,0,195);
           delay(200);
           set_leg1(-x9,-y9); 
           delay(100);        
           /*pwm.setPWM(10,0,497); 
           delay(100);          
           set_leg2(-x9,y9); 
           delay(1000);        
          
           pwm.setPWM(7,0,475);
           delay(100);
           set_leg3(xi,-yi);
           delay(1000);        
           
           pwm.setPWM(4,0,180);
           delay(100);
           set_leg4(xi,yi);
           delay(2000);
           */
    break;
    case 5:
    pwm.setPWM(10,0,497);
           delay(100);
           set_leg2(xe,ye);
           delay(100);
    case 6:
    Serial.println("move body");
    delay(500);
    body_forward2();
    delay(100);
    stp=0;
    break;
    
    }
  }


}
  }

void increase_height(){
  zd+=2;
  set_leg1(-xi,-yi);
  delay(50);
  set_leg2(-xi,yi);
  delay(50);
  set_leg3(xi,-yi);
  delay(50);
  set_leg4(xi,yi);
  delay(100);
  }
void decrease_height(){
  zd-=2;
  set_leg1(-xi,-yi);
  delay(50);
  set_leg2(-xi,yi);
  delay(50);
  set_leg3(xi,-yi);
  delay(50);
  set_leg4(xi,yi);
  delay(100);
  }


void body_forward1(){
  //set_leg4(6,6);
  pulselen1= map(160,60,180,280,600);
  pwm.setPWM(0,0,pulselen1);
  //set_leg1(-xe,-ye);
  Serial.println("rotating leg1");
  pulselen4= map(135,60,160,275,475);
  pwm.setPWM(3,0,pulselen4);
   pwm.setPWM(4,0,180);
  set_leg4(xi,yi);
  Serial.println("rotating leg4");
  pulselen3= map(135,75,180,420,150);
  pwm.setPWM(6,0,pulselen3);
  //set_leg3(xi,-xi);
  Serial.println("rotating leg3");
  pulselen2= map(90,70,180,400,135);
  pwm.setPWM(9,0,pulselen2);
 // set_leg2(-x9,y9);
  Serial.println("rotating leg2");
    delay(1000);
  }



void body_forward2(){
  //set_leg4(6,6);
  pulselen1= map(135,60,180,280,600);
  pwm.setPWM(0,0,pulselen1);
  //set_leg1(-xe,-ye);
  Serial.println("rotating leg1");
  pulselen4= map(90,60,160,275,475);
  pwm.setPWM(3,0,pulselen4);
 // set_leg4(xi,yi);
  Serial.println("rotating leg4");
  pulselen3= map(160,75,180,420,150);
  pwm.setPWM(6,0,pulselen3);
  //set_leg3(xi,-xi);
  Serial.println("rotating leg3");
  pulselen2= map(135,70,180,400,135);
  pwm.setPWM(9,0,pulselen2);
  pwm.setPWM(10,0,497); 
  set_leg2(-xi,yi);
  Serial.println("rotating leg2");
    delay(1000);
    
  }



void set_leg1(double x1,double y1){
 
 yd1=sqrt((x1-bx)*(x1-bx)+(y1-by)*(y1-by))-sqrt(2*a*a);
 g1 = fabs(gamma(x1,y1,bx,by));
  l1 = len(yd1,zd);
  alpha21 = a2(yd1,zd);
  alpha11 = a1(l1);
  alpha1 = alpha11+alpha21;
  pulselen1= map(alpha1,40,180,450,125);
  //Serial.print("pulselen1 is");Serial.println(pulselen1);
  bta1 = beta(l1);
  pulselen1= map(bta1,40,180,204,550);
  //Serial.print("pulselen1 is");Serial.println(pulselen1);
if(g1<60){
  g1=180-g1;
  }
  if(g1>=60&&g1<=180){
pulselen1= map(g1,60,180,280,600);
pwm.setPWM(0,0,pulselen1);
  }
delay(10);
if(alpha1>=40&&alpha1<=180){
pulselen1= map(alpha1,40,180,450,125);
pwm.setPWM(1,0,pulselen1);
}
delay(10);
if(bta1>=40&&bta1<=180){
pulselen1= map(bta1,40,180,204,550);
pwm.setPWM(2,0,pulselen1);
}
delay(10);

Serial.print("gamma1 is");Serial.println(g1);
Serial.print("l1 is");Serial.println(l1);
Serial.print("alpha1 is");Serial.println(alpha1);
Serial.print("beta1 is");Serial.println(bta1);
delay(10);
  }


void set_leg4(double x4,double y4){
   yd4=sqrt((x4-bx)*(x4-bx)+(y4-by)*(y4-by))-sqrt(2*a*a);
   g4 = fabs(gamma(x4,y4,bx,by));
   l4 = len(yd4,zd);
   alpha24 = a2(yd4,zd);
   alpha14 = a1(l4);
   alpha4 = alpha14+alpha24;
   pulselen4= map(alpha4,40,160,500,150);
  // Serial.print("pulselen is");Serial.println(pulselen4);
   bta4 = beta(l4);
   pulselen4= map(bta4,50,170,275,575);
  // Serial.print("pulselen is");Serial.println(pulselen4);

if(g4<60){
    g4=180-g4;
}
if(g4>=60&&g4<=160){
    pulselen4= map(g4,60,160,275,475);
    pwm.setPWM(3,0,pulselen4);
  }
delay(10);
if(alpha4>=40&&alpha4<=160){
    pulselen4= map(alpha4,40,160,500,150);
    pwm.setPWM(4,0,pulselen4);
}
delay(10);
if(bta4>=50&&bta4<=170){
    pulselen4= map(bta4,50,170,275,575);
    pwm.setPWM(5,0,pulselen4);
}
delay(10);
  
  Serial.print("gamma4 is");Serial.println(g4);
  Serial.print("l4 is");Serial.println(l4);
  Serial.print("alpha4 is");Serial.println(alpha4);
  Serial.print("beta4 is");Serial.println(bta4);
delay(10);

    }


void set_leg3(double x3,double y3){
   yd3=sqrt((x3-bx)*(x3-bx)+(y3-by)*(y3-by))-sqrt(2*a*a);
   g3 = fabs(gamma(x3,y3,bx,by));
   l3 = len(yd3,zd);
   alpha23 = a2(yd3,zd);
   alpha13 = a1(l3);
   alpha3 = alpha13+alpha23;
   pulselen3= map(alpha3,40,180,200,550);
  //Serial.print("pulselen is");Serial.println(pulselen3);
   bta3 = beta(l3);
  pulselen3= map(bta3,50,160,425,150);
 // Serial.print("pulselen is");Serial.println(pulselen3);
  
  

if(g3<75){
    g3=180-g3;
  }
if(g3>=75&&g3<=180){
    pulselen3= map(g3,75,180,420,150);
    pwm.setPWM(6,0,pulselen3);
  }
delay(10);
if(alpha3>=40&&alpha3<=180){
    pulselen3= map(alpha3,40,180,200,550);
    pwm.setPWM(7,0,pulselen3);
}
delay(10);
if(bta3>=50&&bta3<=160){
    pulselen3= map(bta3,50,160,425,150);
    pwm.setPWM(8,0,pulselen3);
}
delay(10);
  Serial.print("gamma3 is");Serial.println(g3);
  Serial.print("l3 is");Serial.println(l3);
  Serial.print("alpha3 is");Serial.println(alpha3);
  Serial.print("beta3 is");Serial.println(bta3);

delay(10);

    }

void set_leg2(double x2,double y2){
   yd2=sqrt((x2-bx)*(x2-bx)+(y2-by)*(y2-by))-sqrt(2*a*a);
   g2 = fabs(gamma(x2,y2,bx,by));
   l2 = len(yd2,zd);
   alpha22 = a2(yd2,zd);
   alpha12 = a1(l2);
   alpha2 = alpha12+alpha22;
   pulselen2= map(alpha2,40,180,215,575);
  // Serial.print("pulselen is");Serial.println(pulselen2);
   bta2 = beta(l2);
   pulselen2= map(bta2,60,180,425,125);
  // Serial.print("pulselen is");Serial.println(pulselen2);
   

if(g2<70){
    g2=180-g2;
}
if(g2>=70&&g2<=180){
    pulselen2= map(g2,70,180,400,135);
    pwm.setPWM(9,0,pulselen2);
}
delay(10);
if(alpha2>=40&&alpha2<=180){
    pulselen2= map(alpha2,40,180,215,575);
    pwm.setPWM(10,0,pulselen2);
}
delay(10);
if(bta2>=60&&bta2<=180){
    pulselen2= map(bta2,60,180,425,125);
    pwm.setPWM(11,0,pulselen2);
}
delay(10);
   Serial.print("gamma2 is");Serial.println(g2);
   Serial.print("l2 is");Serial.println(l2);
   Serial.print("alpha2 is");Serial.println(alpha2);
   Serial.print("beta2 is");Serial.println(bta2);
delay(10);


    }
    
