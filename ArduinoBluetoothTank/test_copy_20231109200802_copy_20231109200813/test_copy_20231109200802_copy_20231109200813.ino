//Brandon Syverson
//Bluetooh controlled tank via arduino uno 
//Phone app controller: "USBRControl"
//Bluetooth module = HC-06

//libraries
#include <Servo.h>//servo library

//variables
int data;
Servo rightServo;//right wheel
Servo leftServo;//left wheel

Servo turretRotate;
Servo turretRaise;

int servoTurretPosition = 120;//start turretRaise in lowered position (120)

const int sensorPin = 0;//light sensor
const int ledPin = 2;
int lightLevel, high = 0, low = 1023;

//setup
void setup() 
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);                                                   
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
  
  rightServo.attach(13);
  leftServo.attach(12);

  turretRotate.attach(11);
  turretRaise.attach(10);

  turretRaise.write(servoTurretPosition);//start lowered (120)

  pinMode(ledPin, OUTPUT);
}

//loop
void loop() 
{

//TEST
  //turretShoot();
  //driveRight();

  //read data
  while(Serial.available() > 0){
    data = Serial.read();//'data' is a keycode indicating which button the app was pushed 
    Serial.print(data);
  }

  //restart arduino 
  if(data == 108){//D button
    restart();
  }

  //driving movement
  if(data == 99){//right top button
    driveForward();
  }
  else if(data == 100){//left bottom button
    driveReverse();
  }
  else if(data == 114){//left middle button
    driveStop();
  }

  else if(data == 98){//left right button
    driveRight();
  }
  else if(data == 97){//left left button
    driveLeft();
  }

  //turret movement
  else if(data == 101){//right left button
    turretRotateLeft();
  }
  else if(data == 102){//right right button
    turretRotateRight();
  }
  else if(data == 103){//right up button
    if(servoTurretPosition > 100){
      servoTurretPosition = servoTurretPosition - 5;
      turretRaiseUp(servoTurretPosition);
    }
  }
  else if(data == 104){//right bottom button
    //turretRaiseDown();
      if(servoTurretPosition < 120){
        servoTurretPosition = servoTurretPosition + 5;
        turretRaiseUp(servoTurretPosition);
    }
  }
  else if(data == 112){//R button
    turretShoot();
  }


  //stopping methods
if(data == 0){
    driveStop();
    turretStop();
    turretRaiseStop();
  }

  //debug
debug(500);//prints bluetooth signal codes at 500 speed
  if(data != 0){
    data = 0;
  }

  //headlights
headlights();//enables headlights when dark
}//end loop

//----------methods----------

//headlights
void headlights(){
  lightLevel = analogRead(sensorPin);
  manualTune();
  analogWrite(ledPin, lightLevel);
}

//driving methods
void driveForward()//both servos forward
{
  rightServo.write(180);
  leftServo.write(0);
}

void driveReverse(){//both servos reverse
  rightServo.write(0);
  leftServo.write(180);
}

void driveStop(){//both servos stop
  rightServo.write(91);
  leftServo.write(91);
}

void driveRight(){//left servo forward, right servo reverse
  rightServo.write(180);
  leftServo.write(180);
}

void driveLeft(){//left servo reverse, right servo forward
  rightServo.write(0);
  leftServo.write(0);
}


//turret methods
void turretRotateRight(){//rotate turret right
  turretRotate.write(85);//86
}

void turretRotateLeft(){//rotate turret left
  turretRotate.write(96);//96
}

void turretStop(){//stop turret
  turretRotate.write(91);
}

void turretRaiseUp(int x){//raise barrel up (x)
  //turretRaise.write(80);
  turretRaise.write(x);
}


void turretRaiseDown(int x){//raise barrel down (x)
  //turretRaise.write(110);
  turretRaise.write(x);
}


void turretRaiseStop(){//stop barrel movement
  //turretRaise.write(91);
}

void turretShoot(){//light LED on barrel and make sound with speaker 
  tone(9, 5000);
  delay(10);
  noTone(9);
  digitalWrite(3, HIGH);
  delay(1000);      
  digitalWrite(3, LOW); 
}

//debug method
int debug(int time){//display which button is clicked throught serial monitor and bluetooth
  delay(time);
  Serial.print(data);
}

void autoTune()
{
  if (lightLevel < low)
  {
    low = lightLevel;
  } 
  if (lightLevel > high)
  {
    high = lightLevel;
  }
  lightLevel = map(lightLevel, low+30, high-30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
}

void manualTune()
{
  lightLevel = map(lightLevel, 0, 1023, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
} 

void restart() {
  delay(100);
  Serial.println("Restarting Arduino...");
  asm volatile ("  jmp 0");//restarts software
  delay(100);
}

