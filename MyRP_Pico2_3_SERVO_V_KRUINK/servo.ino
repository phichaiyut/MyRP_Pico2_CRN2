#define sv1 1                        //ตัวขึ้นลง
#define sv2 10                       // ตัวซ้าย
#define sv3 0                        //ตัวขวา
int readyL = 65, readyR = 70;        // ฟังก์ชันองศาของ arm_ready()  //--------->> แขนลง กางฝ่ามือออกเตรียมเข้าไปคีบ
int behindL = 40, behindR = 45;      //ฟังก์ชันองศาของ arm_behind()  //--------->> แขนลง เอาฝ่ามือมาข้างหลัง
int up = 95;                         //ยกแขนขึ้น
int closeL = 91, closeR = 91;        //หุบลูกเล็ก close
int closeBigL = 75, closeBigR = 85;  //หุบลูกใหญ่ big_box

int up45 = 40;

void armupdown(int x) {

  robot.servo(1, x);
  pos1 = x;
}

void arm_left_right(int l, int r) {
  robot.servo(10, l);
  robot.servo(0, r);
  pos2 = l;
  pos3 = r;
}

// -------------------- ฟังก์ชันหลัก --------------------
void Servo(int target1, int target2, int target3, int spd) {

  MotorStop();
  while (pos1 != target1 || pos2 != target2 || pos3 != target3) {
    if (pos1 < target1) pos1++;
    else if (pos1 > target1) pos1--;

    if (pos2 < target2) pos2++;
    else if (pos2 > target2) pos2--;

    if (pos3 < target3) pos3++;
    else if (pos3 > target3) pos3--;

    robot.servo(sv1, pos1);
    robot.servo(sv2, pos2);
    robot.servo(sv3, pos3);

    delay(spd);  // หน่วงเวลา
  }
  pos1 = target1;
  pos2 = target2;
  pos3 = target3;
  delay(200);
}

void Servo(int x, int y, int z) {
  MotorStop();
  robot.servo(sv1, x);
  robot.servo(sv2, y);
  robot.servo(sv3, z);
  pos1 = x;
  pos2 = y;
  pos3 = z;
  delay(200);
}

void armupdown(int x, int spd) {
  Servo(x, pos2, pos3, spd);
}

void arm_left_right(int l, int r, int spd) {
  Servo(pos1, l, r, spd);
}


void arm_ready()  //--------->> แขนลง กางฝ่ามือออกเตรียมเข้าไปคีบ
{
  MotorStop();
  armupdown(servo_down);
  arm_left_right(servoL_open - readyL, servoR_open - readyR);
  delay(200);
  // robot.servo(1, servo_down);
  // robot.servo(10, servoL_open - 30);
  // robot.servo(0, servoR_open - 30);
}

void arm_open_down()  //--------->>  กางฝ่ามือออก  และเอาแขนลง
{
  MotorStop();
  arm_left_right(servoL_open, servoR_open);
  delay(200);
  armupdown(servo_down);
  delay(100);
  // robot.servo(10, servoL_open);
  // robot.servo(0, servoR_open);
  // delay(300);
  // robot.servo(1, servo_down);
}
void arm_down_open()  //--------->>  เอาแขนลง  และ กางฝ่ามือออก
{
  MotorStop();
  armupdown(servo_down);
  delay(100);
  arm_left_right(servoL_open, servoR_open);
  delay(200);
  // robot.servo(1, servo_down);
  // delay(300);
  // robot.servo(10, servoL_open);
  // robot.servo(0, servoR_open);
}
void arm_open_up()  //--------->>  กางฝ่ามือออก  และยกแขนขึ้น
{
  MotorStop();
  arm_left_right(servoL_open, servoR_open);
  delay(200);
  armupdown(servo_down + up);
  delay(100);

  // robot.servo(10, servoL_open);
  // robot.servo(0, servoR_open);
  // delay(300);
  // robot.servo(1, servo_down + 95);
}
void arm_up_open()  //--------->>  เอาแขนขึ้น  และ กางฝ่ามือออก
{
  MotorStop();
  arm_left_right(servoL_open, servoR_open);
  delay(200);
  armupdown(servo_down + up);
  delay(100);
  // robot.servo(1, servo_down + 95);
  // delay(300);
  // robot.servo(10, servoL_open);
  // robot.servo(0, servoR_open);
}
void arm_down_close()  //--------->>  เอาแขนลง  และ หุบมือเข้า
{
  MotorStop();
  armupdown(servo_down);
  delay(100);
  arm_left_right(servoL_open - closeL, servoR_open - closeR);
  delay(200);

  // robot.servo(1, servo_down);
  // delay(100);
  // robot.servo(10, servoL_open - 95);
  // robot.servo(0, servoR_open - 91);
}

void arm_up_close()  //--------->>  ยกแขนขึ้น  และ หุบมือเข้า
{
  MotorStop();
  armupdown(servo_down + up);
  delay(100);
  arm_left_right(servoL_open - closeL, servoR_open - closeR);
  delay(200);
  // robot.servo(1, servo_down + 95);
  // delay(100);
  // robot.servo(10, servoL_open - 95);
  // robot.servo(0, servoR_open - 91);
}
void arm_close_up()  //--------->>  ยกแขนขึ้น  และ หุบมือเข้า
{
  MotorStop();
  arm_left_right(servoL_open - closeL, servoR_open - closeR);
  delay(200);
  armupdown(servo_down + up);
  delay(100);
  // robot.servo(10, servoL_open - 95);
  // robot.servo(0, servoR_open - 91);
  // delay(100);
  // robot.servo(1, servo_down + 95);
}
void arm_big_box()  //--------->>  คีบกล่องใหญ่
{
  MotorStop();
  armupdown(servo_down);
  arm_left_right(servoL_open - closeBigL, servoR_open - closeBigR);
  delay(200);
  // robot.servo(1, servo_down);
  // robot.servo(10, servoL_open - 30);
  // robot.servo(0, servoR_open - 30);
}


void arm_big_box_up()  //--------->>  คีบกล่องใหญ่
{
  MotorStop();
  arm_left_right(servoL_open - closeBigL, servoR_open - closeBigR);
  delay(200);
  armupdown(servo_down + up);
  delay(100);
  // robot.servo(1, servo_down);
  // robot.servo(10, servoL_open - 30);
  // robot.servo(0, servoR_open - 30);
}

void arm_behihd() {
  MotorStop();
  arm_left_right(servoL_open + behindL, servoR_open - behindR);
  delay(200);
}
void arm_up() {
  MotorStop();
  armupdown(servo_down + up);
  delay(100);
}

void arm_up45() {
  MotorStop();
  armupdown(servo_down + up45);
  delay(100);
}
void arm_down() {
  MotorStop();
  armupdown(servo_down);
  delay(100);
}

void arm_open() {
  MotorStop();
  arm_left_right(servoL_open, servoR_open);
  delay(200);
}

void arm_close() {
  MotorStop();
  arm_left_right(servoL_open - closeL, servoR_open - closeR);
  delay(200);
}

void arm_big() {
  MotorStop();
  arm_left_right(servoL_open - closeBigL, servoR_open - closeBigR);
  delay(200);
}

void arm_open_l() {
  MotorStop();
  arm_left_right(servoL_open, servoR_open - closeR);
  delay(200);
}

void arm_open_r() {
  MotorStop();
  arm_left_right(servoL_open - closeL, servoR_open);
  delay(200);
}




//ปรับความเร็วเซอร์โว


void arm_ready(int spd)  //--------->> แขนลง กางฝ่ามือออกเตรียมเข้าไปคีบ
{
  armupdown(servo_down, spd);
  arm_left_right(servoL_open - readyL, servoR_open - readyR, spd);
}

void arm_open_down(int spd)  //--------->>  กางฝ่ามือออก  และเอาแขนลง
{
  arm_left_right(servoL_open, servoR_open, spd);
  armupdown(servo_down, spd);
}
void arm_down_open(int spd)  //--------->>  เอาแขนลง  และ กางฝ่ามือออก
{

  armupdown(servo_down, spd);
  arm_left_right(servoL_open, servoR_open, spd);
}
void arm_open_up(int spd)  //--------->>  กางฝ่ามือออก  และยกแขนขึ้น
{
  arm_left_right(servoL_open, servoR_open, spd);
  armupdown(servo_down + up, spd);
}
void arm_up_open(int spd)  //--------->>  เอาแขนขึ้น  และ กางฝ่ามือออก
{

  arm_left_right(servoL_open, servoR_open,spd);
  armupdown(servo_down + up, spd);
}
void arm_down_close(int spd)  //--------->>  เอาแขนลง  และ หุบมือเข้า
{

  armupdown(servo_down, spd);
  arm_left_right(servoL_open - closeL, servoR_open - closeR, spd);
}

void arm_up_close(int spd)  //--------->>  ยกแขนขึ้น  และ หุบมือเข้า
{

  armupdown(servo_down + up, spd);
  arm_left_right(servoL_open - closeL, servoR_open - closeR, spd);
}
void arm_close_up(int spd)  //--------->>  ยกแขนขึ้น  และ หุบมือเข้า
{

  arm_left_right(servoL_open - closeL, servoR_open - closeR, spd);
  armupdown(servo_down + up, spd);
}
void arm_big_box(int spd)  //--------->>  คีบกล่องใหญ่
{
  armupdown(servo_down, spd);
  arm_left_right(servoL_open - closeBigL, servoR_open - closeBigR, spd);
}


void arm_big_box_up(int spd)  //--------->>  คีบกล่องใหญ่
{

  arm_left_right(servoL_open - closeBigL, servoR_open - closeBigR, spd);
  armupdown(servo_down + up, spd);
}

void arm_behihd(int spd) {
  arm_left_right(servoL_open + behindL, servoR_open - behindR, spd);
}
void arm_up(int spd) {
  armupdown(servo_down + up, spd);
}

void arm_up45(int spd) {
  armupdown(servo_down + up45, spd);
}
void arm_down(int spd) {

  armupdown(servo_down, spd);
}

void arm_open(int spd) {

  arm_left_right(servoL_open, servoR_open, spd);
}

void arm_close(int spd) {

  arm_left_right(servoL_open - closeL, servoR_open - closeR, spd);
}

void arm_big(int spd) {

  arm_left_right(servoL_open - closeBigL, servoR_open - closeBigR, spd);
}

void arm_open_l(int spd) {

  arm_left_right(servoL_open, servoR_open - closeR, spd);
}

void arm_open_r(int spd) {

  arm_left_right(servoL_open - closeL, servoR_open, spd);
}