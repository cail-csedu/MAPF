void record_run(int arr[][6], int size)
{  
  for(int i=0; i<size-1; i++){
      int s0=arr[i][0];
      int e0=arr[i+1][0];
      int s1=arr[i][1];
      int e1=arr[i+1][1];
      int s2=arr[i][2];
      int e2=arr[i+1][2];
      int s3=arr[i][3];
      int e3=arr[i+1][3];
      int s4=arr[i][4];
      int e4=arr[i+1][4];
      int s5=arr[i][5];
      int e5=arr[i+1][5];
      
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


  }
}

void pick(){
  record_run(pick_locations, 7);
}

void place(){
  record_run(place_locations, 7);
}
