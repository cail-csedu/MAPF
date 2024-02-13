//Calibrated values
int blackLimit[6] = {851,938,871,874,871,889};

//PID controller >> Proportional(P), Derivative(D), Integral(I)
int kp = 190;                     //Increrase Kp to increase sensitivity (Coarse tune)
int kd = 50 ;                     //Increrase Kd to decrease sensitivity (Fine tune)

int maxSpeed = 90;  //TO change the speed of the robot(255 can be set max)

//int storage[][6]; //{ {s1,s2,...s6}, {s1,s2,...s6}, {s1,s2,...s6},.......}
//=================Arm variables
int motor_position[6]={25,169,178,74,41,166}; //Initial Motor position
int cameraLeft = 175;
int cameraFront = 90;
int cameraRight = 0;
int currentCameraAngle = cameraFront;

int pick_locations_left[7][6] = {90,130,160,72,25,100,//home
                                140,115,130,164,68,100,//left
                                140,90,100,162,68,100,//approach
                                140,90,100,162,68,40,//grab
                                140,117,115,162,68,40,//off of pick placed
                                140,117,115,162,68,40,//left_grabbed
                                90,130,160,164,68,40//forward grabbed
           
  };
int pick_locations_right[7][6] = {90,130,170,72,25,110,//home
                                15,126,171,164,88,110,//right
                                15,78,130,162,88,110,//approach
                                15,78,130,162,88,32,//grab
                                15,117,137,162,88,32,//off of pick place
                                15,117,137,164,88,32,//right_grabbed
                                90,130,170,164,88,32//forward grabbed
           
  };
int place_locations_left[7][6] = {76,126,160,164,68,40,//home
                                140,126,160,164,68,40,//left_grabbed
                                140,70,115,72,75,40,//approach
                                140,70,115,72,75,100,//ungrab
                                140,104,146,72,75,100,//off of placing place
                                140,104,146,72,75,100,//left
                                76,126,160,72,25,100//forward grabbed
  };
int place_locations_right[7][6] = {76,126,160,164,68,32,//home
                                15,126,160,164,68,32,//right_grabbed
                                15,70,115,72,75,32,//approach
                                15,70,115,72,75,100,//ungrab
                                15,104,146,72,75,100,//off of placing place
                                15,104,146,72,75,100,//right
                                76,126,160,72,25,100//forward openned      
  };
