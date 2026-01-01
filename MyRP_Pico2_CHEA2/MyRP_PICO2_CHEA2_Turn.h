
#define CCL 0

#define CCR 1


int tct, bct, tspd;
int tctL,tctR,bctL,bctR;
int LTurnSpdL, LTurnSpdR, TurnDelayL;
int RTurnSpdL, RTurnSpdR, TurnDelayR;
int Delay_c_f;
int Delay_c_b;


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

void Delay_c_F(int de){
    Delay_c_f = de;
}

void Delay_c_B(int de){
    Delay_c_b = de;
}

void ToCenter() {
BZon();
   Motor(tctL, tctR);
    delay(20);
    ReadCalibrateF();
    while (1) {
      Motor(tctL, tctR);
      ReadCalibrateF();
      if (F[1] < Ref && F[6] < Ref) {
      delay( Delay_c_f/tct);
      Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
        break;
      }
    }
}

void ToCenterC() {
	BZon();
  Motor(tctL, tctR);
  delay(20);
  while (1) {
    Motor(tctL, tctR);
    ReadCalibrateC();
    if (C[CCL] > RefC || C[CCR] > RefC)
   // if (analogRead(46) <  (sensorMin_C[0]+md_sensorC(0))/2 || analogRead(47) < (sensorMin_C[1]+md_sensorC(1))/2)
    {
      Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
      break;
    }
  }
}

void ToCenterCB() {
	BZon();
   Motor(tctL, tctR);
    delay(20);
    ReadCalibrateC();
    while (1) {
      Motor(tctL, tctR);
      ReadCalibrateC();
     if (C[CCL] > RefC || C[CCR] > RefC)
    //  if (analogRead(26) <  (sensorMin_C[0]+md_sensorC(0))/2 || analogRead(27) < (sensorMin_C[1]+md_sensorC(1))/2)
      {
      delay(4000/tct);
      Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
       break;
      }
    }
}

void ToCenterL() {
	BZon();
   Motor(tctL, tctR);
    delay(20);
    ReadCalibrateF();
    while (1) {
      Motor(tctL, tctR);
      ReadCalibrateF();
      if (F[1] < Ref) {
        delay( Delay_c_f/tct);
        Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
        break;
      }
    }
}

void ToCenterCL() {
	BZon();
  Motor(tctL - 5, tctR - 5);
  delay(20);
  while (1) {
    Motor(tctL - 5, tctR - 5);
    ReadCalibrateC();
    if (C[CCL] > RefC )
   // if ( analogRead(26) < (sensorMin_C[0]+md_sensorC(0))/2) 
    {
      Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
      break;
    }
  }
}

void ToCenterR() {
	BZon();
   Motor(tctL, tctR);
    delay(20);
    ReadCalibrateF();
    while (1) {
      Motor(tctL, tctR);
      ReadCalibrateF();
      if (F[6] < Ref) {
        delay(Delay_c_f/tct);
        Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
        break;
      }
    }
}
void ToCenterCR() {
	BZon();
  Motor(tctL - 5, tctR - 5);
  delay(20);
  while (1) {
    Motor(tctL - 5, tctR - 5);
    ReadCalibrateC();
    if ( C[CCR] > RefC) 
    //if (analogRead(27) <  (sensorMin_C[1]+md_sensorC(1))/2 )
    {
      Motor(-tct, -tct);
      delay(5);
      MotorStop();
      BZoff();
      break;
    }
  }
}

void BackCenter() {
	BZon();
  Motor(-bctL, -bctR);
  delay(20);
  while (1) {
    Motor(-bctL, -bctR);
    ReadCalibrateB();
      if (B[1] < Ref || B[6] < Ref) {
      Motor(-bctL, -bctR);
      delay( Delay_c_b/tct);
      Motor(tct, tct);
      delay(10);
      MotorStop();
      BZoff();
      break;
    }
  }
}

void BackCenterC() {
	BZon();
  Motor(-bctL, -bctR);
  delay(20);
  while (1) {
    Motor(-bctL, -bctR);
    ReadCalibrateC();
    if (C[CCL] > RefC || C[CCR] > RefC)
    //if (analogRead(26) <  (sensorMin_C[0]+md_sensorC(0))/2 || analogRead(27) < (sensorMin_C[1]+md_sensorC(1))/2) 
  {
      Motor(tct, tct);
      delay(10);
      MotorStop();
      BZoff();
      break;
    }
  }
}


void BackToCenterCB() {
	BZon();
   Motor(-bctL, -bctR);
    delay(20);
    ReadCalibrateC();
    while (1) {
      Motor(-bctL, -bctR);
      ReadCalibrateC();
     if (C[CCL] > RefC || C[CCR] > RefC)
    //  if (analogRead(26) <  (sensorMin_C[0]+md_sensorC(0))/2 || analogRead(27) < (sensorMin_C[1]+md_sensorC(1))/2)
      {
      delay(6000/tct);
      Motor(tct, tct);
      delay(5);
      MotorStop();
      BZoff();
       break;
      }
    }
}


void TurnLeft() {
  Motor(-LTurnSpdL, LTurnSpdR);
  delay(TurnDelayL);
  while (1) {
    Motor(-LTurnSpdL, LTurnSpdR);
    ReadCalibrateF();
    if (F[2] >= Ref) {
      MotorStop();
      break;
    }
  }
}

void TurnRight() {
  Motor(RTurnSpdL, -RTurnSpdR);
  delay(TurnDelayR);
  while (1) {
    Motor(RTurnSpdL, -RTurnSpdR);
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
  Motor(-tspd, tspd);
  delay(60);
  while (F[2] >= Ref)  ReadCalibrateF();
  while (1) {
    ReadCalibrateF();
    Motor(-tspd, tspd);
    if (F[2] >= Ref) {
      Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void SpinL2() {
  MotorStop();
  delay(10);
  Motor(-tspd, tspd);
  delay(20);
  while (F[2] >= Ref)  ReadCalibrateF();
  while (1) {
    ReadCalibrateF();
    Motor(-tspd, tspd);
    if (F[2] >= Ref) {
      break;
    }
  }
  Motor(-tspd, tspd);
  delay(50);
  while (1) {
    ReadCalibrateF();
    Motor(-tspd, tspd);
    if (F[2] >= Ref) {
      Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void SpinR() {
  MotorStop();
  delay(10);
  Motor(tspd, -tspd);
  delay(60);
  while (F[5] >= Ref)  ReadCalibrateF();
  while (1) {
    ReadCalibrateF();
    Motor(tspd, -tspd);
    if (F[5] >= Ref) {
      Motor(-tspd, tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void SpinR2() {
  MotorStop();
  delay(10);
  Motor(tspd, -tspd);
  delay(20);
  while (F[5] >= Ref)  ReadCalibrateF();
  while (1) {
    ReadCalibrateF();
    Motor(tspd, -tspd);
    if (F[5] >= Ref) {
      break;
    }
  }
  Motor(tspd, -tspd);
  delay(50);
  while (1) {
    ReadCalibrateF();
    Motor(tspd, -tspd);
    if (F[5] >= Ref) {
      Motor(-tspd, tspd);
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
  Motor(-tspd, tspd);
  delay(60);
  while (B[4] >= Ref)  ReadCalibrateB();
  while (1) {
    ReadCalibrateB();
    Motor(-tspd, tspd);
    if (B[4] >= Ref) {
      Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}

void BSpinR() {
  MotorStop();
  delay(10);
  Motor(tspd, -tspd);
  delay(60);
   while (B[3] >= Ref)  ReadCalibrateB();
  while (1) {
    ReadCalibrateB();
    Motor(tspd, -tspd);
    if (B[3] >= Ref) {
      Motor(-tspd, tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}


void BSpinL2() {
  MotorStop();
  delay(10);
  Motor(-tspd, tspd);
  delay(20);
   while (B[4] >= Ref)  ReadCalibrateB();
  while (1) {
    ReadCalibrateB();
    Motor(-tspd, tspd);
    if (B[4] >= Ref) {
      break;
    }
  }
  Motor(-tspd, tspd);
  delay(50);
  while (1) {
    ReadCalibrateB();
    Motor(-tspd, tspd);
    if (B[4] >= Ref) {
      Motor(tspd, -tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}


void BSpinR2() {
  MotorStop();
  delay(10);
  Motor(tspd, -tspd);
  delay(20);
   while (B[3] >= Ref)  ReadCalibrateB();
  while (1) {
    ReadCalibrateB();
    Motor(tspd, -tspd);
    if (B[3] >= Ref) {
      break;
    }
  }
  Motor(tspd, -tspd);
  delay(50);
  while (1) {
    ReadCalibrateB();
    Motor(tspd, -tspd);
    if (B[3] >= Ref) {
      Motor(-tspd, tspd);
      delay(5);
      MotorStop();
      break;
    }
  }
}



void BTurnLeft() {
  Motor(-LTurnSpdL, LTurnSpdR);
  delay(TurnDelayL);
  while (1) {
    Motor(-LTurnSpdL, LTurnSpdR);
    ReadCalibrateB();
    if (B[5] >= Ref) {
      MotorStop();
      break;
    }
  }
}

void BTurnRight() {
  Motor(RTurnSpdL, -RTurnSpdR);
  delay(TurnDelayR);
  while (1) {
    Motor(RTurnSpdL, -RTurnSpdR);
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
  Motor(5, -tspd);
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
    Motor(5, -tspd / 2);

    // เริ่มแตะเส้นใหม่
    if (F[3] >= Ref || F[4] >= Ref) break;
  }

  /* 4️⃣ จับเส้นนิ่ม */
  while (1) {
    ReadCalibrateF();
    Motor(5, -tspd / 2);

    if (F[3] >= Ref && F[4] >= Ref) {
      Motor(5, tspd );
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
  Motor(-tspd, 5);     // ขวาถอย
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
    Motor(-tspd / 2, 5);

    // เริ่มแตะเส้นใหม่
    if (F[3] >= Ref || F[4] >= Ref) break;
  }

  /* 4️⃣ จับเส้นนิ่ม */
  while (1) {
    ReadCalibrateF();
    Motor(-tspd / 2, 5);

    if (F[3] >= Ref && F[4] >= Ref) {
      Motor(tspd, 5);
      delay(4);
      MotorStop();
      break;
    }
  }
}


void ToSensorBack(){

BZon();
     Motor(tctL, tctR);
    delay(20);
    while (1) {
       Motor(tctL, tctR);
      ReadCalibrateB();
      if ((B[0] > Ref || B[7] > Ref)) {
         Motor(-tct, -tct);
        delay(5);
        MotorShot();
        BZoff();
        break;
      }
    }

}