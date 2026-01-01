#define BUZZER_PIN 9
#define NUM_SENSORS 8

// #define DIST A0
int F[NUM_SENSORS], B[NUM_SENSORS], C[2];

uint8_t F_PIN[NUM_SENSORS] = { 0, 1, 2, 3, 4, 5, 6, 7 };
uint8_t B_PIN[NUM_SENSORS] = { 7, 6, 5, 4, 3, 2, 1, 0 };
uint8_t C_PIN[2] = {26, 27};

int Ref = 0;
int RefC = 0;
int RefCali = 1000;

int LineColor = 0;

int  DIST =  A0;

void TrackLineColor(int Col) {
  LineColor = Col;
}

void set_value_calibate(int set_calibate){
RefCali = set_calibate;

}
void ReadF() {
  
for (int i = 0; i < NUM_SENSORS; i++) {
  adc.begin(14, 15, 16, 13 );
  adc.begin(14, 15, 16, 17 );  //adc.begin(5, 4, 12, 20 );    // 5=clk, 4=IN, 12=out
    F[i] = adc.readADC(F_PIN[i]);
  }

}

void ReadB() {
    for (int i = 0; i < NUM_SENSORS; i++) {
   adc.begin(14, 15, 16, 17 ); 
   adc.begin(14, 15, 16, 13 );  //adc.begin(5, 4, 12, 20 );    // 5=clk, 4=IN, 12=out
    B[i] = adc.readADC(B_PIN[i]);
  }

}

void SetAnalogDistance(int x){

  DIST = x;

}
void ReadC() {
  for (int i = 0; i < 2; i++) {  
  C[i] = analogRead(C_PIN[i]); 
 }


}


void ReadCalibrateF() {
  ReadF();
  if (LineColor == 0) {
  for (int i = 0; i < NUM_SENSORS; i++) {
    int x = map(F[i], sensorMinA[i], sensorMaxA[i], RefCali, 0);
    if (x < 0) x = 0;
    if (x > RefCali) x = RefCali;
    F[i] = x;
  }
  }
  else{
      for (int i = 0; i < NUM_SENSORS; i++) {
    int x = map(F[i], sensorMinA[i], sensorMaxA[i], 0, RefCali);
    if (x < 0) x = 0;
    if (x > RefCali) x = RefCali;
    F[i] = x;
  }

  }

}

void ReadCalibrateC() {
  ReadC();
  if (LineColor == 0) {
  for (int i = 0; i < 2; i++) {
    int x = map(C[i], sensorMinC[i], sensorMaxC[i], RefCali, 0);
    if (x < 0) x = 0;
    if (x > RefCali) x = RefCali;
    C[i] = x;
  }
}
else{
for (int i = 0; i < 2; i++) {
    int x = map(C[i], sensorMinC[i], sensorMaxC[i], 0, RefCali);
    if (x < 0) x = 0;
    if (x > RefCali) x = RefCali;
    C[i] = x;
  }
}
}

void ReadCalibrateB() {
  ReadB();
  if (LineColor == 0) {
  for (int i = 0; i < NUM_SENSORS; i++) {
    int x = map(B[i], sensorMinB[i], sensorMaxB[i], RefCali, 0);
    if (x < 0) x = 0;
    if (x > RefCali ) x = RefCali;
    B[i] = x;
  }
}
else {
   for (int i = 0; i < NUM_SENSORS; i++) {
    int x = map(B[i], sensorMinB[i], sensorMaxB[i], 0, RefCali);
    if (x < 0) x = 0;
    if (x > RefCali) x = RefCali;
    B[i] = x;
  }
}
}

void ReadSensor() {
  ReadCalibrateF();
  ReadCalibrateB();
  ReadCalibrateC();
}
void ReadSensorRaw() {
  ReadF();
  ReadB();
  ReadC();
}

void RefLineValue(int x) {
  Ref = x;
}

void RefCenterLineValue(int x) {
  RefC = x;
}


void Beep(int delayb) {
   tone(BUZZER_PIN, 900, delayb);
  delay(delayb);
  noTone(BUZZER_PIN);
}

void b_beebb() {
  tone(BUZZER_PIN, 2000, 80);
  delay(100);
  tone(BUZZER_PIN, 1000, 80);
  delay(100);
  tone(BUZZER_PIN, 2000, 80);
  delay(100);
  tone(BUZZER_PIN, 2500, 150);
  delay(100);
}

void BZon(){
	tone(BUZZER_PIN,2700);	
}
void BZoff(){
	noTone(BUZZER_PIN);
}



///////////////////////////////////////////////////////////////////////////////////////

void Serial_FrontSensor() {
  while (1) {
    ReadSensorRaw();
    for (int _serialF = 0; _serialF < NUM_SENSORS; _serialF++) {
      Serial.print(F[_serialF]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(50);
  }
}

void Serial_BackSensor() {
  while (1) {
    ReadSensorRaw();
    for (int _serialB = 0; _serialB < NUM_SENSORS; _serialB++) {
      Serial.print(B[_serialB]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(50);
  }
}

void Serial_CenterSensor() {
  while (1) {
    ReadSensorRaw();
    for (int _serialA = 0; _serialA < 2; _serialA++) {
      Serial.print(C[_serialA]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(50);
  }
}

void SerialCalibrate_FrontSensor() {
  while (1) {
    ReadSensor();
    for (int _serialF = 0; _serialF < NUM_SENSORS; _serialF++) {
      Serial.print(F[_serialF]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(100);
  }
}

void SerialCalibrate_BackSensor() {
  while (1) {
    ReadSensor();
    for (int _serialB = 0; _serialB < NUM_SENSORS; _serialB++) {
      Serial.print(B[_serialB]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(100);
  }
}

void SerialCalibrate_CenterSensor() {
  while (1) {
    ReadSensor();
    for (int _serialC = 0; _serialC < 2; _serialC++) {
      Serial.print(C[_serialC]);
      Serial.print("\t");
    }
    Serial.println("");
    delay(100);
  }
}
///////////////////////////////////////////////////////////////////////////////////////
int Diss = 0;

int DistanceValue() {
  int adc = analogRead(DIST);   // อ่านค่า ADC จากเซนเซอร์

  float Vo = (float)analogRead(DIST)*3.3/4095.0;
	// float distance = 12.08 / (Vo - 0.1);   // ปรับ slope และ offset
  // Diss = (13.0/Vo) - 0.42;
  Diss = (14.5 / Vo) - 1.0;
  // จำกัดช่วงของเซนเซอร์
  if (Diss < 4)  Diss = 4;
  if (Diss > 30) Diss = 30;

  return Diss;                // ส่งค่าระยะกลับ
}
// int DistanceValue() {
//   int adc = analogRead(DIST);   // อ่านค่า ADC (0..4095 สำหรับ 12-bit)
//   // ฟิตจากข้อมูลของคุณ:
//   float A = -3.62112657;
//   float B = 25143.7837;
//   float C = 385.428104;

//   float d = A + B / ( (float)adc + C );

//   // จำกัดช่วงของเซนเซอร์
//   if (d < 4.0)  d = 4.0;
//   if (d > 30.0) d = 30.0;

//   Diss = (int)round(d);   // แปลงเป็น int (ปัด)
//   return Diss;
// }

void SerialDistance() {
  while (1) {
    Serial.print("ADC : ");
    Serial.println(analogRead(DIST));
   // Serial.print(" ");
   // Serial.println(DistanceValue());
    delay(100);
  }
}

void RGB(){


  //  if(led == 'b')
  //     {
  //       digitalWrite(rgb[0],1);
  //       digitalWrite(rgb[1],0);
  //       digitalWrite(rgb[2],0);
  //       led = 'g';
  //     }
  //   else if(led == 'g')
  //     {
  //       digitalWrite(rgb[0],0);
  //       digitalWrite(rgb[1],1);
  //       digitalWrite(rgb[2],0);
  //       led = 'r';
  //     }
  //   else if(led == 'r')
  //     {
  //       digitalWrite(rgb[0],0);
  //       digitalWrite(rgb[1],0);
  //       digitalWrite(rgb[2],1);
  //       led = 'w';
  //     }
  //   else if(led == 'w')
  //     {
  //       digitalWrite(rgb[0],1);
  //       digitalWrite(rgb[1],1);
  //       digitalWrite(rgb[2],1);
  //       led = 'b';
  //     }
}