/*
Simultaneously Reading Two PWM Signals from an RC Receiver with Arduino
 Brandon Tsuge
https://www.theboredrobot.com/post/simultaneously-reading-two-pwm-signals-from-an-rc-receiver-with-arduino
In this example, I demonstrate how to use Arduino to simultaneously read two RC (50Hz PWM) signals using external interrupts.
 */

//define the pins and variables
#define RCPinFWD 2
#define RCPinSide 3 

volatile long StartTimeFWD = 0;
volatile long CurrentTimeFWD = 0;
volatile long PulsesFWD = 0;
int PulseWidthFWD = 0;

volatile long StartTimeSide = 0;
volatile long CurrentTimeSide = 0;
volatile long PulsesSide = 0;
int PulseWidthSide = 0;

int motor1pin1 = 5; //right
int motor1pin2 = 6;
int motor1speed = 9;

int motor2pin1 = 7; //left
int motor2pin2 = 8;
int motor2speed = 10;


void setup() {
  //set up the serial monitor, pin mode, and external interrupt.
  Serial.begin(9600);
  pinMode(RCPinFWD, INPUT_PULLUP);
  pinMode(RCPinSide, INPUT_PULLUP);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor1speed, OUTPUT);

  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor2speed, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(RCPinFWD),PulseTimerFWD,CHANGE);
  attachInterrupt(digitalPinToInterrupt(RCPinSide),PulseTimerSide,CHANGE);
}

void loop() {
  int x; int y;
  //only save pulse lengths that are less than 2000 microseconds
  if (PulsesFWD < 2000){
    PulseWidthFWD = PulsesFWD;
  } 
  if (PulsesSide < 2000){
    PulseWidthSide = PulsesSide;
  } 
  //Serial.print(PulseWidthFWD);
  x = map(PulseWidthFWD, 1484, 1996, 0, 255);
  if (x > 4) {
          digitalWrite(motor1pin1, LOW);
          digitalWrite(motor1pin2, HIGH);
          analogWrite(motor1speed, x+4);

          digitalWrite(motor2pin1, LOW);
          digitalWrite(motor2pin2, HIGH);
          analogWrite(motor2speed, x);
  }
  if (x < (-4)) {
          digitalWrite(motor1pin1, HIGH);
          digitalWrite(motor1pin2, LOW);
          analogWrite(motor1speed, x*-1);


          digitalWrite(motor2pin1, HIGH);
          digitalWrite(motor2pin2, LOW);
          analogWrite(motor2speed, x*-1);
  } 
  if ((x <= 4) && (x >= - 4)) {
          digitalWrite(motor1pin1, LOW);
          digitalWrite(motor1pin2, LOW);
          analogWrite(motor1speed, x);

          digitalWrite(motor2pin1, LOW);
          digitalWrite(motor2pin2, LOW);
          analogWrite(motor2speed, x);
  }
  Serial.print(PulseWidthFWD);
  Serial.print("    ");
  //Serial.println(PulseWidthSide);
  y = map(PulseWidthSide, 1460, 1972, 0, 255);
  if (y > 4) {
          digitalWrite(motor2pin1, HIGH);
          digitalWrite(motor2pin2, LOW);
          analogWrite(motor2speed, y);

          digitalWrite(motor1pin1, LOW);
          digitalWrite(motor1pin2, HIGH);
          analogWrite(motor1speed, y);
  }
  if (y < -4) {
          digitalWrite(motor2pin1, LOW);
          digitalWrite(motor2pin2, HIGH);
          analogWrite(motor2speed, y*-1);

          digitalWrite(motor1pin1, HIGH);
          digitalWrite(motor1pin2, LOW);
          analogWrite(motor1speed, y*-1);
  } 
  if ((y <= 4) && ( y >= -4 ) ){
          digitalWrite(motor2pin1, LOW);
          digitalWrite(motor2pin2, LOW);
          analogWrite(motor2speed, y);

          digitalWrite(motor1pin1, LOW);
          digitalWrite(motor1pin2, LOW);
          analogWrite(motor1speed, y);
  }
  Serial.println(PulseWidthSide);
}


void PulseTimerFWD(){
  //measure the time between interrupts
  CurrentTimeFWD = micros();
  if (CurrentTimeFWD > StartTimeFWD){
    PulsesFWD = CurrentTimeFWD - StartTimeFWD;
    StartTimeFWD = CurrentTimeFWD;
  }
}

void PulseTimerSide(){
  //measure the time between interrupts
  CurrentTimeSide = micros();
  if (CurrentTimeSide > StartTimeSide){
    PulsesSide = CurrentTimeSide - StartTimeSide;
    StartTimeSide = CurrentTimeSide;
  }
}
