void FD(int Speed, int Time) {
  BaseSpeed = Speed;
  InitialSpeed();
  #include <MyRP_Pico2.h>
robot.Motor(LeftBaseSpeed, RightBaseSpeed);
  delay(Time);
}
void BK(int Speed, int Time) {
  BaseSpeed = Speed;
  InitialSpeed();
  robot.Motor(-BackLeftBaseSpeed, -BackRightBaseSpeed);
  delay(Time);
}

void TL(int Speed, int Time) {
  MotorStop(0);
  robot.Motor(0, Speed);
  delay(Time);
  MotorStop(0);
}
void TR(int Speed, int Time) {
  MotorStop(0);
  robot.Motor(Speed, 0);
  delay(Time);
  MotorStop(0);
}

void SL(int Speed, int Time) {
  MotorStop(0);
  robot.Motor(-Speed, Speed);
  delay(Time);
  MotorStop(0);
}

void SR(int Speed, int Time) {
  MotorStop(0);
  robot.Motor(Speed, -Speed);
  delay(Time);
  MotorStop(0);
}

