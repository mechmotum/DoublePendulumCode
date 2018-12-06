// 2018_11_1
#include "Dp_Fun.h"
#include "Controller.h"
#include "Set_Pos_And_Angles.h"
#include "Serial_Com.h"
// Defining pin numbers **NOTE** Pins 2,3,18,19,20,21 are reserved attachInterrupt

 #include <math.h>

 Dp_Fun dpfun;
 Controller controller;
 Set_Pos_And_Angles setPosAngle;
 Serial_Com serialCom;

// Defining pins 
  int Cart_Step_Pin=8;
  int Cart_Dir_Pin=9;
  int Cart_OutputA=20;
  int Cart_OutputB=21;
  int BM_Step_Pin=4;
  int BM_Dir_Pin=5;
  int BM_OutputA=2;
  int BM_OutputB=3;
  int BM_GND=50;
  int TM_Step_Pin=6;
  int TM_Dir_Pin=7;
  int TM_OutputA=18;
  int TM_OutputB=19;
  int TM_GND=52;



/////////////////////////////////////////////////////////////////////////////////////

// Sets timestep, angles reset to zero at current location, states set to zero
  
  int Cart_Counter = 0;
  double Cart_X = 0;
  double Cart_Error = 0;
  double Cart_dError = 0;
  double Cart_Old_Error = 0;
  double Cart_integralError = 0;
  int Cart_PWM = 0;

  int BM_Counter = 0;
  double BM_Angle = 0;
  double BM_Error = 0;
  double BM_dError = 0;
  double BM_Old_Error = 0;
  double BM_integralError = 0;
  int BM_PWM = 0;
  
  int TM_Counter = 0;
  double TM_Angle = 0;
  double TM_Error = 0;
  double TM_dError = 0;
  double TM_Old_Error = 0;
  double TM_integralError = 0;
  int TM_PWM = 0;
  
// Time and Timestep
// Note: dt is currently chosen as the approximate time each loop takes. 
// Consider modifying so that dt is equal to the length of each previous time step.
// With this alternative approach, a more accurate dt could be achieved 
  double dt = 0.008; // 25 ms based on measuring the time stamp at each loop, change based on actual amount of time each loop takes. 
  unsigned long start_t = 0; // This variable is used later to "zero" the time readings once the user presses start
  unsigned long t = millis();
  long int index = 0;
  
// Define initial set angles
  double Bottom_Set_Angle = 0;
  double Top_Set_Angle = 0;
  double Cart_Set_X = 0;

  // Variables to break out of while loops
  char p = 0;  

  // For serial parsing
  char c = 0;
  String command = ""; // defines a string variable which we will fill up as we read serial inputs
  String motor = ""; // Specifies which motor (BM, TM, Cart)
  String gain = ""; // Specifies which gain (Kp, Ki, Kd)
  String value = ""; // Value of gain x 10000 as a string 
  long int unscaledGain = 0; // String must be converted to an integer, cannot convert directly to float
  float newGainValue = 0; // Later string is converted to a float and divided by 10000 to retrieve value

/////////////////////////////////////////////////////////////////////////////////////

void setup() {

// Begin serial communication
Serial.begin(9600); // Consider increasing this baud rate
delay(100); // Delay and then printing a new line seems to eliminate lost bytes when starting serial com
Serial.println();
Serial.println("Everything set to zero, void setup() has started");

 // Setting Pins to proper inputs/outputs
dpfun.PendPinInitialize();
Serial.println("Pend initialize complete");

// Attach interrupt functions
 attachInterrupt(digitalPinToInterrupt(Cart_OutputA), dpfunCOAC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(Cart_OutputB), dpfunCOBC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(BM_OutputA), dpfunBOAC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(BM_OutputB), dpfunBOBC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(TM_OutputA), dpfunTOAC, CHANGE);
 attachInterrupt(digitalPinToInterrupt(TM_OutputB), dpfunTOBC, CHANGE);

Serial.println("Interrupts set");

// Pause until start button pressed
// Waits for user to give a serial input before swinging up and moving forward
// This allows the user to open Processing, establish serial connection, and get ready
  while (p != '1') {
  delay(100);
    if(Serial.available()){
      if(Serial.read() == '@'){ // Waits for the @ symbol to be received to know that Processing is ready 
        // Prints all gains in a comma separated line so that Processing can identify the initial gains and display them for the user
        Serial.print(PID_BM_Kp,4);
        Serial.print(",");
        Serial.print(PID_BM_Ki,4);
        Serial.print(",");
        Serial.print(PID_BM_Kd,4);
        Serial.print(",");
        Serial.print(PID_TM_Kp,4);
        Serial.print(",");
        Serial.print(PID_TM_Ki,4);
        Serial.print(",");
        Serial.print(PID_TM_Kd,4);
        Serial.print(",");
        Serial.print(PID_Cart_Kp,4);
        Serial.print(",");
        Serial.print(PID_Cart_Ki,4);
        Serial.print(",");
        Serial.println(PID_Cart_Kd,4);
        Serial.flush();
        while (p != '1'){
          delay(100);
          if(Serial.available()) {
            if(Serial.read() == '$') { // Once Processing has read the gains, it sends the $ symbol and the code proceeds
              dpfun.Swing_Up();
              Serial.println("Swingup done");
              p = Serial.read();
              p = '1';  
            }
          }
        }
      }
    }
  }
Serial.println();
Serial.println("Index , Time , Cart_X , BM_Angle , TM_Angle"); // Prints headers

start_t = millis(); // This time is subtracted from the "millis" command in the main loop to give time relative to the pendulum completing its swingup
}


// Main loop
// Issues: Serial print statements in this loop are probably slowing down this code. This is actually a bigger concern.
// We have not worked on a solution for this yet, but one solution could be having a second arduino that only prints data.
// This would be easy to do, maybe just split the encoder lines so that the second arduino also counts encoder values and crunches numbers on its own
// This second arduino could interface with any number of serial logging applications (TerraTerm, etc) to log data
void loop() {
index = index + 1;
//Serial.print(index);
//Serial.print(",");
t = millis() - start_t;  
Serial.println((float) t/1000, 3);
//Serial.print(",");
setPosAngle.BM_Setpoint_At_t(); // Updates the set angle of the bottom motor as a function of time
setPosAngle.TM_Setpoint_At_t(); // Updates the set angle of the top motor as a function of time
setPosAngle.Cart_Setpoint_At_t(); // Updates the x position of the bottom motor as a function of time
dpfun.Safety_Check(); // Ensures that set position and angles are not out of bounds and clips if needed
dpfun.Get_Cart_States(); // Gets cart Error, dError, and integralError
controller.PID_Cart_Controller(); // Computes cart PWM
dpfun.Send_Cart_PWM(); // Sends PWM to cart
dpfun.Get_States(); // Gets arm Errors, dErrors, and integralErrors
controller.PID_Controller(); // Computes cart PWM
dpfun.Send_PWM();  // Sends PWM to arm
//delay(10); // Delays 10 ms, used to be 1ms, adjust based on how long it ACTUALLY takes to complete a loop. This needs to be addressed
//Serial.print(Cart_X); // Printing everything slows the code down by 15 ms! No delays, loop takes 8ms, with delays its ~25ms. 
//Serial.print(",");
//Serial.print(BM_Angle);
//Serial.print(",");
//Serial.println(TM_Angle);
serialCom.Parse(); //Parses data and then executes command (updates controller gains based on user input)
}

// Bring the ISRs into global scale. There is probably a cleaner way to do this, but this approach seems to work with no issues
void dpfunCOAC(){
dpfun.Cart_OutputA_Change(); 
}

void dpfunCOBC() {
dpfun.Cart_OutputB_Change();
}

void dpfunBOAC() {
 dpfun.BM_OutputA_Change();
}

void dpfunBOBC() {
dpfun.BM_OutputB_Change();
}

void dpfunTOAC() {
dpfun.TM_OutputA_Change();
}

void dpfunTOBC(){
dpfun.TM_OutputB_Change();
}
