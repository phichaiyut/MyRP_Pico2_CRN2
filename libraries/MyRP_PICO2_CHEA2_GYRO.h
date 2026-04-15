void rotate_left(int spd,int degree,int offset){

robot.rotate(-spd, spd, -abs(degree), offset); 

}

void rotate_right(int spd,int degree,int offset){

robot.rotate(spd, -spd, abs(degree), offset); 

}
void fw_gyro(int spdl, int spdr, float kp,  int distance,int offset){

robot.fw_gyro(spdl, spdr, kp,  distance, offset);   // ความเร็ว 30 30  kp1.5   ระยะ 60 เซนติเมตร ค่าเบรค 10
}

void bw_gyro(int spdl, int spdr, float kp,  int distance,int offset){

robot.bw_gyro(spdl, spdr, kp,  distance, offset);   // ความเร็ว 30 30  kp1.5   ระยะ 60 เซนติเมตร ค่าเบรค 10
}


void fw_gyro(int spd, float kp,  int distance,int offset){
BaseSpeed = spd;
InitialSpeed();
robot.fw_gyro(LeftBaseSpeed, RightBaseSpeed, kp,  distance, offset);   // ความเร็ว 30 30  kp1.5   ระยะ 60 เซนติเมตร ค่าเบรค 10
}

void bw_gyro(int spd, float kp,  int distance,int offset){
BaseSpeed = spd;
InitialSpeed();
robot.bw_gyro(BackLeftBaseSpeed, BackRightBaseSpeed, kp,  distance, offset);   // ความเร็ว 30 30  kp1.5   ระยะ 60 เซนติเมตร ค่าเบรค 10
}



void fw_gyros(int spdl, int spdr, float kp,  int distance,int offset){

robot.fw_gyros(spdl, spdr, kp,  distance, offset);   // ความเร็ว 30 30  kp1.5   ระยะ 60 เซนติเมตร ค่าเบรค 10
}

void bw_gyros(int spdl, int spdr, float kp,  int distance,int offset){

robot.bw_gyros(spdl, spdr, kp,  distance, offset);   // ความเร็ว 30 30  kp1.5   ระยะ 60 เซนติเมตร ค่าเบรค 10
}


void fw_gyros(int spd, float kp,  int distance,int offset){
BaseSpeed = spd;
InitialSpeed();
robot.fw_gyros(LeftBaseSpeed, RightBaseSpeed, kp,  distance, offset);   // ความเร็ว 30 30  kp1.5   ระยะ 60 เซนติเมตร ค่าเบรค 10
}

void bw_gyros(int spd, float kp,  int distance,int offset){
BaseSpeed = spd;
InitialSpeed();
robot.bw_gyros(BackLeftBaseSpeed, BackRightBaseSpeed, kp,  distance, offset);   // ความเร็ว 30 30  kp1.5   ระยะ 60 เซนติเมตร ค่าเบรค 10
}


void place_left_in(int spd,int degree,int offset){
robot.place_left_in(spd, degree, offset) ;  //---> หมุนซ้ายเข้า มอเตอร์ ซ้าย 0   ขวา 30 หมุนไปที่  90 องศา

}

void place_left_out(int spd, int degree, int offset){
robot.place_left_out(spd, degree, offset) ; //---> หมุนซ้ายออก มอเตอร์ ซ้าย 0   ขวา 30 หมุนไปที่  90 องศา

}

void place_right_in(int spd, int degree, int offset){
 robot.place_right_in(spd, degree, offset) ;  //---> หมุนขวาเข้า มอเตอร์ ซ้าย 0   ขวา 30 หมุนไปที่  90 องศา

}

void place_right_out(int spd, int degree, int offset)
{
robot.place_right_out(spd, degree, offset); //---> หมุนขวาออก มอเตอร์ ซ้าย 0   ขวา 30 หมุนไปที่  90 องศา

}
    
     

// #include "MyRP_PICO2_CHEA2_Motor.h"
// #include <my_BMI160.h>
// my_BMI160 my; 

// float current_degree = 0;

// void SetRobotAngle() {
//   float sum = 0;

//   for (int i = 0; i < 10; i++) {
//     sum += my.gyro('z');
//     delay(6);
//   }

//   current_degree = sum / 10.0;
// }

// void FFtimer(){

// my.resetAngles();

// float initialDegree = 0.0f;
//     for (int i = 0; i < 10; i++) {
//         initialDegree += my.gyro('z');
//         delay(6);
//         }
//     initialDegree /= 10.0f;
// }

// void spinDegree(int speed, int relative_degree) {
//   SetRobotAngle(); // เซ็ตค่าปัจจุบัน
//   int min_speed = 5;
//   int max_speed = speed;
//   float kp = 0.9;
//   float kd = 0.15;
//   float small_angle_threshold = 25;
//   float stop_threshold = 1.0;
//   float previous_error = 0;
//   float target_degree = current_degree + relative_degree;
//   if (target_degree > 180) target_degree -= 360;
//   if (target_degree < -180) target_degree += 360;
//   current_degree = target_degree;
//   while (1) {
//     float current_angle = my.gyro('z');
//     float error = target_degree - current_angle;
//     if (error > 180) error -= 360;
//     else if (error < -180) error += 360;
//     int pd_value = (kp * error) + (kd * (error - previous_error));
//     if (pd_value > max_speed) pd_value = max_speed;
//     else if (pd_value < -max_speed) pd_value = -max_speed;
//     if (error > stop_threshold && error < small_angle_threshold) {
//       robot.Motor(min_speed, -min_speed);
//     } else if (error < -stop_threshold && error > -small_angle_threshold) {
//       robot.Motor(-min_speed, min_speed);
//     } else if (error >= -stop_threshold && error <= stop_threshold) {
//       MotorStop();
//       break;
//     } else {
//       robot.Motor(pd_value, -pd_value);
//     }
//     previous_error = error;
//   }
//   Stop(60);
// }

