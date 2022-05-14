//motorPins
const int backleft1 = 3,backleft2 = 4;       //backleft motor
const int backright1 = 5,backright2= 6;       //backright motor
const int frontleft1 = 8,frontleft2= 9;       //frontleft motor
const int frontright1 = 10,frontright2 = 11;       //frontright motor

int max=150, min=10;

void setup() {
  // put your setup code here, to run once:
 //initializing motorPins
  pinMode(backleft1, OUTPUT);
  pinMode(backleft2, OUTPUT);
  pinMode(backright1, OUTPUT);
  pinMode(backright2, OUTPUT);
  
  pinMode(frontleft1, OUTPUT);
  pinMode(frontleft2, OUTPUT);
  pinMode(frontright1, OUTPUT);
  pinMode(frontright2, OUTPUT);
}

void loop() {

//goForward(100);
//delay(4000);
//brake();
//delay(1000);

goBackward(90);
delay(4000);
brake();
delay(1000);


//goRight(255);
//goBackward(255);
//goLeft(255);
//rotate(255);
//brake(10000);

}

//motor functions
//motor functions

void goForward(int beshi)
{
  analogWrite(backleft1, 0);
  analogWrite(backleft2 , beshi);
  analogWrite(backright1, beshi);
  analogWrite(backright2, 0);


  analogWrite(frontleft1, beshi);
  analogWrite(frontleft2 , 0);
  analogWrite(frontright1, 0);
  analogWrite(frontright2, beshi);
}

void goBackward(int beshi)
{
  analogWrite(backleft1, beshi);
  analogWrite(backleft2 , 0);
  analogWrite(backright1, 0);
  analogWrite(backright2,beshi);

  analogWrite(frontleft1, 0);
  analogWrite(frontleft2 , beshi);
  analogWrite(frontright1, beshi);
  analogWrite(frontright2,0);
}

void goLeft(int beshi)
{
  analogWrite(backleft1, beshi);
  analogWrite(backleft2, 0);
  analogWrite(backright1, 0);
  analogWrite(backright2, 0);

}

void goRight(int beshi,int kom)
{
  analogWrite(backleft1, 0);
  analogWrite(backleft2, kom);
  analogWrite(backright1, beshi);
  analogWrite(backright2, 0);

}

void brake()
{
  analogWrite(backleft1, 0);
  analogWrite(backleft2, 0);
  analogWrite(backright1, 0);
  analogWrite(backright2, 0);

  analogWrite(frontleft1, 0);
  analogWrite(frontleft2 , 0);
  analogWrite(frontright1, 0);
  analogWrite(frontright2, 0);

}


void rotate(int beshi)
{
  analogWrite(backleft1,beshi);
  analogWrite(backleft2, 0);
  analogWrite(backright1, 0);
  analogWrite(backright2, beshi);

}
