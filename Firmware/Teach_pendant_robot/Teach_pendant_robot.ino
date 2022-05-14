#define resetPin 4
#include "HCPCA9685.h"

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address is 0x40 */
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);



int motor_position[6]={112,169,178,88,41,158};
                                                       
int storage[6][50];
int storage_loc= 0;
int last_storage_loc=0;
int Start_point=0;
int Next_point=1;
int i=0;
int Speed=50;
int Delay=50;

    unsigned int lowerBit = 0;
    unsigned int higherBit = 0;
    unsigned int realposition =0;

  int Step=0;
  int temp;

void setup()
{
  digitalWrite(resetPin,HIGH);
  pinMode(resetPin,OUTPUT);
  
  
  Serial.begin(9600);

   HCPCA9685.Init(SERVO_MODE);

  /* Wake the device up */
  HCPCA9685.Sleep(false);

  
  servo01(motor_position[0]);
  servo02(motor_position[1]);
  servo03(motor_position[2]);
  servo04(motor_position[3]);
  servo05(motor_position[4]);
  servo06(motor_position[5]);
}
void loop()
{
  //servorun();
    
  
  if (Serial.available()>= 2)
  {
      lowerBit = Serial.read();
      higherBit = Serial.read();
      realposition = (higherBit *256) + lowerBit;
        //Serial.println(realposition);


       if (realposition >= 1000 && realposition <1180) 
        {
          motor_position[0] = realposition;
          motor_position[0] = map(motor_position[0], 1000, 1180, 0, 180);
          servo01(motor_position[0]);
          /*Serial.println("Base:");
          Serial.println(motor_position[0]);*/
          delay(10);
        }
        else if (realposition >= 2000 && realposition <2180) 
        {
          motor_position[1] = realposition;
          motor_position[1] = map(motor_position[1], 2000, 2180, 0, 180);
          servo02(motor_position[1]);
          //Serial.println("Shoulder:");
          //Serial.println(motor_position[1]);
          delay(10);
        }
        else if (realposition >= 3000 && realposition <3180) 
        {
          motor_position[2] = realposition;
          motor_position[2] = map(motor_position[2], 3000, 3180, 0, 180);
          servo03(motor_position[2]);
          //Serial.println("Elbow:");
          //Serial.println(motor_position[2]);
          delay(10);
        }
        else if (realposition >= 4000 && realposition <4180) 
        {
          motor_position[3] = realposition;
          motor_position[3] = map(motor_position[3], 4000, 4180, 0, 180);
          servo04(motor_position[3]);
          //Serial.println("Wrist:");
          //Serial.println(motor_position[3]);
          delay(10);
        }
        else if (realposition >= 5000 && realposition <5180)
        {
          motor_position[4] = realposition;
          motor_position[4] = map(motor_position[4], 5000, 5180, 0, 180);
          servo05(motor_position[4]);
          //Serial.println("Wrist Roll:");
          //Serial.println(motor_position[4]);
          delay(10);
        }
        else if (realposition >= 6000 && realposition <6180) 
        {
          motor_position[5] = realposition;
          motor_position[5] = map(motor_position[5], 6000, 6180, 0, 180);
          servo06(motor_position[5]);
          //Serial.println("End Effector:");
         // Serial.println(motor_position[5]);
          delay(10);
        }


        
       else if(realposition==0)   //for save button,serial out =0                                                                             //SAVE
           {
            //Serial.println("save");
            for(i=0;i<6;i++)
              {
                storage[i][storage_loc] = motor_position[i];
                //Serial.println(storage[i][storage_loc]);
                //Serial.println(storage_loc);
          //Serial.println(motor_position[i]);
                //Serial.println("save");
              }
                last_storage_loc=storage_loc;
                storage_loc++;
          }
      else if(realposition==2)  //play er aage rest press korle reset er jonno                                                             //RESET
          {
            
            //Serial.println("reset done");
            digitalWrite(resetPin,LOW);    //reset done
            //Serial.println("never happens");
          }
      
      else if(realposition==1)      //for play button,serial out=1                                                 //PLAY
          {
            //Serial.println("PLAY");
            record_run();        
          }
    
      else if(realposition>=7681 && realposition<=7780)   //for SetSpeed button,serial out=30*256+(0to100)=7681to 7780                                              //SET SPEED
          {
            //temp=Serial.read();    //serial buffer theke 3 value remove korlam,jeno next serial out=speed pai
            Speed=realposition-(30*256);   //speed set
            Delay=map(Speed,1,100,100,(700/Delay));   //delay must be above 700ms/50step=14 karon 0 to 180 degree approx 700ms lage
            //Serial.print("SET SPEED:");
           // Serial.println(Speed);
          }
          
  }

  else
      {
        servo01(motor_position[0]);
        servo02(motor_position[1]);
        servo03(motor_position[2]);
        servo04(motor_position[3]);
        servo05(motor_position[4]);
        servo06(motor_position[5]);
      }
 
 }


void record_run()
{  

      while(true)
    {
      int s0=storage[0][Start_point];
      int e0=storage[0][Next_point];
      int s1=storage[1][Start_point];
      int e1=storage[1][Next_point];
      int s2=storage[2][Start_point];
      int e2=storage[2][Next_point];
      int s3=storage[3][Start_point];
      int e3=storage[3][Next_point];
      int s4=storage[4][Start_point];
      int e4=storage[4][Next_point];
      int s5=storage[5][Start_point];
      int e5=storage[5][Next_point];
  int a[6]={abs(s0-e0),abs(s1-e1),abs(s2-e2),abs(s3-e3),abs(s4-e4),abs(s5-e5)};
  
  int highest=a[0];
  for(int j=0;j<=5;j++)
  {
    if(a[j]>highest) highest=a[j];   
  }
  
  while(true)
  {

   servo01(map(Step,0,50,s0,e0));      //18 june 2018 dupure khabar somoy ei algo mathay ashche -_-
   servo02(map(Step,0,50,s1,e1));
   servo03(map(Step,0,50,s2,e2));       //50 step e kaj kortese
   servo04(map(Step,0,50,s3,e3));
   servo05(map(Step,0,50,s4,e4));
   servo06(map(Step,0,50,s5,e5));
            
   if(Step==50)
   {
    break;
   }
   Step++;
   delay(map(highest,0,180,0,Delay));              //700/50step=14(delay must be above14 so 50 dewa hoise...karon 0 to 180 approx 700ms lage
   //Serial.println(map(highest,0,180,0,Delay));
  }
      delay(Delay);
      Step=0;
      Start_point++;
      Next_point++;
      if(Start_point==last_storage_loc+1)
      {
        Start_point=0;
      }
      if(Next_point==last_storage_loc+1)
        {
          Next_point=0;
        }
      if (Serial.available()>= 2)
        {
       
          lowerBit = Serial.read();
          higherBit = Serial.read();
          realposition = (higherBit *256) + lowerBit;
            if(realposition==2)  //play er aage rest press korle reset er jonno                                                             //RESET
          {
            
            Serial.println("reset done");
            digitalWrite(resetPin,LOW);    //reset done
            Serial.println("never happens");
          }
            else if(realposition>=7681 && realposition<=7780)   //for SetSpeed button,serial out=30*256+(0to100)=7681to 7780                                              //SET SPEED
          {
            //temp=Serial.read();    //serial buffer theke 3 value remove korlam,jeno next serial out=speed pai
            Speed=realposition-(30*256);   //speed set
            Delay=map(Speed,1,100,100,(700/Delay));   //delay must be above 700ms/50step=14 karon 0 to 180 degree approx 700ms lage
            //Serial.print("SET SPEED:");
           // Serial.println(Speed);
          }
        }
    }
}

//////copyright @ akash
