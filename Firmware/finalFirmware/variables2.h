//Calibrated values
int blackLimit[6] = {874,930,970,969,940,861};

//PID controller >> Proportional(P), Derivative(D), Integral(I)
int kp = 180;                     //Increrase Kp to increase sensitivity (Coarse tune)
int kd = 70 ;                     //Increrase Kd to decrease sensitivity (Fine tune)

int maxSpeed = 90;  //TO change the speed of the robot(255 can be set max)

//int storage[][6]; //{ {s1,s2,...s6}, {s1,s2,...s6}, {s1,s2,...s6},.......}
//=================Arm variables
int motor_position[6]={25,169,178,74,41,166}; //Initial Motor position
int cameraLeft = 175;
int cameraFront = 90;
int cameraRight = 0;
int currentCameraAngle = cameraFront;

int pick_locations_left[7][6] = {76,126,160,72,25,100,//home
                                140,103,122,164,68,100,//left
                                140,85,100,162,68,100,//approach
                                140,85,100,162,68,40,//grab
                                140,117,115,162,68,40,//off of pick placed
                                140,117,115,162,68,40,//left_grabbed
                                76,126,160,164,68,40//forward grabbed
           
  };
int pick_locations_right[7][6] = {76,126,160,72,25,95,//home
                                0,103,122,164,68,95,//right
                                0,80,105,162,68,95,//approach
                                0,80,105,162,68,40,//grab
                                0,117,115,162,68,40,//off of pick place
                                0,117,115,164,68,40,//right_grabbed
                                76,126,160,164,68,40//forward grabbed
           
  };
int place_locations_left[7][6] = {76,126,160,164,68,40,//home
                                140,126,160,164,68,40,//left_grabbed
                                140,70,115,72,75,40,//approach
                                140,70,115,72,75,100,//ungrab
                                140,104,146,72,75,100,//off of placing place
                                140,104,146,72,75,100,//left
                                76,126,160,72,25,100//forward grabbed
  };
int place_locations_right[7][6] = {76,126,160,164,68,40,//home
                                0,126,160,164,68,40,//right_grabbed
                                0,70,115,72,75,40,//approach
                                0,70,115,72,75,100,//ungrab
                                0,104,146,72,75,100,//off of placing place
                                0,104,146,72,75,100,//right
                                76,126,160,72,25,100//forward openned      
  };
