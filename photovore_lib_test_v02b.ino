#include <Motor_TB.h>

Motor_TB robot(9,8,7,3,5,4,11,10,2);

//LDRs
int Left = A1;
int Center = A2;
int Right = A3;

int data[3];
int ldrThreshold = 750;
int largeVal;



void setup() {
  // put your setup code here, to run once:
  pinMode(Left, INPUT);
  pinMode(Center, INPUT);
  pinMode(Right, INPUT);
  
  Serial.begin(9600);
}

void getReadings(){
  data[0] = analogRead(Left);
  data[1] = analogRead(Center);
  data[2] = analogRead(Right);

  Serial.print("Left = ");
  Serial.print(data[0]);
  Serial.print(" | Center = ");
  Serial.print(data[1]);
  Serial.print(" | Right = ");
  Serial.println(data[2]);

}

void getLargest(){
  data[0] = analogRead(Left);
  data[1] = analogRead(Center);
  data[2] = analogRead(Right);

  if(data[0] < ldrThreshold && data[1] < ldrThreshold && data[2] < ldrThreshold){
    //stopMotors();
    Serial.println("stopping...looking for light source");
    return true;
  }
  else if(data[1] > data[0] && data[1] > data[2]){
    //forward(150,100);
    Serial.print("Highest reading - ");  
    Serial.print(data[1]);  
    Serial.println(" | going forard");
    largeVal = data[1];
  }
  else if(data[0] > data[1] && data[0] > data[2]){
    Serial.print("Highest reading - ");  
    Serial.print(data[0]);  
    //turnLeft(150,100);
    Serial.println(" | turing left");
    largeVal = data[0];
  }
  else if(data[2] > data[1] && data[2] >data[0]){
    Serial.print("Highest reading - ");  
    Serial.print(data[2]);  
    //turnRight(150,100);
    Serial.println(" | turing right"); 
    largeVal = data[2];
  }
  return largeVal;
}

void driveToBrightness(){
  if(true){
    robot.go(0,0);
  }
  else if (largeVal == data[1]){
    robot.go(150,100);
  }
  else if(largeVal == data[0]){
    robot.go(-150,100);
  }
  else if(largeVal == data[2]){
    robot.go(150,-100);
  }
}

/*
void drive2Brite(){
  int range = map(largeVal,data[0],data[1],data[2]);

  switch (range) {
    case 0:
      if(true){
        robot.go(0,0);
      }
      break;
    case 1:
      if (largeVal == data[1]){
        robot.go(150,100);
      }
      break;
    case 2:
      if(largeVal == data[0]){
        robot.go(-150,100);
      }
      break;
    case 3:
      if(largeVal == data[2]){
        robot.go(150,-100);
      }
      break;
  }
}
*/

void loop() {
  // put your main code here, to run repeatedly:
  driveToBrightness();
  //delay(1000);
}
