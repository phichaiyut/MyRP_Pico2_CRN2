void fw_gyro(int Speed, float kp,  char select) 
{     
    BaseSpeed = Speed;
    InitialSpeed();
    int target_speed = min(LeftBaseSpeed, RightBaseSpeed); 
    float traveled_distance = 0;
    unsigned long last_time = millis();
    
    float speed_scale = 1.5;  // <-- ใช้ค่าที่คำนวณจากการวัดจริง

    resetAngles();
    float yaw_offset = my.gyro('z'); 
    float _integral = 0;
    float _prevErr = 0;
    unsigned long prevT = millis();   

    int maxLeftSpeed = LeftBaseSpeed;
    int maxRightSpeed = RightBaseSpeed; 

    while (1) 
    {
        unsigned long now = millis();
        float dt = (now - prevT) / 1000.0;
        if (dt <= 0) dt = 0.001; 
        prevT = now;

        float yaw = my.gyro('z') - yaw_offset;
        float err = yaw;

        _integral += err * dt;
        float deriv = (err - _prevErr) / dt;
        _prevErr = err;
        float corr = kp * err + 0.0001 * _integral + 0.05 * deriv;

        int leftSpeed  = constrain(LeftBaseSpeed - corr, -100, 100);
        int rightSpeed = constrain(RightBaseSpeed + corr, -100, 100);
        Motor(leftSpeed, rightSpeed);
        ReadCalibrateF();
            if (F[0] > Ref || F[1] > Ref || F[2] > Ref || F[3] > Ref || F[4] > Ref || F[5] > Ref || F[6] > Ref || F[7] > Ref) {
      break;
    }

        delayMicroseconds(50);
    }

    TrackSelectF(Speed, select);
    
}

// ===========================
// ฟังก์ชันวิ่งถอยหลัง ใช้ Gyro + PID
// ===========================
void bw_gyro(int Speed, float kp,  char select) 
 {     
     BaseSpeed = Speed;
    InitialSpeed();
    int target_speed = min(BackLeftBaseSpeed, BackRightBaseSpeed); 
    float traveled_distance = 0;
    unsigned long last_time = millis();
    
    float speed_scale = 1.6;  // ใช้ค่าที่คาลิเบรตจาก fw()

    resetAngles();
    float yaw_offset = my.gyro('z'); 
    float _integral = 0;
    float _prevErr = 0;
    unsigned long prevT = millis();   

    int maxLeftSpeed = BackLeftBaseSpeed;
    int maxRightSpeed = BackRightBaseSpeed; 

    while (1) 
    {
        unsigned long now = millis();
        float dt = (now - prevT) / 1000.0;
        if (dt <= 0) dt = 0.001; 
        prevT = now;

        float yaw = my.gyro('z') - yaw_offset;
        float err = -yaw;

        _integral += err * dt;
        float deriv = (err - _prevErr) / dt;
        _prevErr = err;
        float corr = kp * err + 0.0001 * _integral + 0.05 * deriv;

        // สปีดถอยหลัง
        int leftSpeed  = constrain(-(BackLeftBaseSpeed - corr), -100, 100);
        int rightSpeed = constrain(-(BackRightBaseSpeed + corr), -100, 100);
        Motor(leftSpeed, rightSpeed);

       ReadCalibrateB();
    if (B[0] > Ref || B[1] > Ref || B[2] > Ref || B[3] > Ref || B[4] > Ref || B[5] > Ref || B[6] > Ref || B[7] > Ref) {
      break;
    }

        delayMicroseconds(50);
    }

    TrackSelectB(Speed, select);
  }



  void fw_gyro(int Speed, float kp,  float distance, int offset) 
{     
  BaseSpeed = Speed;
    InitialSpeed();
    int target_speed = min(LeftBaseSpeed, RightBaseSpeed); 
    float traveled_distance = 0;
    unsigned long last_time = millis();
    
    float speed_scale = 1.5;  // <-- ใช้ค่าที่คำนวณจากการวัดจริง

    resetAngles();
    float yaw_offset = my.gyro('z'); 
    float _integral = 0;
    float _prevErr = 0;
    unsigned long prevT = millis();   

    int maxLeftSpeed = LeftBaseSpeed;
    int maxRightSpeed = RightBaseSpeed; 

    while (1) 
    {
        unsigned long now = millis();
        float dt = (now - prevT) / 1000.0;
        if (dt <= 0) dt = 0.001; 
        prevT = now;

        float yaw = my.gyro('z') - yaw_offset;
        float err = yaw;

        _integral += err * dt;
        float deriv = (err - _prevErr) / dt;
        _prevErr = err;
        float corr = kp * err + 0.0001 * _integral + 0.05 * deriv;

        int leftSpeed  = constrain(LeftBaseSpeed - corr, -100, 100);
        int rightSpeed = constrain(RightBaseSpeed + corr, -100, 100);
        Motor(leftSpeed, rightSpeed);

        if (distance > 0) 
        {
            unsigned long current_time = millis();
            float delta_time = (current_time - last_time) / 1000.0;
            traveled_distance += (target_speed * speed_scale) * delta_time;
            last_time = current_time;

            if (traveled_distance >= distance) break;
        }

        delayMicroseconds(50);
    }

    // soft stop
    if(offset >0)
      {
        Motor(-15, -15); delay(offset);
        Motor(-1, -1);   delay(10);
        Motor(0, 0);     delay(10);
      }
    else{Motor(0, 0);delay(5);}
    
}

// ===========================
// ฟังก์ชันวิ่งถอยหลัง ใช้ Gyro + PID
// ===========================
void bw_gyro(int Speed, float kp,  float distance, int offset) 
 {     
    BaseSpeed = Speed;
    InitialSpeed();
    int target_speed = min(BackLeftBaseSpeed, BackRightBaseSpeed); 
    float traveled_distance = 0;
    unsigned long last_time = millis();
    
    float speed_scale = 1.6;  // ใช้ค่าที่คาลิเบรตจาก fw()

    resetAngles();
    float yaw_offset = my.gyro('z'); 
    float _integral = 0;
    float _prevErr = 0;
    unsigned long prevT = millis();   

    int maxLeftSpeed = BackLeftBaseSpeed;
    int maxRightSpeed = BackRightBaseSpeed; 

    while (1) 
    {
        unsigned long now = millis();
        float dt = (now - prevT) / 1000.0;
        if (dt <= 0) dt = 0.001; 
        prevT = now;

        float yaw = my.gyro('z') - yaw_offset;
        float err = -yaw;

        _integral += err * dt;
        float deriv = (err - _prevErr) / dt;
        _prevErr = err;
        float corr = kp * err + 0.0001 * _integral + 0.05 * deriv;

        // สปีดถอยหลัง
        int leftSpeed  = constrain(-(BackLeftBaseSpeed - corr), -100, 100);
        int rightSpeed = constrain(-(BackRightBaseSpeed + corr), -100, 100);
        Motor(leftSpeed, rightSpeed);

        if (distance > 0) 
        {
            unsigned long current_time = millis();
            float delta_time = (current_time - last_time) / 1000.0;
            traveled_distance += (target_speed * speed_scale) * delta_time;
            last_time = current_time;

            if (traveled_distance >= distance) break;
        }

        delayMicroseconds(50);
    }

    if(offset >0)
      {
        Motor(-15, -15); delay(offset);
        Motor(-1, -1);   delay(10);
        Motor(0, 0);     delay(10);
      }
    else{Motor(0, 0);delay(5);}
  }

  void Spin_left_gyro(int speed, int degree, int offset) 
  {
      resetAngles();
        // คำนวณค่ามุมเริ่มต้น
        float initialDegree = 0;
        for (int i = 0; i < 5; i++) {
            initialDegree += my.gyro('z');  // ใช้ค่าที่อ่านได้จากเซ็นเซอร์
            delay(10);
        }
        initialDegree /= 5.0;
    
        // คำนวณมุมเป้าหมาย
        float targetDegree = initialDegree + (-degree);
    
        // กำหนดค่าของ PID
        
        float lr_kp  = 2.05;  // ปรับค่า Kp เพื่อให้การหมุนเร็วขึ้น
        float lr_ki  = 0.00001;  // ค่า Ki ปรับตามความแม่นยำในการหยุด
        float lr_kd = 0.015; // ปรับค่า Kd เพื่อให้การหยุดมีความแม่นยำขึ้น
        
        float error = 0, previous_error = 0;
        float integral = 0, output = 0;
        float currentDegree = 0;
    
        unsigned long lastTime = millis();
        unsigned long timeout = 500;  // กำหนดเวลา timeout
        unsigned long startTime = millis();
    
        while (true) {
            currentDegree = my.gyro('z');  // อ่านค่ามุมปัจจุบัน
            error = targetDegree - currentDegree;  // คำนวณความผิดพลาด
    
            // ตรวจสอบเงื่อนไขการหยุดเมื่อใกล้ถึงมุมที่ต้องการ
            if (abs(error) < 1 && abs(output) < 5) break;
    
            unsigned long now = millis();
            float dt = (now - lastTime) / 1000.0;
            lastTime = now;
    
            if (dt > 0) {
                integral += error * dt;
                float derivative = (error - previous_error) / dt;
                previous_error = error;
    
                output = lr_kp * error + lr_ki * integral + lr_kd * derivative;
            }
    
            // จำกัดค่าของ output ให้อยู่ในช่วงความเร็วที่ต้องการ
            output = constrain(output, -speed, speed);
    
            // ควบคุมมอเตอร์ให้หมุนตาม PID ที่คำนวณ
            if(degree > 0)
              {
                Motor(output, -output);  
                delay(5);
              }
              else
              {
                
                 Motor(output, -(output));  
                delay(5);
              }
    
            // ตรวจจับ timeout หากใช้เวลานานเกินไป
            if (millis() - startTime > timeout) {
                break;  // ออกจาก loop หากเวลาผ่านไปนานเกินไป
            }
        }
    
        // หยุดมอเตอร์หลังจากหมุนเสร็จ
        if(degree>0)
          {
            
            Motor(output, -output);
            delay(offset);
          }
        else
          {
            Motor(output, -(output)); 
            delay(offset);
          }
        Motor(-1, -1);
        delay(10);
  }

void Spin_right_gyro(int speed, int degree, int offset) 
  {
      resetAngles();
        // คำนวณค่ามุมเริ่มต้น
        float initialDegree = 0;
        for (int i = 0; i < 5; i++) {
            initialDegree += my.gyro('z');  // ใช้ค่าที่อ่านได้จากเซ็นเซอร์
            delay(10);
        }
        initialDegree /= 5.0;
    
        // คำนวณมุมเป้าหมาย
        float targetDegree = initialDegree + degree;
    
        // กำหนดค่าของ PID
        
        float lr_kp  = 2.05;  // ปรับค่า Kp เพื่อให้การหมุนเร็วขึ้น
        float lr_ki  = 0.00001;  // ค่า Ki ปรับตามความแม่นยำในการหยุด
        float lr_kd = 0.015; // ปรับค่า Kd เพื่อให้การหยุดมีความแม่นยำขึ้น
        
        float error = 0, previous_error = 0;
        float integral = 0, output = 0;
        float currentDegree = 0;
    
        unsigned long lastTime = millis();
        unsigned long timeout = 500;  // กำหนดเวลา timeout
        unsigned long startTime = millis();
    
        while (true) {
            currentDegree = my.gyro('z');  // อ่านค่ามุมปัจจุบัน
            error = targetDegree - currentDegree;  // คำนวณความผิดพลาด
    
            // ตรวจสอบเงื่อนไขการหยุดเมื่อใกล้ถึงมุมที่ต้องการ
            if (abs(error) < 1 && abs(output) < 5) break;
    
            unsigned long now = millis();
            float dt = (now - lastTime) / 1000.0;
            lastTime = now;
    
            if (dt > 0) {
                integral += error * dt;
                float derivative = (error - previous_error) / dt;
                previous_error = error;
    
                output = lr_kp * error + lr_ki * integral + lr_kd * derivative;
            }
    
            // จำกัดค่าของ output ให้อยู่ในช่วงความเร็วที่ต้องการ
            output = constrain(output, -speed, speed);
    
            // ควบคุมมอเตอร์ให้หมุนตาม PID ที่คำนวณ
            if(degree > 0)
              {
                Motor(output, -(output));  
                delay(5);
              }
              else
              {
                Motor(output, -output);  
                delay(5);
              }
    
            // ตรวจจับ timeout หากใช้เวลานานเกินไป
            if (millis() - startTime > timeout) {
                break;  // ออกจาก loop หากเวลาผ่านไปนานเกินไป
            }
        }
    
        // หยุดมอเตอร์หลังจากหมุนเสร็จ
        if(degree>0)
          {
            Motor(output, -(output)); 
            delay(offset);
          }
        else
          {
            Motor(output, -output);
            delay(offset);
          }
        Motor(-1, -1);
        delay(10);
  }




  void Turn_left_gyro(int speed, int degree, int offset) 
{
  resetAngles();
  float initialDegree = 0;
  for (int i = 0; i < 5; i++) {
    initialDegree += my.gyro('z');
    delay(10);
  }
  initialDegree /= 5.0;

  float targetDegree = initialDegree - degree;

  // PID parameters
  float lr_kp  = 2.05;
  float lr_ki  = 0.00001;
  float lr_kd = 0.015;

  float error = 0, previous_error = 0;
  float integral = 0, output = 0;
  float currentDegree = 0;

  unsigned long lastTime = millis();
  unsigned long timeout = 2000;  // เพิ่มเวลาเพราะหมุนล้อเดียวช้ากว่า
  unsigned long startTime = millis();

  while (true) {
    currentDegree = my.gyro('z');
    error = targetDegree - currentDegree;

    if (abs(error) < 1 && abs(output) < 5) break;

    unsigned long now = millis();
    float dt = (now - lastTime) / 1000.0;
    lastTime = now;

    if (dt > 0) {
      integral += error * dt;
      float derivative = (error - previous_error) / dt;
      previous_error = error;
      output = lr_kp * error + lr_ki * integral + lr_kd * derivative;
    }

    output = constrain(output, -speed, speed);

    // หมุนล้อเดียว (ล้อขวาหมุน ล้อซ้ายหยุด)
    Motor(0, output);
    delay(5);

    if (millis() - startTime > timeout) {
      break;
    }
  }

  // หลังหมุนเสร็จ ทำ offset เล็กน้อย
  Motor(0, output);
  delay(offset);
  Motor(0, 0);
}

void Turn_right_gyro(int speed, int degree, int offset) 
{
  resetAngles();
  float initialDegree = 0;
  for (int i = 0; i < 5; i++) {
    initialDegree += my.gyro('z');
    delay(10);
  }
  initialDegree /= 5.0;

  float targetDegree = initialDegree + degree;

  float lr_kp  = 2.05;
  float lr_ki  = 0.00001;
  float lr_kd = 0.015;

  float error = 0, previous_error = 0;
  float integral = 0, output = 0;
  float currentDegree = 0;

  unsigned long lastTime = millis();
  unsigned long timeout = 2000;
  unsigned long startTime = millis();

  while (true) {
    currentDegree = my.gyro('z');
    error = targetDegree - currentDegree;

    if (abs(error) < 1 && abs(output) < 5) break;

    unsigned long now = millis();
    float dt = (now - lastTime) / 1000.0;
    lastTime = now;

    if (dt > 0) {
      integral += error * dt;
      float derivative = (error - previous_error) / dt;
      previous_error = error;
      output = lr_kp * error + lr_ki * integral + lr_kd * derivative;
    }

    output = constrain(output, -speed, speed);

    // หมุนล้อเดียว (ล้อซ้ายหมุน ล้อขวาหยุด)
    Motor(output, 0);
    delay(5);

    if (millis() - startTime > timeout) {
      break;
    }
  }

  Motor(output, 0);
  delay(offset);
  Motor(0, 0);
}


void fw_gyro_dist(int Speed, float kp,  char select,int dist) 
{     
    BaseSpeed = Speed;
    InitialSpeed();
    int target_speed = min(LeftBaseSpeed, RightBaseSpeed); 
    float traveled_distance = 0;
    unsigned long last_time = millis();
    
    float speed_scale = 1.5;  // <-- ใช้ค่าที่คำนวณจากการวัดจริง

    resetAngles();
    float yaw_offset = my.gyro('z'); 
    float _integral = 0;
    float _prevErr = 0;
    unsigned long prevT = millis();   

    int maxLeftSpeed = LeftBaseSpeed;
    int maxRightSpeed = RightBaseSpeed; 

    while (1) 
    {
        unsigned long now = millis();
        float dt = (now - prevT) / 1000.0;
        if (dt <= 0) dt = 0.001; 
        prevT = now;

        float yaw = my.gyro('z') - yaw_offset;
        float err = yaw;

        _integral += err * dt;
        float deriv = (err - _prevErr) / dt;
        _prevErr = err;
        float corr = kp * err + 0.0001 * _integral + 0.05 * deriv;

        int leftSpeed  = constrain(LeftBaseSpeed - corr, -100, 100);
        int rightSpeed = constrain(RightBaseSpeed + corr, -100, 100);
        Motor(leftSpeed, rightSpeed);
      if (analogRead(DIST) >  dist) {
      break;
    }

        delayMicroseconds(50);
    }

    TrackSelectF(Speed, select);
    
}

// ===========================
// ฟังก์ชันวิ่งถอยหลัง ใช้ Gyro + PID
// ===========================
void bw_gyro_dist(int Speed, float kp,  char select,int dist) 
 {     
     BaseSpeed = Speed;
    InitialSpeed();
    int target_speed = min(BackLeftBaseSpeed, BackRightBaseSpeed); 
    float traveled_distance = 0;
    unsigned long last_time = millis();
    
    float speed_scale = 1.6;  // ใช้ค่าที่คาลิเบรตจาก fw()

    resetAngles();
    float yaw_offset = my.gyro('z'); 
    float _integral = 0;
    float _prevErr = 0;
    unsigned long prevT = millis();   

    int maxLeftSpeed = BackLeftBaseSpeed;
    int maxRightSpeed = BackRightBaseSpeed; 

    while (1) 
    {
        unsigned long now = millis();
        float dt = (now - prevT) / 1000.0;
        if (dt <= 0) dt = 0.001; 
        prevT = now;

        float yaw = my.gyro('z') - yaw_offset;
        float err = -yaw;

        _integral += err * dt;
        float deriv = (err - _prevErr) / dt;
        _prevErr = err;
        float corr = kp * err + 0.0001 * _integral + 0.05 * deriv;

        // สปีดถอยหลัง
        int leftSpeed  = constrain(-(BackLeftBaseSpeed - corr), -100, 100);
        int rightSpeed = constrain(-(BackRightBaseSpeed + corr), -100, 100);
        Motor(leftSpeed, rightSpeed);

    if (analogRead(DIST) <  dist) {
      break;
    }

        delayMicroseconds(50);
    }

    TrackSelectB(Speed, select);
  }

