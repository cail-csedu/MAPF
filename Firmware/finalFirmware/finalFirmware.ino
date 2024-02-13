#include <SoftwareSerial.h>
#define resetPin 4
#define robot_1 1
#include "HCPCA9685.h"

#ifdef robot_1
#include "variables1.h"
#elif robot_2
#include "variables2.h"
#elif robot_3
#include "variables3.h"
#elif robot_4
#include "variables4.h"
#elif robot_5
#include "variables5.h"
#else
#endif

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address is 0x40 */
#define  I2CAdd 0x40

#define sensorNum 6  //number of sensror in array
#define rotationSpeed 90


HCPCA9685 HCPCA9685(I2CAdd);


const int motorPin1 = 10, motorPin2 = 11;   //right motor
const int motorPin3 = 9, motorPin4 = 6;  //left motor


int i = 0;
int Speed = 50;
int Delay = 70;

int Step = 0;
int temp;


//=================Line following variables
int irArrayPins[] = {A7, A6, A3, A2, A1, A0};
int digitalReading[6]; //holds state of ir sensors. 1>>black, 0>>white


float error, prevError = 0;
float mappedValue, targetValue = 5;      //mapped value ranges from 0 to 10, 5 is target(means in middle of the line)
int checkpoint = 0;


float safety = 0.70;


int motorResponse;
float correction;

int leftSpeed, rightSpeed;
int digitalValue;


float lastAct;
int time = 7; //calibration time in second

char command;

void setup()
{
  //defining motor pins as input to prevent bootup random pwm signal
  pinMode(motorPin1, INPUT_PULLUP);
  pinMode(motorPin2, INPUT_PULLUP);
  pinMode(motorPin3, INPUT_PULLUP);
  pinMode(motorPin4, INPUT_PULLUP);

  Serial.begin(9600);
  //initialize IR pins
  for (int i = 0; i < sensorNum; i++)
  {
    pinMode(irArrayPins[i], INPUT);
  }

  //initialize motor pins
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);



  //Arm initialization
  HCPCA9685.Init(SERVO_MODE);

  /* Wake the device up */
  HCPCA9685.Sleep(false);

  // Initialize arm to home

  servo01(pick_locations_right[0][0]);
  servo02(pick_locations_right[0][1]);
  servo03(pick_locations_right[0][2]);
  servo04(pick_locations_right[0][3]);
  servo05(pick_locations_right[0][4]);
  servo06(pick_locations_right[0][5]);
  servo07(cameraFront);


#ifdef robot_1
  //R1 "FFLFFFFpFLFqF"
  delay(3000);
//
  //Forward(90, 2600);
  nextNode(); nextNode();
  delay(200);
  Forward(90, 200);
  Motor(-100, 90, 1550);

  //  Forward(90, 5000);
  nextNode(); delay(200); nextNode(); delay(200); nextNode(); delay(200); nextNode(); delay(200);
  lookRight();
  lookLeft();
  lookForward();
  //  Forward(90, 1300);
  nextNode();
  delay(200);
  Forward(90, 200);
  Motor(-100, 90, 1580);
  //  Forward(90, 1300);
  nextNode();
  Forward(90, 300);
  brake();
  delay(200);
  placeRight();
  Forward(90, 3000);

#elif robot_2
  //R2 "FLFFFFpFFLFq"
  delay(4000);
  //  Forward(90, 1350);
  nextNode();
  Forward(90, 210);
  brake();
  delay(200);
  Motor(-150, 130, 1100);

  //  Forward(90, 5000);
  nextNode(); delay(50); nextNode(); delay(50); nextNode(); delay(50); nextNode(); delay(50);
  lookRight();
  lookLeft();
  lookRight();
  pickRight();

//  Forward(90, 2500);
  nextNode(); delay(50); nextNode(); delay(50);
  Forward(90, 300);
  brake();
  
  delay(200);
  Motor(-150, 130, 1000);
  Forward(90, 1300);
  //nextNode();
  delay(200);
  placeRight();
#elif robot_3

#elif robot_4
  //R4 "wait FFFFpFFLFq"
  delay(20000);

  Motor(60, 70, 5000);
  delay(2000);
  lookRight();
  lookLeft();
  lookRight();

  pickRight();
  delay(12000);

  Motor(60, 70, 2230);
  delay(200);
  Motor(-90, 80, 1280);

  Motor(65, 75, 1400);
  delay(200);
  placeRight();

#elif robot_5

#else

#endif



  //calibration();
  //delay(3000);
  //nextNode();
  //delay(2000);
  //nextNode();
  //delay(2000);
}


void loop()
{
  //sensorMapping();
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'F') {
      nextNode();
      //testMotorMS();
    }

    else if (command == 'R') {
      Serial.println("Turning Right");
      rotateRight();
    }
    else if (command == 'L') {
      Serial.println("Turning left");
      rotateLeft();
    }
    else if (command == 'P') {
      Serial.println("Picking from left");
      pickLeft();
    }
    else if (command == 'p') {
      Serial.println("Picking from right");
      pickRight();
    }
    else if (command == 'Q') {
      Serial.println("Placing to left");
      placeLeft();
    }
    else if (command == 'q') {
      Serial.println("Placing to right");
      placeRight();
    }
    else if (command == 'x') {
      Serial.println("Look left");
      lookLeft();
    }
    else if (command == 'y') {
      Serial.println("Look forward");
      lookForward();
    }
    else if (command == 'z') {
      Serial.println("Look right");
      lookRight();
    }
    else if (command == 'c') {
      Serial.println("Calibrating");
      calibration();
    }


  }


}

void nextNode() {
  forward(maxSpeed);
  delay(400);
  while (1) {

    sensorMapping();//This function maps the sensor values to understand the robot position.
    //Serial.println(mappedValue);

    if (mappedValue != 0) //when all sensors are on white line mappedValue=0. So if it is on black line...
    {
      //digitalReading[1] == 1 && digitalReading[2] == 1 && digitalReading[3] == 1 && digitalReading[4] == 1
      if (digitalReading[0] == 1 and digitalReading[sensorNum - 1] == 1) {
        //1 0 0 0 0 1
        brake();
        Serial.println("Node reached");
        break;
      }
      else {
        //Serial.println("Following line");
        pid(); //run pid calculation in each loop
        motor(leftSpeed, rightSpeed); //run motor after planning
        lastAct = mappedValue; //save last mappedValue
      }

    }

  }
}


void rotateRight() {
  forward(100);
  delay(550);
  plannedCRotate();
  delay(700);
  sensorMapping();
  while (digitalReading[2] != 1 and digitalReading[3] != 1) {
    //0 0 1 1 0 0
    sensorMapping();
  }
  brake();
  Serial.println("Rotated Right");
}

void rotateLeft() {
  forward(100);
  delay(500);
  plannedACRotate();
  delay(700);
  sensorMapping();
  while (digitalReading[2] != 1 and digitalReading[3] != 1) {
    //0 0 1 1 0 0
    sensorMapping();
  }
  brake();
  Serial.println("Rotated Left");
}


void sensorMapping()
{
  int sum = 0, coun = 0;

  for (int i = 0; i < sensorNum; i++) //from 0 to 5 number sensor. Where 0 --> rightmost, 5 --> leftmost
  {
    //Serial.print(analogRead(irArrayPins[i]));
    //Serial.print(",");
    if (analogRead(irArrayPins[i]) < blackLimit[i]) //assuming low IR value in black
    {
      sum += i * 2; //Calculating sum of the all (sensor_number*2),  that is on top of black line
      coun++;     //Count of number of sensor on black line

      digitalReading[i] = 1; // 1 means on black


    }
    else digitalReading[i] = 0;

    Serial.print(digitalReading[i]);
    Serial.print(", ");
  }
  Serial.println("");
  if (coun != 0) {
    //calculating average. ie. mappedValue.
    mappedValue = sum / coun;
    //mappedValue ranges from 0 to 10
    //5 means robot is in middle of line
  }
  else mappedValue = 0;


}


void pid()
{

  error = targetValue - mappedValue;              //Error is the offset from middle position
  correction = (kp * error) + (kd * (error - prevError)); //proportional correction uses only error.  differental correction calculated by taking difference of error
  prevError = error;
  motorResponse = (int)correction;


  //keeping correctd value inside max speed limit
  if (motorResponse > maxSpeed) motorResponse = maxSpeed;
  if (motorResponse < -maxSpeed) motorResponse = -maxSpeed;


  if (motorResponse > 0)
  {
    rightSpeed = maxSpeed;
    leftSpeed = maxSpeed - motorResponse;
  }
  else
  {
    rightSpeed = maxSpeed + motorResponse;
    leftSpeed = maxSpeed;
  }

}



//auto calibration
void calibration()
{
  Serial.println("Calibrating.....");
  //plannedCRotate();  //rotate colockwise while calibrating. It will help getting different sensor values for black and white


  float upSum = 0, lowSum = 0;
  int sensorArray[sensorNum][2]; //To store min and max range of each sensor

  //getting initial values
  for (int i = 0; i < sensorNum; i++)
  {
    sensorArray[i][0] = analogRead(irArrayPins[i]);
    sensorArray[i][1] = analogRead(irArrayPins[i]);
  }


  //int loopCounter = (int)(time * 1000 / 2.5); //Will rotate the robot for this amount of time
  long tic = millis();
  while ( (millis() - tic) < time * 1000 )
  {
    for (int i = 0; i < sensorNum; i++) //read all sensor
    {
      if (analogRead(irArrayPins[i]) < sensorArray[i][0]) sensorArray[i][0] = analogRead(irArrayPins[i]); //store lowest values among all in one array
      if (analogRead(irArrayPins[i]) > sensorArray[i][1]) sensorArray[i][1] = analogRead(irArrayPins[i]); //store highest values among all in another array
    }

  }

  Serial.println("Calibrated blacklimits:");
  for (int i = 0; i < sensorNum; i++) {
    //BlackLimit is a threshold for black white decision. It is close to the mid value of highest and lowest value received by sensors while rotating
    blackLimit[i] = (int)(sensorArray[i][0] + safety * (sensorArray[i][1] - sensorArray[i][0]));
    Serial.print(blackLimit[i]);
    Serial.print(",");
  }
  Serial.println("");

  brake();
  Serial.println("Calibration Complete.");

}

//////author github@mnakash
