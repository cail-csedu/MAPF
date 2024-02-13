void servo01(int pos) {
  int mappedVal = map(pos, 0, 180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(0, mappedVal);
}
void servo02(int pos) {
  int mappedVal = map(pos, 0, 180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(2, mappedVal);
}
void servo03(int pos) {
  int mappedVal = map(pos, 0, 180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(4, mappedVal);
}
void servo04(int pos) {
  int mappedVal = map(pos, 0, 180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(6, mappedVal);
}
void servo05(int pos) {
  int mappedVal = map(pos, 0, 180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(8, mappedVal);
}
void servo06(int pos) {
  int mappedVal = map(pos, 0, 180, 10, 450); //it takes 10-450 value
  HCPCA9685.Servo(10, mappedVal);
}


//Camera holder servo
void servo07(int pos) {
  int diff = pos - currentCameraAngle;

  if (diff >= 0) {
    for (int i = currentCameraAngle; i <= pos; i++) {
      int mappedVal = map(i, 0, 180, 10, 450); //it takes 10-450 value
      HCPCA9685.Servo(12, mappedVal);
      delay(5);
    }
  }
  else{
    for (int i = currentCameraAngle; i >= pos; i--) {
      int mappedVal = map(i, 0, 180, 10, 450); //it takes 10-450 value
      HCPCA9685.Servo(12, mappedVal);
      delay(5);
    }
  }
  currentCameraAngle = pos;
  
}
void lookLeft() {
  servo07(cameraLeft);
  delay(2000);
}
void lookForward() {
  servo07(cameraFront);
  delay(2000);
}
void lookRight() {
  servo07(cameraRight);
  delay(2000);
}
