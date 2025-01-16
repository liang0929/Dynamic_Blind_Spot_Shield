#include <Arduino.h>
#include <Servo.h>

Servo myservo;  // 建立SERVO物件


void setup() {
  myservo.attach(9);  // 設定要將伺服馬達接到哪一個PIN腳
}

void loop() {   
  myservo.write(0);  //旋轉到22度，就是下歸零
  delay(1000);
  myservo.write(360); //旋轉到70度
  delay(1000000);
  
}