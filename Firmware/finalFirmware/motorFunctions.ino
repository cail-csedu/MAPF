void testMotorMS() { /* function testMotorMS */
 //// Test DC motor
 Serial.println(F("-------------------------------------"));
 Serial.println(F("Forward "));
 forward(100);
 delay(500);
 Serial.println(F("Backward "));
 backward(100);
 delay(500);
 Serial.println(F("Stop "));
 brake();
 delay(1000);
}

void motor(int left, int right)//left, right value ranges from (-maxSpeed, maxSpeed)
{
  
  if(right>0)
  {
  analogWrite(motorPin1,right);
  analogWrite(motorPin2,0);
  }
  else
  {
    analogWrite(motorPin1,0);
    analogWrite(motorPin2,-right);
  }

  if(left>0)
  {
  analogWrite(motorPin3,left);
  analogWrite(motorPin4,0);
  }
  else
  {
   analogWrite(motorPin3,0);
   analogWrite(motorPin4,-left); 
  }

 }

void forward(int pwm) { /* function dcForward */
  analogWrite(motorPin1, pwm);//right
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, pwm);//left
  analogWrite(motorPin4, 0);
}
void backward(int pwm) { /* function dcBackward */
  analogWrite(motorPin1, 0);//right
  analogWrite(motorPin2, pwm);
  analogWrite(motorPin3, 0);//left
  analogWrite(motorPin4, pwm);
}

void brake()
{
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4, 0);
}

void turnLeft(int Delay)
{
  analogWrite(motorPin1,rotationSpeed);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4,rotationSpeed);

  delay(Delay);
  brake();
}

void turnRight(int Delay)
{
  analogWrite(motorPin1,0);
  analogWrite(motorPin2, rotationSpeed);
  analogWrite(motorPin3, rotationSpeed-15);
  analogWrite(motorPin4,0);

  delay(Delay);
  brake();
}

void plannedACRotate()
{
  analogWrite(motorPin1,rotationSpeed);
  analogWrite(motorPin2, 0);
  analogWrite(motorPin3, 0);
  analogWrite(motorPin4,rotationSpeed);

}

void plannedCRotate()
{
  analogWrite(motorPin1,0);
  analogWrite(motorPin2, rotationSpeed);
  analogWrite(motorPin3, rotationSpeed-15);
  analogWrite(motorPin4,0);

}
