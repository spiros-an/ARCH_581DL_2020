#include <Servo.h>

Servo motor; // Create the servo object

const int MOTOR_PIN = 9; // The analog output pin where the servo is connected
const int SPEED_PIN = A0; // The analog input pin where the speed potentiometer is connected
const int RANGE_PIN = A1; // The analog input pin where the range potentiometer is connected

int motorSpeed; // An integer value to control the servo speed
int motorRange; // An integer value to control the servo range
int motorPos; // An integer value to control the servo position


void setup() {
  
  motor.attach(MOTOR_PIN); // Attach the servo to pin 9 (MOTOR_PIN)
  motor.write(0); // Initial servo position before the loop starts
  delay(1000); // A delay berofe the loop starts
  Serial.begin(1000000); // Increased the bit per second communication because serial print/plotter was delaying the performance
  while(!Serial); // wait until the serial is ready
  Serial.println("Pos, Speed, Range"); // Labelling for the serial plotter, if using serial monitor and not plotter this has to be disabled

}

void loop() {

  // Using the for loop statement to repeat the position and rotate the servo from 0 to the max range set by the RANGE_PIN
  for (motorPos = 0; motorPos <= motorRange; motorPos +=1) { // for motor position 0 until the motor position <= the predefined range add a step of 1 degree
  motorRange = map(analogRead(RANGE_PIN), 0, 1023, 0, 180); // this declares the value set by the range potentiometer and map the values from 0 to 180 degrees
  motorSpeed = map(analogRead(SPEED_PIN), 0, 1023, 4, 40); // this declares the value set by the speed potentiometer and map the delay values from 3 to 40, increasing or decreasing those mapped values, affect the speed of the motor
  while(map(analogRead(SPEED_PIN), 0, 1023, 4, 40)  > 35); // the while loop let the for loop executing until the (delay) value is > 35, where it pauses the loop and stops the motor. When the value is < 35 it continues the for loop from where it has paused 
  motor.write(motorPos); // write the position to the servo
  delay(motorSpeed); // wait the delay set from the speed potentiometer for the servo to go reach the position

  
  //Serial.print("Pos: "); // enable this if you use serial monitor and keep it disable when using serial plotter
  Serial.print(motorPos);
  Serial.print(" , ");
  //Serial.print("(+) Sp: "); // enable this if you use serial monitor and keep it disable when using serial plotter
  Serial.print(motorSpeed);  
  Serial.print(" , ");
  //Serial.print(" / Ra: "); // enable this if you use serial monitor and keep it disable when using serial plotter
  Serial.println(motorRange);  
  }
  

  // Using the for loop statement to repeat the position and rotate the servo from the max range set by the RANGE_PIN back to 0
  for (motorPos = motorRange; motorPos >= 0; motorPos -=1) {  // for motor position at the given range potition until the motor position >= 0  add a step of 1 degree  
  motorRange = map(analogRead(RANGE_PIN), 0, 1023, 0, 180); // this declares the value set by the range potentiometer and map the values from 0 to 180 degrees
  motorSpeed = map(analogRead(SPEED_PIN), 0, 1023, 4, 40); // this declares the value set by the speed potentiometer and map the delay values from 3 to 40, increasing or decreasing those mapped values, affect the speed of the motor
  while(map(analogRead(SPEED_PIN), 0, 1023, 4, 40)  > 35); // the while loop let the for loop executing until the (delay) value is > 35, where it pauses the loop and stops the motor. When the value is < 35 it continues the for loop from where it has paused
  motor.write(motorPos); // write the position to the servo
  delay(motorSpeed); // wait the delay set from the speed potentiometer for the servo to go reach the position

  //Serial.print("Pos: "); // enable this if you use serial monitor and keep it disable when using serial plotter
  Serial.print(motorPos);
  Serial.print(" , ");
  //Serial.print("(-) Sp: "); // enable this if you use serial monitor and keep it disable when using serial plotter
  Serial.print(motorSpeed);  
  Serial.print(" , ");
  //Serial.print(" / Ra: "); // enable this if you use serial monitor and keep it disable when using serial plotter
  Serial.println(motorRange);  
  }
}
  
