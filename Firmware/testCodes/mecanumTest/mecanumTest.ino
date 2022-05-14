//motorPins
const int left1 = 9,left2 = 5;       //left motor
const int right1 = 10,right2 = 11;       //right motor

int max=150, min=10;

void setup() {
  // put your setup code here, to run once:
 //initializing motorPins
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  

  goForward(100);
  delay(500);
  brake();
  delay(1000);
  
  goBackward(80);
  delay(500);
  brake();
  delay(500);
  
}

void loop() {

//goForward(100);
//delay(500);
//brake();
//delay(1000);
//
//goBackward(100);
//delay(500);
//brake();
//delay(500);


//goRight(255);
//goBackward(255);
//goLeft(255);
//rotate(255);
//brake(10000);

}

//motor functions
//motor functions

void goForward(int speed)
{
  analogWrite(left1, speed);
  analogWrite(left2, 0);
  analogWrite(right1, speed);
  analogWrite(right2, 0);

}

void goBackward(int speed)
{
  analogWrite(left1, 0);
  analogWrite(left2, speed);
  analogWrite(right1, 0);
  analogWrite(right2, speed);
}

void goLeft(int speed)
{
  analogWrite(left1, 0);
  analogWrite(left2, speed);
  analogWrite(right1, speed);
  analogWrite(right2, 0);

}

void goRight(int speed)
{
  analogWrite(left1, speed);
  analogWrite(left2, 0);
  analogWrite(right1, 0);
  analogWrite(right2, speed);

}

void brake()
{
  analogWrite(left1, 0);
  analogWrite(left2, 0);
  analogWrite(right1, 0);
  analogWrite(right2, 0);

}
