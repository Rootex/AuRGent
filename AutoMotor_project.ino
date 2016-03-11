// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
// Plaix Corp First Robotic project.
 
#include <AFMotor.h>
#include <Servo.h>

#define MAX_SPEED 80
#define MIN_SPEED 70
#define SLOW_SPEED 60
#define trig  12 // attach pin 3 to Trig
#define echo 13 //attach pin 4 to Echo

AF_DCMotor motorlf(1);
AF_DCMotor motorrf(2);
AF_DCMotor motorlb(3);
AF_DCMotor motorrb(4);

Servo servo1;
Servo servo2;
int pos = 0;
int left, right;
void setup() {
  servo1.attach(9);
  servo2.attach(10);
  pinMode (trig,OUTPUT);
  pinMode (echo,INPUT);
  // initialize serial communication:
  Serial.begin(9600);     // set up Serial library at 9600 bps
//  Serial.println("Autonomous Navigation Project");

  // turn on motor
  motorlf.setSpeed(MAX_SPEED);
  motorrf.setSpeed(MAX_SPEED);
  motorlb.setSpeed(MIN_SPEED);
  motorrb.setSpeed(MIN_SPEED);
  motorlf.run(RELEASE);
  motorrf.run(RELEASE);
  motorlb.run(RELEASE);
  motorrb.run(RELEASE);
}

void move_forward(){
   //Forward
  motorlf.run(FORWARD);
  motorrf.run(BACKWARD);
  motorlb.run(BACKWARD);  
  motorrb.run(FORWARD);
}

void bot_stop(){
  motorlf.run(RELEASE);
  motorrf.run(RELEASE);
  motorlb.run(RELEASE);
  motorrb.run(RELEASE);
}

void move_backward(){
  //Backward
  motorlf.run(BACKWARD);
  motorrf.run(FORWARD);
  motorlb.run(FORWARD);
  motorrb.run(BACKWARD);
}

void turn_right(){
  motorrf.run(FORWARD);
  motorrb.run(BACKWARD);
  motorlf.run(FORWARD);
  motorlb.run(BACKWARD);
  }
  
void turn_left(){
  motorrf.run(BACKWARD);
  motorrb.run(FORWARD);
  motorlf.run(BACKWARD);
  motorlb.run(FORWARD);
  }

int get_motor_speed(int distance)
{
    int motor_speed = 0;
    if(distance >=40)
    {
         //motor_speed = FORWARD;
         motor_speed = map(distance,30,40,125,255);
    }
    else if(distance >= 32)
    {
         //speed.Direction = FORWARD;
         motor_speed = map(distance,22,29,70,125);
    }
    else if(distance >=25)
    {
         //speed.Direction = FORWARD;
        motor_speed = map(distance,15,21,50,70);
    }
    else if(distance >=18)
    {
         //speed.Direction = BRAKE;
         motor_speed = 0;
    }
    else if(distance >=14)
    {
         //speed.Direction = BACKWARD;
         motor_speed = map(distance,4,7,50,100);
    }
    else
    {
//     speed.Direction = BACKWARD;
     motor_speed = 200;
    }
    return motor_speed;
} 

void set_speed(int motor_speed){
    motorlf.setSpeed(motor_speed);
    motorrf.setSpeed(motor_speed);
    motorlb.setSpeed(motor_speed);
    motorrb.setSpeed(motor_speed);
}
int bot_move(int motor_speed, int distance){
  
    if(distance >=50)
    {
         set_speed(motor_speed);
         move_forward();
         return 0;
    }
    else if(distance >= 42)
    {
         set_speed(motor_speed);
         move_forward();
         return 0;
    }
    else if(distance >=35)
    {
         set_speed(motor_speed);
         move_forward();
         return 0;
    }
    else if(distance >=20)
    {
         set_speed(motor_speed);
         bot_stop();
         return 1;
    }
    else if(distance >=15)
    {
         set_speed(motor_speed);
         move_backward();
         return 0;
    }
    else
    {
//     move_backward();
       set_speed(200);
       move_backward();
    }
}

long microseconds_to_inches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second). This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
  return microseconds / 74 / 2;
}

long microseconds_to_centimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return (microseconds / 29.1) / 2;
}

int get_distance(){
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, cm;
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = microseconds_to_centimeters(duration); //Converting distance to cm
  return cm;
}

void compareDistance(){
  
  if (left>right) //if left is less obstructed 
  {
    turn_left();
    delay(500); 
  }
  else if (right>left) //if right is less obstructed
  {
    turn_right();
    delay(500);
  }
   else //if they are equally obstructed
  {
    turn_right();
    delay(1000);
  }
}

void loop() {
  int cm, motor_speed, type;
  
  cm = get_distance();
  motor_speed = get_motor_speed(cm);
  type = bot_move(motor_speed, cm); 
  if( type == 1){
        servo2.write(0); 
        delay(500);
        right = get_distance(); //scan to the right
        delay(500);
        servo2.write(165);
        delay(600);
        left = get_distance(); //scan to the left
        delay(500);
        servo2.write(90); //return to center
        delay(100);
        compareDistance();
  }
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  // convert the time into a distance
    delay(50);
   
 
//    
//  }
}
