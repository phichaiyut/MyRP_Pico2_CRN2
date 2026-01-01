#include <MyRP_PICO2_CHEA2_Sensor.h> 
#include <MyRP_PICO2_CHEA2_Motor.h> 
#include <MyRP_PICO2_CHEA2_Initial.h> 
#include <MyRP_PICO2_CHEA2_ForwardBackwardAndTurn.h> 
#include <MyRP_PICO2_CHEA2_Turn.h> 
#include <MyRP_PICO2_CHEA2_PID.h> 
#include <MyRP_PICO2_CHEA2_GYRO.h> 


// int pos1 = 90, pos2 = 90, pos3 = 90;





void OK(){

  sw();
}


void OK_STOP(){
MotorStop(0);
  sw();
}

void moveServo(int servoID, int targetAngle) {
  if (targetAngle < 0 || targetAngle > 180) {
    Serial.println("Error: มุมต้องอยู่ระหว่าง 0 - 180");
    return;
  }

  switch (servoID) {
    case 1: servo(1,targetAngle); Serial.print("Servo1 = "); break;
    case 2: servo(10,targetAngle); Serial.print("Servo2 = "); break;
    case 3: servo(0,targetAngle); Serial.print("Servo3 = "); break;
    default: Serial.println("Error: ไม่มี Servo หมายเลขนี้ (ใช้ 1, 2, 3)"); return;
  }
  Serial.println(targetAngle);
}

// ฟังก์ชันอ่านคำสั่งจาก Serial
void readSerialCommand() {
  while (1) {
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n');
      input.trim();

      // ถ้าอยากออกจาก loop
      if (input.equalsIgnoreCase("EXIT")) {
        Serial.println("ออกจากโหมดควบคุม Serial แล้ว");
        break; // ออกจาก while loop
      }
      input.toUpperCase();
      if (input.startsWith("S1")) {
        int angle = input.substring(2).toInt();
        moveServo(1, angle);
      }
      else if (input.startsWith("S2")) {
        int angle = input.substring(2).toInt();
        moveServo(2, angle);
      }
      else if (input.startsWith("S3")) {
        int angle = input.substring(2).toInt();
        moveServo(3, angle);
      }
      else {
        Serial.println("❌ รูปแบบไม่ถูกต้อง! ใช้ S1/S2/S3 ตามด้วยมุม เช่น S1 90");
      }
    }
  }
}
