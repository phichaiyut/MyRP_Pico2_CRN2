void FD(int Speed, int Time) {
  BaseSpeed = Speed;
  InitialSpeed();
  Motor(LeftBaseSpeed, RightBaseSpeed);
  delay(Time);
}
void BK(int Speed, int Time) {
  BaseSpeed = Speed;
  InitialSpeed();
  Motor(-BackLeftBaseSpeed, -BackRightBaseSpeed);
  delay(Time);
}

void TL(int Speed, int Time) {
  MotorStop(0);
  Motor(0, Speed);
  delay(Time);
  MotorStop(0);
}
void TR(int Speed, int Time) {
  MotorStop(0);
  Motor(Speed, 0);
  delay(Time);
  MotorStop(0);
}

void SL(int Speed, int Time) {
  MotorStop(0);
  Motor(-Speed, Speed);
  delay(Time);
  MotorStop(0);
}

void SR(int Speed, int Time) {
  MotorStop(0);
  Motor(Speed, -Speed);
  delay(Time);
  MotorStop(0);
}

