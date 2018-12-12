#ifndef Dp_Fun_h
#define Dp_Fun_h
#include "Set_Pos_And_Angles.h" //NEW. SEE IF IT ALLOWS POSITION AS FUNCTION OF TIME

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else 
  #include "WProgram.h"
#endif




/////////////////////////////////////////////////////////////////////////////////////

// Cart
 extern int Cart_Counter;
 extern double Cart_X;
 extern double Cart_Error;
 extern double Cart_dError;
 extern double Cart_Old_Error;
 extern double Cart_integralError;
 extern int Cart_PWM;
  
// Bottom motor
 extern int BM_Counter;
 extern double BM_Angle;
 extern double BM_Error;
 extern double BM_dError;
 extern double BM_Old_Error;
 extern double BM_integralError;
 extern int BM_PWM;

 // Top motor
 extern int TM_Counter;
 extern double TM_Angle;
 extern double TM_Error;
 extern double TM_dError;
 extern double TM_Old_Error;
 extern double TM_integralError;
 extern int TM_PWM;
 
// Other
 extern int Cart_Step_Pin;
 extern int Cart_Dir_Pin;
 extern int Cart_OutputA;
 extern int Cart_OutputB;
 extern int BM_Step_Pin;
 extern int BM_Dir_Pin;
 extern int BM_OutputA;
 extern int BM_OutputB;
 extern int BM_GND;
 extern int TM_Step_Pin;
 extern int TM_Dir_Pin;
 extern int TM_OutputA;
 extern int TM_OutputB;
 extern int TM_GND; 
 extern double dt;
 extern unsigned long t;
 extern char c;
 extern char p;


 
class Dp_Fun {  
  
public: 
  void Safety_Check();
  void Get_Cart_States();
  void Send_Cart_PWM();
  void Dp_Initial_Conditions();
  void Swing_Up();
  void Send_PWM();
  void Get_States();
  void Cart_OutputA_Change();
  void Cart_OutputB_Change();
  void BM_OutputA_Change();
  void BM_OutputB_Change();
  void TM_OutputA_Change();
  void TM_OutputB_Change();
  void PendPinInitialize();

private: 

 
};


#endif
