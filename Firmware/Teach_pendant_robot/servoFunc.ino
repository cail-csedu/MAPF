void servo01(int pos){
  int mappedVal = map(pos, 0,180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(0, mappedVal);
}
void servo02(int pos){
  int mappedVal = map(pos, 0,180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(2, mappedVal);
}
void servo03(int pos){
  int mappedVal = map(pos, 0,180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(4, mappedVal);
}
void servo04(int pos){
  int mappedVal = map(pos, 0,180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(6, mappedVal);
}
void servo05(int pos){
  int mappedVal = map(pos, 0,180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(8, mappedVal);
}
void servo06(int pos){
  int mappedVal = map(pos, 0,180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(10, mappedVal);
}
