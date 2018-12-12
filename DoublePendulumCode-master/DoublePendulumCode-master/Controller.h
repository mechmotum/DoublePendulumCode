#ifndef Controller_h
#define Controller_h
#include "DP_Fun.h"
#if (ARDUINO >= 100)
  #include "Arduino.h"
#else 
  #include "WProgram.h"
#endif


// Gains are externed so that they can be modified with serial commands and Serial_Com.cpp parse function
  extern double PID_BM_Kp;
  extern double PID_BM_Kd;
  extern double PID_BM_Ki;
  extern double PID_TM_Kp;
  extern double PID_TM_Kd;
  extern double PID_TM_Ki;
  extern double PID_Cart_Kp;
  extern double PID_Cart_Kd;
  extern double PID_Cart_Ki;
  
class Controller {
 
 public:
 void PD_Controller();
 void PID_Controller();
 void PID_Cart_Controller();

 private:
 

 
};



#endif
