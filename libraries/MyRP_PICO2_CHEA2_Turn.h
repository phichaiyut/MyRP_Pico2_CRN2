
#define CCL 1

#define CCR 0


int tct, bct, tspd;
int tctL,tctR,bctL,bctR;
int LTurnSpdL, LTurnSpdR, TurnDelayL;
int RTurnSpdL, RTurnSpdR, TurnDelayR;
int LastError_F1, LastError_B1;
int line_centor = 0;
float kp_slow1 = 0.007 , kd_slow1 = 0.07;
void BZon();
void BZoff();
void InitialSpeed();

void SetRobotPID(float Kp, float Kd) {
  PID_KP = Kp;
  PID_KD = Kd;
}


void SetToCenterSpeed(int tctv) {
	
  tct = tctv;
  bct = tctv;
	BaseSpeed = tctv;
	InitialSpeed();
	tctL = LeftBaseSpeed;
	tctR = RightBaseSpeed;
	bctL = BackLeftBaseSpeed;
	bctR = BackRightBaseSpeed;
}

void SetTurnSpeed(int tspdv) {
  tspd = tspdv;
}

void TurnSpeedLeft(int l, int r, int de) {
  LTurnSpdL = l;
  LTurnSpdR = r;
  TurnDelayL = de;
}

void TurnSpeedRight(int l, int r, int de) {
  RTurnSpdL = l;
  RTurnSpdR = r;
  TurnDelayR = de;
}



void set_line_center(int x){
  line_centor = x;


}
void set_kp_kd_slow(float kp, float kd){
  kp_slow1 = kp;
  kd_slow1 = kd;
}

int readPositionF_none(int Track, int noise) {
  unsigned char i, online = 0;
  unsigned long avg = 0;
  unsigned int sum = 0;
  static int last_value = (NUM_SENSORS - 1) * 1000 / 2;
  ReadCalibrateF();
  for (i = 0; i < NUM_SENSORS; i++) {
    int values = F[i];
    if (values > Track) {
      online = 1;
    }
    if (values > noise) {
      avg += (long)(values) * (i * 1000);
      sum += values;
    }
  }
  if (!online) {
     
    if (last_value < (NUM_SENSORS - 1) * 1000 / 2)
    // if (last_value < set_position)
    {
      return 3500;
    } else {
      return 3500;
    }
  }
  last_value = avg / sum;
  return last_value;
}

int readPositionB_none(int Track, int noise) {
  unsigned char i, online = 0;
  unsigned long avg = 0;
  unsigned int sum = 0;
  static int last_value = (NUM_SENSORS - 1) * 1000 / 2;
  ReadCalibrateB();
  for (i = 0; i < NUM_SENSORS; i++) {
    int values = B[i];
    if (values > Track) {
      online = 1;
    }
    if (values > noise) {
      avg += (long)(values) * (i * 1000);
      sum += values;
    }
  }
  if (!online) {
     
    if (last_value < (NUM_SENSORS - 1) * 1000 / 2)
    // if (last_value < set_position)
     {
      return 3500;
    } else {
      return 3500;
    }
  }
  last_value = avg / sum;
  return last_value;
}


void PIDF_none(int SpeedL, int SpeedR, float Kp, float Kd) {
   int Pos;
   ReadCalibrateF();
  if (F[3] > Ref && F[4] > Ref) {
    Pos = 3500;
  } else {
    Pos = readPositionF_none(250, 50);
  }
  // int Pos = readPositionF_none(250, 50);
  int Error = Pos - (NUM_SENSORS - 1) * 1000 / 2;
  // if(abs(Error) < 1000) Error = 0;
  
  int PID_Value = (Kp * Error) + (Kd * (Error - LastError_F1));
  LastError_F1 = Error;

  int LeftPower  = SpeedL  + PID_Value;
  int RightPower = SpeedR - PID_Value;

  if (LeftPower > 100) LeftPower = 100;
  if (LeftPower < -100) LeftPower = -100;
  if (RightPower > 100) RightPower = 100;
  if (RightPower < -100) RightPower = -100;

  robot.Motor(LeftPower, RightPower);
      
}

void PIDB_none(int SpeedL, int SpeedR, float Kp, float Kd) {
  int Pos;
   ReadCalibrateB();
   if (B[3] > Ref && B[4] > Ref) {
  Pos = 3500;
}
else if (B[4] > Ref && B[5] > Ref){
  Pos = 4500;   // เผื่อเส้นเฉียง
}
else if (B[2] > Ref && B[3] > Ref) {
  Pos = 2500;
}
else {
    Pos = readPositionB_none(250, 50);
  }
  // int Pos = readPositionB_none(250, 50);
  int Error = Pos - (NUM_SENSORS - 1) * 1000 / 2;
  int PID_Value = (Kp * Error) + (Kd * (Error - LastError_B1));
  LastError_B1 = Error;

  int LeftPower  = SpeedL  + PID_Value;
  int RightPower = SpeedR - PID_Value;

  if (LeftPower > 100) LeftPower = 100;
  if (LeftPower < -100) LeftPower = -100;
  if (RightPower > 100) RightPower = 100;
  if (RightPower < -100) RightPower = -100;

  robot.Motor(-LeftPower, -RightPower); // วิ่งย้อน (กลับทิศกับ PIDF)
    
}

void ToCenterC() {
	BZon();
  if(line_centor == 0){
      robot.Motor(tctL, tctR);
      delay(20);
    }
    else{
      for( int i = 0; i <= 20; i++){
        PIDF_none(tctL,tctR,kp_slow1,kd_slow1);
      }  
    }
  // robot.Motor(tctL, tctR);
  // delay(20);
  while (1) {
    // robot.Motor(tctL, tctR);
    if(line_centor == 0){
      robot.Motor(tctL, tctR);
    }
    else{
      PIDF_none(tctL,tctR,kp_slow1,kd_slow1);
    }
   
    ReadCalibrateC();
    if (C[CCL] > RefC || C[CCR] > RefC)
   // if (analogRead(46) <  (sensorMin_C[0]+md_sensorC(0))/2 || analogRead(47) < (sensorMin_C[1]+md_sensorC(1))/2)
    {
      robot.Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
      break;
    }
  }
}



void ToCenterCL() {
	BZon();
   if(line_centor == 0){
      robot.Motor(tctL, tctR);
      delay(20);
    }
    else{
      for( int i = 0; i <= 20; i++){
        PIDF_none(tctL,tctR,kp_slow1,kd_slow1);
      } 
    }
  // robot.Motor(tctL - 5, tctR - 5);
  // delay(20);
  while (1) {
    if(line_centor == 0){
      robot.Motor(tctL - 5, tctR - 5);
    }
    else{
      PIDF_none(tctL,tctR,kp_slow1,kd_slow1);
    }
    ReadCalibrateC();
    if (C[CCL] > RefC )
   // if ( analogRead(26) < (sensorMin_C[0]+md_sensorC(0))/2) 
    {
      robot.Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
      break;
    }
  }
}


void ToCenterCR() {
	BZon();
  // robot.Motor(tctL - 5, tctR - 5);
  // delay(20);
   if(line_centor == 0){
      robot.Motor(tctL, tctR);
      delay(20);
    }
    else{
      for( int i = 0; i <= 20; i++){
        PIDF_none(tctL,tctR,kp_slow1,kd_slow1);
      } 
    }
  while (1) {
    if(line_centor == 0){
      robot.Motor(tctL - 5, tctR - 5);
    }
    else{
      PIDF_none(tctL,tctR,kp_slow1,kd_slow1);
    }
    ReadCalibrateC();
    if ( C[CCR] > RefC) 
    //if (analogRead(27) <  (sensorMin_C[1]+md_sensorC(1))/2 )
    {
      robot.Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
      break;
    }
  }
}



void BackCenterC() {
	BZon();
   if(line_centor == 0){
      robot.Motor(-bctL, -bctR);
      delay(20);
    }
    else{
      for( int i = 0; i <= 20; i++){
        PIDB_none(bctL,bctR,kp_slow1,kd_slow1);
      } 
    }
  
  while (1) {
    if(line_centor == 0){
      robot.Motor(-bctL, -bctR);
    }
    else{
      PIDB_none(bctL,bctR,kp_slow1,kd_slow1);
    }
    //Motor(-bctL, -bctR);
    ReadCalibrateC();
    if (C[CCL] > RefC || C[CCR] > RefC)
    //if (analogRead(26) <  (sensorMin_C[0]+md_sensorC(0))/2 || analogRead(27) < (sensorMin_C[1]+md_sensorC(1))/2) 
  {
      robot.Motor(bctL, bctR);
      delay(10);
      MotorStop();
      BZoff();
      break;
    }
  }
}



void TurnLeft() {
  robot.Motor(-LTurnSpdL, LTurnSpdR);
  delay(TurnDelayL);
  while (1) {
    robot.Motor(-LTurnSpdL, LTurnSpdR);
    ReadCalibrateF();
    if (F[2] >= Ref) {
      MotorStop();
      break;
    }
  }
}

void TurnRight() {
  robot.Motor(RTurnSpdL, -RTurnSpdR);
  delay(TurnDelayR);
  while (1) {
    robot.Motor(RTurnSpdL, -RTurnSpdR);
    ReadCalibrateF();
    if (F[5] >= Ref) {
      MotorStop();
      break;
    }
  }
}

void SpinL() {
  MotorStop();
  delay(10);
  robot.Motor(-tspd, tspd);
  delay(60);
  while (F[2] >= Ref)  ReadCalibrateF();
  while (1) {
    ReadCalibrateF();
    robot.Motor(-tspd, tspd);
    if (F[2] >= Ref) {
      robot.Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void SpinL2() {
  MotorStop();
  delay(10);
  robot.Motor(-tspd, tspd);
  delay(20);
  while (F[2] >= Ref)  ReadCalibrateF();
  while (1) {
    ReadCalibrateF();
    robot.Motor(-tspd, tspd);
    if (F[2] >= Ref) {
      break;
    }
  }
  robot.Motor(-tspd, tspd);
  delay(50);
  while (1) {
    ReadCalibrateF();
    robot.Motor(-tspd, tspd);
    if (F[2] >= Ref) {
      robot.Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void SpinR() {
  MotorStop();
  delay(10);
  robot.Motor(tspd, -tspd);
  delay(60);
  while (F[5] >= Ref)  ReadCalibrateF();
  while (1) {
    ReadCalibrateF();
    robot.Motor(tspd, -tspd);
    if (F[5] >= Ref) {
      robot.Motor(-tspd, tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void SpinR2() {
  MotorStop();
  delay(10);
  robot.Motor(tspd, -tspd);
  delay(20);
  while (F[5] >= Ref)  ReadCalibrateF();
  while (1) {
    ReadCalibrateF();
    robot.Motor(tspd, -tspd);
    if (F[5] >= Ref) {
      break;
    }
  }
  robot.Motor(tspd, -tspd);
  delay(50);
  while (1) {
    ReadCalibrateF();
    robot.Motor(tspd, -tspd);
    if (F[5] >= Ref) {
      robot.Motor(-tspd, tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

//เลี้ยวแบบใช้เซนเซอร์หลัง

void BSpinL() {
  MotorStop();
  delay(10);
  robot.Motor(-tspd, tspd);
  delay(60);
  while (B[4] >= Ref)  ReadCalibrateB();
  while (1) {
    ReadCalibrateB();
    robot.Motor(-tspd, tspd);
    if (B[4] >= Ref) {
      robot.Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void BSpinR() {
  MotorStop();
  delay(10);
  robot.Motor(tspd, -tspd);
  delay(60);
   while (B[2] >= Ref)  ReadCalibrateB();
  while (1) {
    ReadCalibrateB();
    robot.Motor(tspd, -tspd);
    if (B[2] >= Ref) {
      robot.Motor(-tspd, tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}


void BSpinL2() {
  MotorStop();
  delay(10);
  robot.Motor(-tspd, tspd);
  delay(20);
   while (B[2] >= Ref)  ReadCalibrateB();
  while (1) {
    ReadCalibrateB();
    robot.Motor(-tspd, tspd);
    if (B[2] >= Ref) {
      break;
    }
  }
  robot.Motor(-tspd, tspd);
  delay(50);
  while (1) {
    ReadCalibrateB();
    robot.Motor(-tspd, tspd);
    if (B[2] >= Ref) {
      robot.Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}


void BSpinR2() {
  MotorStop();
  delay(10);
  robot.Motor(tspd, -tspd);
  delay(20);
   while (B[5] >= Ref)  ReadCalibrateB();
  while (1) {
    ReadCalibrateB();
    robot.Motor(tspd, -tspd);
    if (B[5] >= Ref) {
      break;
    }
  }
  robot.Motor(tspd, -tspd);
  delay(50);
  while (1) {
    ReadCalibrateB();
    robot.Motor(tspd, -tspd);
    if (B[5] >= Ref) {
      robot.Motor(-tspd, tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}



void BTurnLeft() {
  robot.Motor(-LTurnSpdL, LTurnSpdR);
  delay(TurnDelayL);
  while (1) {
    robot.Motor(-LTurnSpdL, LTurnSpdR);
    ReadCalibrateB();
    if (B[5] >= Ref) {
      MotorStop();
      break;
    }
  }
}

void BTurnRight() {
  robot.Motor(RTurnSpdL, -RTurnSpdR);
  delay(TurnDelayR);
  while (1) {
    robot.Motor(RTurnSpdL, -RTurnSpdR);
    ReadCalibrateB();
    if (B[2] >= Ref) {
      MotorStop();
      break;
    }
  }
}



void Back_TurnL() {
  MotorStop();
  delay(5);

  /* 1️⃣ สะบัดแรง */
  robot.Motor(5, -tspd);
  delay(35);

  /* 2️⃣ รอจนเส้นพ้นกลาง + ซ้าย */
  while (1) {
    ReadCalibrateF();

    // เซนเซอร์กลางและซ้ายหลุดเส้น
    if (F[3] < Ref && F[2] < Ref) break;
  }

  /* 3️⃣ หมุนช้าหาเส้นใหม่ */
  while (1) {
    ReadCalibrateF();
    robot.Motor(5, -tspd / 2);

    // เริ่มแตะเส้นใหม่
    if (F[3] >= Ref || F[4] >= Ref) break;
  }

  /* 4️⃣ จับเส้นนิ่ม */
  while (1) {
    ReadCalibrateF();
    robot.Motor(5, -tspd / 2);

    if (F[3] >= Ref && F[4] >= Ref) {
      robot.Motor(5, tspd );
      delay(4);
      MotorStop();
      break;
    }
  }
}


void Back_TurnR() {
  MotorStop();
  delay(5);

  /* 1️⃣ สะบัดแรง */
  robot.Motor(-tspd, 5);     // ขวาถอย
  delay(35);

  /* 2️⃣ รอจนเส้นพ้นกลาง + ขวา */
  while (1) {
    ReadCalibrateF();

    // เซนเซอร์กลางและขวาหลุดเส้น
    if (F[2] < Ref && F[3] < Ref) break;
  }

  /* 3️⃣ หมุนช้าหาเส้นใหม่ */
  while (1) {
    ReadCalibrateF();
    robot.Motor(-tspd / 2, 5);

    // เริ่มแตะเส้นใหม่
    if (F[3] >= Ref || F[4] >= Ref) break;
  }

  /* 4️⃣ จับเส้นนิ่ม */
  while (1) {
    ReadCalibrateF();
    robot.Motor(-tspd / 2, 5);

    if (F[3] >= Ref && F[4] >= Ref) {
      robot.Motor(tspd, 5);
      delay(4);
      MotorStop();
      break;
    }
  }
}


void ToSensorBack(){

BZon();
     robot.Motor(tctL, tctR);
    delay(20);
    while (1) {
       robot.Motor(tctL, tctR);
      ReadCalibrateB();
      if ((B[0] > Ref || B[7] > Ref)) {
         robot.Motor(-tct, -tct);
        delay(5);
        MotorShot();
        BZoff();
        break;
      }
    }

}


// ---------- Balance ----------

void BalanceF(int Counter) {
  Move(-10, -10, 50);
  for (int i = 0; i <= Counter; i++) {
    Move(-10, -10, 80);
    while (1) {
      robot.Motor(10, 10);
      ReadCalibrateF();
      if (F[0] > Ref) {
        while (1) {
          robot.Motor(0, 5);
          ReadCalibrateF();
          if (F[7] > Ref) { MotorStop(); break; }
        }
      }
      if (F[7] > Ref) {
        while (1) {
          robot.Motor(5, 0);
          ReadCalibrateF();
          if (F[0] > Ref) { MotorStop(); break; }
        }
      }
      if (F[0] > Ref && F[7] > Ref) { MotorStop(); break; }
    }
    MotorStop();
    delay(50);
  }
}

void BalanceB(int Counter) {
  Move(10, 10, 50);
  for (int i = 0; i <= Counter; i++) {
    Move(10, 10, 80);
    while (1) {
      robot.Motor(-12, -12);
      ReadCalibrateB();
      if (B[0] > Ref) {
        while (1) {
          robot.Motor(0, -5);
          ReadCalibrateB(); 
          if (B[7] > Ref) { MotorStop(); break; }
        }
      }
      if (B[7] > Ref) {
        while (1) {
          robot.Motor(-5, 0);
          ReadCalibrateB();
          if (B[0] > Ref) { MotorStop(); break; }
        }
      }
      if (B[0] > Ref && B[7] > Ref) { MotorStop(); break; }
    }
    MotorStop();
    delay(50);
  }
}
