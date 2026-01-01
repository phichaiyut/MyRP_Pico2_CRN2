
void  Move(int l,int r,int time){
Motor(l,r);
delay(time);


}

void MotorShot() {
  digitalWrite(AIN1, 1);
  digitalWrite(AIN2, 1);
  analogWrite(PWMA, 255);
  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 1);
  analogWrite(PWMB, 255);
}
void MotorShot(int time) {
  digitalWrite(AIN1, 1);
  digitalWrite(AIN2, 1);
  analogWrite(PWMA, 255);
  digitalWrite(BIN1, 1);
  digitalWrite(BIN2, 1);
  analogWrite(PWMB, 255);
  delay(time);
}

void MotorStop() {
  analogWrite(PWMA, 0);  
  analogWrite(PWMB, 0);
  delay(5);
}


void MotorStop(int t) {
  analogWrite(PWMA, 0);  
  analogWrite(PWMB, 0);
  delay(t);
}


void TestMotor(){
	Move(60, 0, 500);
	Move(0, 60, 500);
	MotorStop(100);
}
