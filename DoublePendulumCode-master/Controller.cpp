#include "Controller.h"

// PD controller
// This basic PD controller is no longer needed, to achieve same effect, set KI = 0 on PID controller
  double PD_BM_Kp = 10;
  double PD_BM_Kd = .1;
  double PD_TM_Kp = 4;
  double PD_TM_Kd = .1;
  
void Controller::PD_Controller() {
BM_PWM = (int) PD_BM_Kp*BM_Error + PD_BM_Kd*BM_dError;
TM_PWM = (int) PD_TM_Kp*TM_Error + PD_TM_Kd*TM_dError;
}

// PID controller
  double PID_BM_Kp = 6;
  double PID_BM_Kd = 0; // Initially set to zero to be conservative
  double PID_BM_Ki = 0; // Initially set to zero to be conservative
  double PID_TM_Kp = 4;
  double PID_TM_Kd = 0; // Initially set to zero to be conservative
  double PID_TM_Ki = 0; // Initially set to zero to be conservative
  
void Controller::PID_Controller() {
BM_PWM = (int) PID_BM_Kp*BM_Error + PID_BM_Kd*BM_dError + PID_BM_Ki*BM_integralError;
TM_PWM = (int) PID_TM_Kp*TM_Error + PID_TM_Kd*TM_dError + PID_TM_Ki*TM_integralError;
}

// Cart PID controller
// The cart is on a PID controller since once tuned, it will allow the user to get rapid responses and control position nicely
  double PID_Cart_Kp = 200;
  double PID_Cart_Kd = 0; // Initially set to zero to be conservative
  double PID_Cart_Ki = 0; // Initially set to zero to be conservative
  
void Controller::PID_Cart_Controller() {
Cart_PWM = (int) PID_Cart_Kp*Cart_Error + PID_Cart_Kd*Cart_dError + PID_Cart_Ki*Cart_integralError;
}
