#include <SoftwareSerial.h>
#define resetPin 4
#include "HCPCA9685.h"

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address is 0x40 */
#define  I2CAdd 0x40

#define sensorNum 6  //number of sensror in array
#define maxSpeed 100  //TO change the speed of the robot(255 can be set max)
#define rotationSpeed 70


HCPCA9685 HCPCA9685(I2CAdd);


const int motorPin1=10,motorPin2=11;        //right motor
const int motorPin3=9,motorPin4=5;       //left motor

//=================Arm variables
int motor_position[6]={25,169,178,74,41,166}; //Initial Motor position
                                                       
int i=0;
int Speed=50;
int Delay=70;

int Step=0;
int temp;

//int storage[][6]; //{ {s1,s2,...s6}, {s1,s2,...s6}, {s1,s2,...s6},.......}
int pick_locations[7][6] = {25,169,178,74,41,166,//forward
                112,169,178,74,41,166,//left
                112,128,130,74,86,166,//approach
                112,128,130,74,86,137,//grab
                112,135,130,74,95,137,//off of pick placed
                112,169,178,74,41,137,//left_grabbed
                25,169,178,74,41,137//forward grabbed
           
  };

int place_locations[7][6] = {25,169,178,74,41,137,//forward grabbed
                112,169,178,74,41,137,//left_grabbed
                112,135,130,74,95,137,//off of pick placed
                112,128,130,74,86,137,//grab
                112,128,130,74,86,166,//approach
                112,169,178,74,41,166,//left
                25,169,178,74,41,166//forward        
  };

  
//=================Line following variables
int irArrayPins[] = {A7, A6, A3, A2, A1, A0};
int digitalReading[6]; //holds state of ir sensors. 1>>black, 0>>white

int blackLimit[sensorNum];

float error, prevError=0;
float mappedValue, targetValue = 5;      //mapped value ranges from 0 to 10, 5 is target(means in middle of the line)
int checkpoint = 0;


float safety=0.35;

//PID controller >> Proportional(P), Derivative(D), Integral(I)
int kp=200;                       //Increrase Kp to increase sensitivity (Coarse tune)
int kd=0 ;                       //Increrase Kd to decrease sensitivity (Fine tune)                               

int motorResponse;
float correction;

int leftSpeed,rightSpeed;
int digitalValue;

float lastAct;
int time=7; //calibration time in second

char command;
String pidCommand;

void setup()
{
  //defining motor pins as input to prevent bootup random pwm signal
  pinMode(motorPin1, INPUT_PULLUP);
  pinMode(motorPin2, INPUT_PULLUP);
  pinMode(motorPin3, INPUT_PULLUP);
  pinMode(motorPin4, INPUT_PULLUP);
  
  Serial.begin(9600);
  //initialize IR pins
  for(int i = 0; i < sensorNum; i++)
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
  servo01(motor_position[0]);
  servo02(motor_position[1]);
  servo03(motor_position[2]);
  servo04(motor_position[3]);
  servo05(motor_position[4]);
  servo06(motor_position[5]);

//  pick();
//  place();

  
  calibration();
  delay(4000);
}


void loop()
{


  if(Serial.available()>0){
    char command = Serial.read();

    if(command == 'F'){
      nextNode();
    }

    if(command == 'R'){
      Serial.println("Turning Right");
      rotateRight();
    }
    if(command == 'L'){
      Serial.println("Turning left");
      rotateLeft();
    }
  }
  

}

void nextNode(){

  while(1){
    
  sensorMapping();//This function maps the sensor values to understand the robot position.
  //Serial.println(mappedValue);  
    
  if(mappedValue!=0) //when all sensors are on white line mappedValue=0. So if it is on black line...
    {
      if(digitalReading[1]==1 && digitalReading[2]==1 && digitalReading[3]==1 && digitalReading[4]==1){
        //0 1 1 1 1 0
        brake();
        Serial.println("Node reached");
        break;
      }
      else{
        //Serial.println("Following line");
        pid(); //run pid calculation in each loop
        motor(leftSpeed,rightSpeed); //run motor after planning 
        lastAct = mappedValue; //save last mappedValue
      }
        
   }

  }
}


void rotateRight(){
  plannedCRotate();
  delay(70);
  while(digitalReading[1]!=1 && digitalReading[2]!=1 && digitalReading[3]!=1 && digitalReading[4]!=1){
        //0 1 1 1 1 0
        brake();
        Serial.println("Rotated Right");
        break;
      }
}

void rotateLeft(){
  plannedACRotate();
  delay(70);
  while(digitalReading[1]!=1 && digitalReading[2]!=1 && digitalReading[3]!=1 && digitalReading[4]!=1){
        //0 1 1 1 1 0
        brake();
        Serial.println("Rotated Left");
        break;
      }
}


void sensorMapping()
{
  int sum=0,coun=0;
 
  for (int i = 0; i <sensorNum; i++) //from 0 to 5 number sensor. Where 0 --> rightmost, 5 --> leftmost
  {
    //Serial.print(analogRead(irArrayPins[i]));
    //Serial.print(",");
    if (analogRead(irArrayPins[i]) < blackLimit[i]) //assuming low IR value in black
     {
      sum += i*2; //Calculating sum of the all (sensor_number*2),  that is on top of black line
      coun++;     //Count of number of sensor on black line
  
      digitalReading[i] = 1; // 1 means on black
  
      
     }
     else digitalReading[i] = 0;
  
     Serial.print(digitalReading[i]);
     Serial.print(", ");
  }
  Serial.println("");
  if(coun!=0){
     //calculating average. ie. mappedValue.
    mappedValue = sum / coun;
    //mappedValue ranges from 0 to 10
    //5 means robot is in middle of line
  }
   else mappedValue=0;


}


void pid()
{
  
  error=targetValue-mappedValue;                  //Error is the offset from middle position
  correction=(kp*error)+(kd*(error-prevError));   //proportional correction uses only error.  differental correction calculated by taking difference of error
  prevError=error;
  motorResponse=(int)correction;


  //keeping correctd value inside max speed limit
  if(motorResponse>maxSpeed) motorResponse=maxSpeed;
  if(motorResponse<-maxSpeed) motorResponse=-maxSpeed;

  
  if(motorResponse>0)
  {
    rightSpeed=maxSpeed;
    leftSpeed=maxSpeed-motorResponse;
  }
  else 
  {
    rightSpeed=maxSpeed+ motorResponse;
    leftSpeed=maxSpeed;
  }

}



//auto calibration
void calibration()
{
  Serial.println("Calibrating.....");
  plannedCRotate();  //rotate colockwise while calibrating. It will help getting different sensor values for black and white

  
  float upSum = 0,lowSum = 0;
  int sensorArray[sensorNum][2]; //To store min and max range of each sensor

  //getting initial values
  for(int i = 0; i < sensorNum; i++)
    {
      sensorArray[i][0] = analogRead(irArrayPins[i]);
      sensorArray[i][1] = analogRead(irArrayPins[i]);
    }
 

  //int loopCounter = (int)(time * 1000 / 2.5); //Will rotate the robot for this amount of time
  long tic = millis();
  while( (millis()- tic) < time*1000 )
  {
    for(int i = 0; i < sensorNum; i++) //read all sensor
    {
      if(analogRead(irArrayPins[i])<sensorArray[i][0]) sensorArray[i][0]=analogRead(irArrayPins[i]); //store lowest values among all in one array
      if(analogRead(irArrayPins[i])>sensorArray[i][1]) sensorArray[i][1]=analogRead(irArrayPins[i]); //store highest values among all in another array
    }

  }

  Serial.println("Calibrated blacklimits:");
 for(int i=0; i < sensorNum; i++){
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
