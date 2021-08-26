//#include "L_S_Encoder_count.h"
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h> 
#include "math.h"

#define encoder0PinA 2
#define encoder0PinB 3 

int flag=0;
int check=0;
int encoder0Pos = 0;
int STBY = 7; //standby
//Motor A
int PWMA = 4; //Speed control
int AIN1 = 6; //Direction
int AIN2 = 5; //Direction

//Motor B
int PWMB = 10; //Speed control
int BIN1 = 8; //Direction
int BIN2 = 9; //Direction

void move(int motor, int speed, int direction);
void doEncoderA();
void doEncoderB();
//unsigned int ENCODER_CNT = 0;
//unsigned int Timer_flag = 0;
int Encoder_value = 0;

double vth = 0.0;
double vx = 0.0;
//int servo_angle = 85;
int dc_vel = 0;

void motor(const geometry_msgs::Twist& msg){
    vx = msg.angular.z;
    vth = msg.linear.x;
    //servo_angle = 85 + msg.angular.z * 50; //30, 85, 140 angle -> msg.angular.z * 57
    //dc_vel = abs(510*msg.linear.x);
    int a=0;
    //encoder0Pos = 0;
    //Serial.println("chekchekchekchkechk");
    if(msg.linear.x>0){
      move(0, 50, 1);
      move(1, 50, 1);
    }
    if(msg.linear.x<0){
      move(0, 50, 0);
      move(1, 50, 0);
    }
    if(msg.linear.x==0){
      move(0, 0, 0);
      move(1, 0, 0);
    }
    if(msg.angular.z>0){
      move(0, 50, 1);
      move(1, 50, 0);
    }
    if(msg.angular.z<0){
      move(0, 50, 0);
      move(1, 50, 1);
    }
    /*
      if(msg.angular.z<0){
      while(1){
        a++;
        move(2, 150,  0);
        if(a>10000){
          move(2, 0,  1);
          break;
        }
      }
    }
  if(msg.linear.x > 0){
    digitalWrite(BIN1, LOW);  
    digitalWrite(BIN2, HIGH);  
    analogWrite(PWMB, 100);  
    //servo.write(servo_angle);
    delay(1); // use delay to avoid disturbance
  }
  else if(msg.linear.x < 0){
    digitalWrite(BIN1, HIGH);  
    digitalWrite(BIN2, LOW);    
    analogWrite(PWMB, 100);  
    //servo.write(servo_angle);
    delay(1);
  }
  else{
    digitalWrite(BIN1, HIGH);  
    digitalWrite(BIN2, LOW);  
    analogWrite(PWMB, 100);
    //servo.write(servo_angle);
    delay(1);
  }
 */
}

ros::NodeHandle n;
std_msgs::Float64 encoder_msg;
ros::Publisher pub_encoder("encoder_pulse", &encoder_msg);
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", motor);

void setup() {
 
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  digitalWrite(PWMB, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  pinMode(encoder0PinA, INPUT); 
  pinMode(encoder0PinB, INPUT);
  attachInterrupt(1, doEncoderA, CHANGE); // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderB, CHANGE); // encoder pin on interrupt 1 (pin 3)
  flag=1;
  //Timer1::set(500000, Timer1_ISR);
  //Timer1::start();
  
  // ROS Node
  n.initNode();
  n.subscribe(sub);
  n.advertise(pub_encoder);
}

void loop() {
  
 //if(flag==1){
    if(vx < 0) {
    Encoder_value = encoder0Pos;
    
    }
    else if(vx > 0) {
    Encoder_value = encoder0Pos;
    
    }
    else {
    Encoder_value = 0;
    }
    encoder0Pos = 0;
    //flag=0;
 //}
    
    
  
  encoder_msg.data = Encoder_value;
  pub_encoder.publish(&encoder_msg);
  n.spinOnce();
}

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }
   else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void doEncoderA(){
  // look for a low-to-high on channel A
  //flag=1;
  if (digitalRead(encoder0PinA) == HIGH) { 
    // check channel B to see which way encoder is turning
    if (digitalRead(encoder0PinB) == HIGH) {  
      encoder0Pos = encoder0Pos + 1;
    } 
    else {
      encoder0Pos = encoder0Pos - 1;
    }
  }
  else   // must be a high-to-low edge on channel A                                       
  { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinB) == LOW) {   
      encoder0Pos = encoder0Pos + 1;
    } 
    else {
      encoder0Pos = encoder0Pos - 1;
    }
  }
  //Serial.println (encoder0Pos);
}

void doEncoderB(){
  /*
    countIntB++;  
  if (countIntB == INT_COUNT){  
    inputB = (float) INT_COUNT * 1000 / (float)(nowTime - startTimeB);  
    startTimeB = nowTime;  
    countIntB = 0;  
  }  */
  // look for a low-to-high on channel B
  //flag=1;
  if (digitalRead(encoder0PinB) == HIGH) {   
   // check channel A to see which way encoder is turning
    if (digitalRead(encoder0PinA) == LOW) {  
      encoder0Pos = encoder0Pos + 1;
    } 
    else {
      encoder0Pos = encoder0Pos - 1;
    }
  }
  // Look for a high-to-low on channel B
  else { 
    // check channel B to see which way encoder is turning  
    if (digitalRead(encoder0PinA) == HIGH) {   
      encoder0Pos = encoder0Pos + 1;
    } 
    else {
      encoder0Pos = encoder0Pos - 1;
    }
  }
  //Serial.println (encoder0Pos);
}
/*void Encoder_count() {

  ENCODER_CNT++;
}

void Timer1_ISR() {
  Timer_flag = 1;
}*/
