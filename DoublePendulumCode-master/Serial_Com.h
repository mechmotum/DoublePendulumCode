#ifndef Serial_Com_h
#define Serial_Com_h
#include "DP_Fun.h"
#include "Controller.h"

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else 
  #include "WProgram.h"
#endif

  extern String command; // defines a string variable which we will fill up as we read serial inputs
  extern String motor;
  extern String gain;
  extern String value;
  extern long int unscaledGain;
  extern float newGainValue;
  
class Serial_Com {
 
 public:
 void Parse();
 void Update_Gains();

 private:
 

 
};



#endif
