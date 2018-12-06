#include "Dp_Fun.h"



// Initialize function
// Defines which pins are inputs and outputs
void Dp_Fun::PendPinInitialize()
{ pinMode(Cart_Step_Pin,OUTPUT);
 pinMode(Cart_Dir_Pin,OUTPUT);
 pinMode(Cart_OutputA,INPUT);
 pinMode(Cart_OutputB,INPUT);
 pinMode(BM_Step_Pin,OUTPUT);
 pinMode(BM_Dir_Pin,OUTPUT);
 pinMode(BM_OutputA,INPUT);
 pinMode(BM_OutputB,INPUT);
 pinMode(BM_GND, OUTPUT);
 digitalWrite(BM_GND, LOW);
 pinMode(TM_Step_Pin,OUTPUT);
 pinMode(TM_Dir_Pin,OUTPUT);
 pinMode(TM_OutputA,INPUT);
 pinMode(TM_OutputB,INPUT);
 pinMode(TM_GND, OUTPUT);
 digitalWrite(TM_GND, LOW);}


// Interrput functions
// The interupt functions interrupt the code and increase or decrease the encoder counts as the encoder rotates
// To understand these functions, it is important to understand the operating principles of the encoders...
// As the encoder rotates, its output pins change from high to low with each count.
// There are 3 output pins, but we are only using 2. This gives high enough accuracy for this application (>10counts/degree)

// Cart interrupt functions
void Dp_Fun::Cart_OutputA_Change() 
{
 if(digitalRead(Cart_OutputA) == HIGH) {
 if(digitalRead(Cart_OutputB) == HIGH) {
 Cart_Counter--;
 } else {
 Cart_Counter++;
 }
 } else {
 if(digitalRead(Cart_OutputB) == HIGH) {
 Cart_Counter++;
 } else {
 Cart_Counter--;
 }
 }
}


void Dp_Fun::Cart_OutputB_Change() 
{
 if(digitalRead(Cart_OutputB) == HIGH) {
 if(digitalRead(Cart_OutputA) == HIGH) {
 Cart_Counter++;
 } else {
 Cart_Counter--;
 }
 } else {
 if(digitalRead(Cart_OutputA) == HIGH) {
 Cart_Counter--;
 } else {
 Cart_Counter++;
 }
 }
}

// BM interrupt functions
void Dp_Fun::BM_OutputA_Change() 
{
 if(digitalRead(BM_OutputA) == HIGH) {
 if(digitalRead(BM_OutputB) == HIGH) {
 BM_Counter--;
 } else {
 BM_Counter++;
 }
 } else {
 if(digitalRead(BM_OutputB) == HIGH) {
 BM_Counter++;
 } else {
 BM_Counter--;
 }
 }
}
void Dp_Fun::BM_OutputB_Change() 
{
 if(digitalRead(BM_OutputB) == HIGH) {
 if(digitalRead(BM_OutputA) == HIGH) {
 BM_Counter++;
 } else {
 BM_Counter--;
 }
 } else {
 if(digitalRead(BM_OutputA) == HIGH) {
 BM_Counter--;
 } else {
 BM_Counter++;
 }
 }
}

 // TM interrupt functions
 void Dp_Fun::TM_OutputA_Change() 
 {
 if(digitalRead(TM_OutputA) == HIGH) {
 if(digitalRead(TM_OutputB) == HIGH) {
 TM_Counter--;
 } else {
 TM_Counter++;
 }
 } else {
 if(digitalRead(TM_OutputB) == HIGH) {
 TM_Counter++;
 } else {
 TM_Counter--;
 }
 }
}
void Dp_Fun::TM_OutputB_Change() 
{
 if(digitalRead(TM_OutputB) == HIGH) {
 if(digitalRead(TM_OutputA) == HIGH) {
 TM_Counter++;
 } else {
 TM_Counter--;
 }
 } else {
 if(digitalRead(TM_OutputA) == HIGH) {
 TM_Counter--;
 } else {
 TM_Counter++;
 }
 }
}

// Pendulum swing up routine
// Only the bottom pendulum needs to swing up and be re-zerod
void Dp_Fun::Swing_Up(){
digitalWrite(BM_Dir_Pin, HIGH); // Set direction to counter-clockwise
while (BM_Counter < 2625) { // While the arm has not swung 90 deg
 analogWrite(BM_Step_Pin, 255); // Set PWM to 100% duty 
 Serial.println(BM_Counter); // Print the counter value
 Serial.flush();
 delay(10); // Delay to avoid serial com issues, not sure this is necessary
}
analogWrite(BM_Step_Pin, 0); // Once swinging up, 0% duty cycle
BM_Counter = 0; // Reset counter, sets vertical to 0 deg
delay(10); // Not sure this line is necessary
}


//Get states of top and bottom motor
void Dp_Fun::Get_States() {
  BM_Old_Error = BM_Error; // Error at previous time step saved as "old error"
  BM_Angle = (double) BM_Counter/14.611; // Calculates angle. 14.611 counts/deg
  BM_Error = Bottom_Set_Angle - BM_Angle; // 
  BM_dError = (BM_Error-BM_Old_Error)/dt;
  BM_integralError = BM_integralError + BM_Error;
  TM_Old_Error = TM_Error;
  TM_Angle = (double) TM_Counter/11.378;
  TM_Error = Top_Set_Angle - TM_Angle;
  TM_dError = (TM_Error - TM_Old_Error)/dt;
  TM_integralError = TM_integralError + TM_Error;
  }

//Write PWM signals
void Dp_Fun::Send_PWM() {
  //Clip signals
  if (BM_PWM > 255) {
    BM_PWM = 255;
  }
  if (BM_PWM < -255) {
    BM_PWM = -255;
  }
  if (TM_PWM > 255) {
    TM_PWM = 255;
  }
  if (TM_PWM < -255){
    TM_PWM = -255;
  }
  //Set pin directions based on PWM sign, then make PWM positive
   if (BM_PWM < 0) {
  digitalWrite(BM_Dir_Pin,LOW);
 }
 if (BM_PWM > 0) {
  digitalWrite(BM_Dir_Pin,HIGH);
 }
 if (BM_PWM < 0) {
  BM_PWM = -BM_PWM;
 }
  if (TM_PWM > 0){
 digitalWrite(TM_Dir_Pin,LOW);
 }
 if (TM_PWM < 0){
  digitalWrite(TM_Dir_Pin,HIGH);
 }
 if (TM_PWM < 0) {
  TM_PWM = -TM_PWM;
 }
 analogWrite(BM_Step_Pin,BM_PWM);
 analogWrite(TM_Step_Pin,TM_PWM);
}

// Safety check and software limits
// The cart should be positioned in the center of the track during operation for this safety check to be effective
// This function examines the set angles of the pendulum and set position of the cart
// If the set position/angles are outside of specified bounds, this function clips those set values
void Dp_Fun::Safety_Check(){
  if (Cart_Set_X > 3.5){ //Cart X is in inches
    Cart_Set_X = 3.5;
  }
  if (Cart_Set_X < -3.5){
    Cart_Set_X = -3.5;
  }
  if (Bottom_Set_Angle > 160){
    Bottom_Set_Angle = 160;  
  }
  if (Bottom_Set_Angle < -160){
    Bottom_Set_Angle = -160;
  }
  if (Top_Set_Angle > 90){
    Top_Set_Angle = 90;
  }  
  if (Top_Set_Angle < -90){
    Top_Set_Angle = -90;
  }
}

// Cart states
void Dp_Fun::Get_Cart_States() {
  Cart_Old_Error = Cart_Error;
  Cart_X = (double) Cart_Counter/1085; // 8.5" = 9225 counts. This was found experimentally by averaging 3 trials
  Cart_Error = Cart_Set_X - Cart_X;
  Cart_dError = (Cart_Error-Cart_Old_Error)/dt;
  Cart_integralError = Cart_integralError + Cart_Error;
  }



// Cart PWM
void Dp_Fun::Send_Cart_PWM() {
  //Clip signals
  if (Cart_PWM > 255) {
    Cart_PWM = 255;
  }
  if (Cart_PWM < -255) {
    Cart_PWM = -255;
  }
  
  //Set pin directions based on PWM sign, then make PWM positive
   if (Cart_PWM > 0) {
  digitalWrite(Cart_Dir_Pin,LOW);
 }
 if (Cart_PWM < 0) {
  digitalWrite(Cart_Dir_Pin,HIGH);
 }
 if (Cart_PWM < 0) {
  Cart_PWM = -Cart_PWM;
 }
 analogWrite(Cart_Step_Pin,Cart_PWM);
}
