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

int getLargest(){
  data[0] = analogRead(Left);
  data[1] = analogRead(Center);
  data[2] = analogRead(Right);

  //bool left = false;
  //bool forward = false;
  //bool right = false;

  if(data[0] < ldrThreshold && data[1] < ldrThreshold && data[2] < ldrThreshold){
    //stopMotors();
    Serial.println("stopping...looking for light source");
    return -1;
  }
  else if(data[1] > data[0] && data[1] > data[2]){
    //forward(150,100);
    Serial.print("Highest reading - ");  
    Serial.print(data[1]);  
    Serial.println(" | going forward");
    //largeVal = data[1];
    return data[1];
    //forward = true;
  }
  else if(data[0] > data[1] && data[0] > data[2]){
    Serial.print("Highest reading - ");  
    Serial.print(data[0]);  
    //turnLeft(150,100);
    Serial.println(" | turing left");
    //largeVal = data[0];
    return data[0];
    //left = true;
  }
  else if(data[2] > data[1] && data[2] > data[0]){
    Serial.print("Highest reading - ");  
    Serial.print(data[2]);  
    //turnRight(150,100);
    Serial.println(" | turing right"); 
    //largeVal = data[2];
    return data[2];
    //right = true;
  }
  //return largeVal;
}

void driveToBrightness(){
  int highVal = getLargest();
  if(highVal == -1){
    robot.go(0,0);
  }
  else if (highVal == data[1]){
    robot.go(150,100);
  }
  else if(highVal == data[0]){
    robot.go(-150,100);
  }
  else if(highVal == data[2]){
    robot.go(150,-100);
  }
  else{
    robot.go(0,0);
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
