#include <Arduino.h>
#include <Unistep2.h>

// 初始化步進馬達：指定引腳和參數
Unistep2 stepper(2, 3, 4, 5, 4096, 900);
int lastSignal;
void setup() {
  Serial.begin(9600); // 初始化串列通訊
  stepper.move(0); // 初始化位置
}

void loop() {
  if (digitalRead(6) != lastSignal) {
    if (digitalRead(6) == HIGH) {
      stepper.move(8192); // 設定目標位置，順時針旋轉一圈
      Serial.println(666);
    } else if (digitalRead(6) == LOW) {
      stepper.move(-4096); // 設定目標位置，逆時針旋轉一圈
      Serial.println(888);
    }
  }
  lastSignal = digitalRead(6);
  // 執行步進馬達運動
  stepper.run();
}