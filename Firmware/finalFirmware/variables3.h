//int storage[][6]; //{ {s1,s2,...s6}, {s1,s2,...s6}, {s1,s2,...s6},.......}
int pick_locations_left[7][6] = {76,126,160,72,25,133,//home
                                144,137,171,72,23,133,//left
                                144,70,77,72,43,133,//approach
                                144,70,77,72,43,40,//grab
                                144,110,77,72,43,40,//off of pick placed
                                144,137,171,72,23,40,//left_grabbed
                                76,126,160,72,25,40//forward grabbed
           
  };
int pick_locations_right[7][6] = {76,126,160,72,25,133,//home
                                144,137,171,72,23,133,//right
                                144,70,77,72,43,133,//approach
                                144,70,77,72,43,40,//grab
                                144,110,77,72,43,40,//off of pick place
                                144,137,171,72,23,40,//right_grabbed
                                76,126,160,72,25,40//forward grabbed
           
  };
int place_locations_left[7][6] = {76,126,160,72,25,40,//home
                                0,137,171,72,23,40,//left_grabbed
                                0,70,77,72,43,40,//approach
                                0,70,77,72,43,133,//ungrab
                                0,110,77,72,43,133,//off of placing place
                                0,137,171,72,23,133,//left
                                76,126,160,72,25,133//forward grabbed
  };
int place_locations_right[7][6] = {76,126,160,72,25,133,//home
                                0,137,171,72,23,133,//right_grabbed
                                0,70,77,72,43,133,//approach
                                0,70,77,72,43,40,//ungrab
                                0,110,77,72,43,40,//off of placing place
                                0,137,171,72,23,40,//right
                                76,126,160,72,25,40//forward openned      
  };
