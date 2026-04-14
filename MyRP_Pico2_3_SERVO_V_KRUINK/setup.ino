void set_motor()
  {    
    robot.set_Freq("Coreless_Motors");      // หรือ "DC_Motors"
    robot.sp_factor_cm_s_forFW(1.75);  
    robot.sp_factor_cm_s_forBW(1.75);
    
    
    robot.set_slow_motor(20, 20);     
    robot.set_turn_center_l(-90, 90);
    robot.set_turn_center_r(90, -90);
    robot.set_turn_front_l(-30, 100);
    robot.set_turn_front_r(100, -30);
    robot.set_brake_fc(10, 30);
    robot.set_brake_bc(10, 30);
    robot.set_delay_f(10);
    
  }


  void fw_ch_line(int num)
  {
    for(int i=0; i< num; i++)
      {
        while(1)
          {
            delay(5);      
            if(robot.read_sensorA(0) < robot.md_sensorA(0)-50 && robot.read_sensorA(7) > robot.md_sensorA(7)-50)
              {
                robot.Motor(-5 ,20);
              }
            else if(robot.read_sensorA(0) > robot.md_sensorA(0)-50 && robot.read_sensorA(7) < robot.md_sensorA(7)-50)
              {
                robot.Motor(20 ,-5);
              }
            else if(robot.read_sensorA(0) > robot.md_sensorA(0)-50 && robot.read_sensorA(7) > robot.md_sensorA(7)-50)
              {          
                robot.Motor(15 ,15);
              }
            else 
              {
                robot.Motor(-1 ,-1);
                break;
              }      
          }
        if(num > 1)
          {
            robot.Motor(-15 ,-15);
            delay(50);
            robot.Motor(-1 ,-1);
          }
      }
    
  }

void bw_ch_line(int num)
  {
    for(int i=0; i< num; i++)
      {
        while(1)
          {
            delay(5);      
            if(robot.read_sensorB(0) < robot.md_sensorB(0)-50 && robot.read_sensorB(7) > robot.md_sensorB(7)-50)
              {
                robot.Motor(-20 ,5);
              }
            else if(robot.read_sensorB(0) > robot.md_sensorB(0)-50 && robot.read_sensorB(7) < robot.md_sensorB(7)-50)
              {
                robot.Motor(5 ,-20);
              }
            else if(robot.read_sensorB(0) > robot.md_sensorB(0)-50 && robot.read_sensorB(7) > robot.md_sensorB(7)-50)
              {          
                robot.Motor(-15 ,-20);
              }
            else 
              {
                robot.Motor(-1 ,-1);
                break;
              }      
          }
        if(num > 1)
          {
            robot.Motor(10 ,10);
            delay(50);
            robot.Motor(-1 ,-1);
          }
      }
    

  }
