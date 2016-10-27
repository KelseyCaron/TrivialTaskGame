/* Read Jostick
Kelsey Caron
debugging ELEGOO joyStick
October 20, 2016
Purpose: to debug and learn about the ELEGOO JoyStick

  */

 //int ledPin = 13;
 int joyPinX = A0;                // X-axis When JoyStick is pugged into bread board
 int joyPinY = A1;                // Y-axis When JoyStick is pugged into bread board
 int joyPush = A2;                // Push application for joyStick
 int value1 = 0;                  // variable to read the value from the analog pin 0
 int value2 = 0;                  // variable to read the value from the analog pin 1
 int value3 = 0;                  // variable to read the value from the analog pin 2
 void setup() {
  Serial.begin(9600);
 }


 void loop() {
  // reads the value of the variable resistor 
  value1 = analogRead(joyPinX); // BASE:513
  value2 = analogRead(joyPinY);   // BASE:515
  value3 = analogRead(joyPush); // BASE: 533- 387

  ////////////////////////////////////////////////////////
  //Print Reading from JoyStick for X, Y, and Push.
  //Serial.print("x axis: ");
  //Serial.println(value1);
  //Serial.print("y-axis: ");
  //Serial.println(value2);
  //Serial.print("push: ");
  //Serial.println(value3);
  //delay(1000);
  ////////////////////////////////////////////////////////           

  ////////////////////////////////////////////////////////
  //JoyStick at work, printing out LEFT,RIGHT,UP,DOWN,PUSH
  if(value1 > 1000){
    Serial.println("RIGHT");
    }
  else if(value1 < 200){
    Serial.println("LEFT");
    }
  else if(value2 < 200){
    Serial.println("DOWN");
    }
    else if(value2 > 1000){
    Serial.println("UP");
    }
    else if(value3 == 0){
     Serial.println("PUSH");
     }

//////////////////////////////////////////////////////////
    
      

 }
