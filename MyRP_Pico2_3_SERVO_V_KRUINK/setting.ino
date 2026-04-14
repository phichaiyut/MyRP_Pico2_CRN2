void _setting() {
  /******************** IMU : BNO055 ********************/
if (!bno.begin()) {
  Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
}
delay(1000);
bno.setExtCrystalUse(true);

Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");

/******************** CALIBRATION ********************/
set_value_calibate(1000);     // ค่า Recalibrate

/******************** LINE SENSOR CONFIG ********************/
RefLineValue(400);            // ค่า threshold เซนเซอร์หน้า-หลัง
RefCenterLineValue(700);      // ค่า threshold เซนเซอร์คู่กลาง
TrackLineColor(0);            // 0 = พื้นขาวเส้นดำ | 1 = พื้นดำเส้นขาว
Dottedline(0);                // 0 = ไม่มีเส้นประ | 1 = มีเส้นประ

/******************** LINE CENTERING ********************/
// set_line_center(0);        // เดินธรรมดา เข้ากลางหุ่น
set_line_center(1);           // เดินตามเส้น เข้ากลางหุ่น
SetToCenterSpeed(20);         // ความเร็วเข้ากลางหุ่น
set_kp_kd_slow(0.010, 0.08);  // PID ช่วงช้า

/******************** TURN & SPEED CONFIG ********************/
SetTurnSpeed(40);             // ความเร็วเลี้ยวเข้าแยก


TurnSpeedLeft(25, 80, 60);    // เลี้ยวซ้าย (q Q)
TurnSpeedRight(80, 25, 60);   // เลี้ยวขวา (e E)


ModeSpdPID(0, 100, -5);       // โหมดควบคุมความเร็ว
// SetRobotPID(0.014, 0.04);  // PID หลัก (ยังไม่ใช้)

/******************** LINE POSITION ********************/
set_position_line(3500);      // 0–7000 | 1500=ซ้าย 3500=กลาง 5500=ขวา

/******************** DISTANCE SENSOR ********************/
SetAnalogDistance(A3);        // A0–A3 เซนเซอร์ตรวจจับวัตถุ

/******************** DEBUG / SERIAL MONITOR ********************/
// SerialDistance();                  // เซนเซอร์วัดระยะ
// Serial_FrontSensor();              // เซนเซอร์หน้า
// Serial_BackSensor();               // เซนเซอร์หลัง
// Serial_CenterSensor();             // เซนเซอร์กลาง
// SerialCalibrate_FrontSensor();     // ค่า Calibrate หน้า
// SerialCalibrate_BackSensor();      // ค่า Calibrate หลัง
// SerialCalibrate_CenterSensor();    // ค่า Calibrate กลาง
// SerialPositionF();                 // ตำแหน่งเส้น (หน้า)
// SerialPositionB();                 // ตำแหน่งเส้น (หลัง)
}



void RobotSetup() {
  SetBalanceSpeedForward();   //ฟังก์ชั่นตั้งค่าความสมดุลมอเตอร์ในแต่ละความเร็ว
  SetBalanceSpeedBackward();  //ฟังก์ชั่นตั้งค่าความสมดุลมอเตอร์ในแต่ละความเร็ว
  SetKpKd();                  //ฟังก์ชั่นตั้งค่า KP KD ในแต่ละความเร็ว
  SetKpKdBack();              //ฟังก์ชั่นตั้งค่า KP KD ในแต่ละความเร็ว
}

void SetKpKd() {  //เดินหน้า

  Set_KP_KD(SPD_10, 0.008, 0.16);   //ความเร็ว 10
  Set_KP_KD(SPD_20, 0.009, 0.18);   //ความเร็ว 20
  Set_KP_KD(SPD_30, 0.011, 0.28);   //ความเร็ว 30
  Set_KP_KD(SPD_40, 0.015, 0.15);   //ความเร็ว 40
  Set_KP_KD(SPD_50, 0.020, 0.36);   //ความเร็ว 50
  Set_KP_KD(SPD_60, 0.025, 0.50);   //ความเร็ว 60
  Set_KP_KD(SPD_70, 0.026, 0.52);   //ความเร็ว 70
  Set_KP_KD(SPD_80, 0.030, 0.60);   //ความเร็ว 80
  Set_KP_KD(SPD_90, 0.033, 0.66);   //ความเร็ว 90
  Set_KP_KD(SPD_100, 0.036, 0.72);  //ความเร็ว 100
}

void SetKpKdBack() {                     //ถอยหลัง
  Set_KP_KD_Back(SPD_10, 0.008, 0.16);   //ความเร็ว 10
  Set_KP_KD_Back(SPD_20, 0.009, 0.18);   //ความเร็ว 20
  Set_KP_KD_Back(SPD_30, 0.014, 0.28);   //ความเร็ว 30
  Set_KP_KD_Back(SPD_40, 0.014, 0.28);   //ความเร็ว 40
  Set_KP_KD_Back(SPD_50, 0.020, 0.38);   //ความเร็ว 50
  Set_KP_KD_Back(SPD_60, 0.020, 0.40);   //ความเร็ว 60
  Set_KP_KD_Back(SPD_70, 0.023, 0.46);   //ความเร็ว 70
  Set_KP_KD_Back(SPD_80, 0.028, 0.56);   //ความเร็ว 80
  Set_KP_KD_Back(SPD_90, 0.031, 0.62);   //ความเร็ว 90
  Set_KP_KD_Back(SPD_100, 0.033, 0.66);  //ความเร็ว 100
}



void SetBalanceSpeedForward() {  //เดินหน้า
  //ข้างไหนแรงกว่าไปข้างเพิ่มข้างนั้น
  //______________________________setBalanceSpeed(SPD_10,ข้างซ้าย, ข้างขวา);__________________________________
  setBalanceSpeed(SPD_10, 0, 0);   //ความเร็ว 10
  setBalanceSpeed(SPD_20, 0, 0);   //ความเร็ว 20
  setBalanceSpeed(SPD_30, 0, 0);   //ความเร็ว 30
  setBalanceSpeed(SPD_40, 0, 0);   //ความเร็ว 40
  setBalanceSpeed(SPD_50, 0, 0);   //ความเร็ว 50
  setBalanceSpeed(SPD_60, 0, 0);   //ความเร็ว 60
  setBalanceSpeed(SPD_70, 0, 0);   //ความเร็ว 70
  setBalanceSpeed(SPD_80, 0, 0);   //ความเร็ว 80
  setBalanceSpeed(SPD_90, 0, 0);   //ความเร็ว 90
  setBalanceSpeed(SPD_100, 0, 0);  //ความเร็ว 100
}


void SetBalanceSpeedBackward() {  //ถอยหลัง
  //ข้างไหนแรงกว่าไปข้างเพิ่มข้างนั้น
  //______________________setBalanceBackSpeed(SPD_10, ข้างซ้าย, ข้างขวา);____________________________________________
  setBalanceBackSpeed(SPD_10, 0, 0);   //ความเร็ว 10
  setBalanceBackSpeed(SPD_20, 0, 0);   //ความเร็ว 20
  setBalanceBackSpeed(SPD_30, 0, 0);   //ความเร็ว 30
  setBalanceBackSpeed(SPD_40, 0, 0);   //ความเร็ว 40
  setBalanceBackSpeed(SPD_50, 0, 0);   //ความเร็ว 50
  setBalanceBackSpeed(SPD_60, 0, 0);   //ความเร็ว 60
  setBalanceBackSpeed(SPD_70, 0, 0);   //ความเร็ว 70
  setBalanceBackSpeed(SPD_80, 0, 0);   //ความเร็ว 80
  setBalanceBackSpeed(SPD_90, 0, 0);   //ความเร็ว 90
  setBalanceBackSpeed(SPD_100, 0, 0);  //ความเร็ว 100
}

