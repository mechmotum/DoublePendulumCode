#include "Serial_Com.h"

// This section of code governs serial data that passes through the arduino to the user's PC. 
void Serial_Com::Parse() {
 
  if(Serial.available()){ // if there is data in the buffer
    char c = Serial.read(); // reads the character in the buffer
    if(c=='\n') { // if the new line character is sent (like at end of a command) this acts as a deliminator
      Serial.println(command);
      // incomming commands are of the form "BM%Kp 10300"
      motor = command.substring(0, command.indexOf("%")); // Identifies Motor ID
      gain = command.substring(command.indexOf("%") + 1,command.indexOf(" ")); // Identifies which gain (Kp Ki Kd) 
      value = command.substring(command.indexOf(" ") + 1); // Identifies value of gain. Note: incomming gains are multiplied by 10000
      unscaledGain = value.toInt(); // Converts value to integer. This is why the gains are x10000. Cannot convert string to float directly
      newGainValue = (float) unscaledGain; // Convert integer to float
      newGainValue = newGainValue/10000; // Divide by 10000 to retrieve desired value
      Serial.print("New gain read as ");
      Serial.println(newGainValue);
      Serial.println("Setting gain now...");
      Update_Gains(); // executes the command (updates the gain)
      command = ""; // resets the command string to blank
      Serial.println("Parse function finished");
    }
    else
    {
      command += c; // if you havent reached the end of the buffer, append to the command variable
    }
    }
}


// Updates gains
// This function has a nested "if-statement" structure that allows the PID gains of the three motors to be updated individually
void Serial_Com::Update_Gains(){

  if(motor=="TM") {
    if(gain.equalsIgnoreCase("Kp")) { // Reads value ignoring captialization of letters
      PID_TM_Kp = newGainValue;
      Serial.print("PID_TM_Kp = "); //Serial Print used to send information back through the serial monitor
      Serial.println(PID_TM_Kp,5);
      }   
    else if(gain.equalsIgnoreCase("Kd")) {
      PID_TM_Kd = newGainValue;  
      Serial.print("PID_TM_Kd = ");
      Serial.println(PID_TM_Kd,5);
      }
    else if(gain.equalsIgnoreCase("Ki")) {
      PID_TM_Ki = newGainValue;
      Serial.print("PID_TM_Ki = ");
      Serial.println(PID_TM_Ki,5);
      }  
    else {
      Serial.println("TM command not recognized");
      }
    }
  
  else if(motor=="BM") {
    if(gain.equalsIgnoreCase("Kp")) { 
      PID_BM_Kp = newGainValue;
      Serial.print("PID_BM_Kp = ");
      Serial.println(PID_BM_Kp,5);
      }   
    else if(gain.equalsIgnoreCase("Kd")) {
      PID_BM_Kd = newGainValue;  
      Serial.print("PID_BM_Kd = ");
      Serial.println(PID_BM_Kd,5);      
      }
    else if(gain.equalsIgnoreCase("Ki")) {
      PID_BM_Ki = newGainValue;
      Serial.print("PID_BM_Ki = ");
      Serial.println(PID_BM_Ki,5);      
      }  
    else {
      Serial.println("BM command not recognized");
      }
    }
  
  else if(motor=="Cart") {
    if(gain.equalsIgnoreCase("Kp")) { 
      PID_Cart_Kp = newGainValue;
      Serial.print("PID_Cart_Kp = ");
      Serial.println(PID_Cart_Kp,5);   
      }   
    else if(gain.equalsIgnoreCase("Kd")) {
      PID_Cart_Kd = newGainValue; 
      Serial.print("PID_Cart_Kd = ");
      Serial.println(PID_Cart_Kd,5);    
      }
    else if(gain.equalsIgnoreCase("Ki")) {
      PID_Cart_Ki = newGainValue;
      Serial.print("PID_Cart_Ki = ");
      Serial.println(PID_Cart_Ki,5);   
      }  
    else {
      Serial.println("Cart command not recognized");
      }   
    }
  
  else {
    Serial.println("Command not recognized, motor not specified correctly");
    }
}
