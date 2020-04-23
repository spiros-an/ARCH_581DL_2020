#include <Servo.h>

Servo motor;

const int MOTOR_PIN = 9; // The analog output pin where the servo is connected
const int SPEED_PIN = A0; // The analog input pin where the speed potentiometer is connected
const int RANGE_PIN = A1; // The analog input pin where the range potentiometer is connected

int MaxAngleVal; // An integer value declared by the range potentiometer
int MaxAngle; // An integer value for further use of the angle
int RotateSpeedVal; // An integer value declared by the speed potentiometer
int RotateSpeed; // An integer value for further use of the speed

int pos; // An integer value to control the servo position

boolean reversePos; // A boolean value to toggle between true and false for reversing the position of the servo

void setup()
{
  motor.attach(MOTOR_PIN); // Attach the servo to pin 9 (MOTOR_PIN)
  motor.write(0); // Initial servo position before the loop starts
  reversePos=false; // Initial state of bool reversing position
  delay(1000); // A delay berofe the loop starts
  Serial.begin(9600);
}

void loop()
{
  
  MaxAngleVal=analogRead(RANGE_PIN); // Declaring the value read from the range pin
  RotateSpeedVal=analogRead(SPEED_PIN); // Declaring the value read from the speed pin
  
  MaxAngle=map(MaxAngleVal,0,1023,1,180); // Mapping the value for the range from 1 to 180, not from 0 because it stops the servo rotation
  RotateSpeed=map(RotateSpeedVal,0,1023,5,30); // Mapping the value for the speen from 5 to 30, increasing or decreasing those mapped values, affect the speed of the motor
  
  if (RotateSpeed<28){ // if statement that stops the rotation of the servo when the delay is > 28 and contains other if statments for the rotation
    if (pos < MaxAngle && reversePos==false){ // controling the rotation from 0 to max angle value defined by the range potentiometer
      motor.write(pos); // write the position to the servo
      delay(RotateSpeed); // wait the delay set from the speed potentiometer for the servo to go reach the position
      pos += 1; // moving the servo from the previous position to  plus 1 degree 
    }
    
    if (pos==MaxAngle){ // check when the motor position reaches the max angle defined by the range potentiometer
      reversePos=true;  // toggling the bool state to true in order to reverse the rotation
    }
    
    if (reversePos==true) { // controling the rotation from the max angle value defined by the range potentiometer back to 0 
      motor.write(pos);    // write the position to the servo
      delay(RotateSpeed); // wait the delay set from the speed potentiometer for the servo to go reach the position
      pos -= 1; // moving the servo from the previous position to minus 1 degree
    }
    
    if (pos==0){ // check when the motor position reaches 0 angle 
      reversePos=false; // toggling the bool state to true in order to reverse the rotation
    }
  }

   Serial.println(pos); // serial print the position of the servo
}
