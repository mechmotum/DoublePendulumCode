// importing the ControlP5 Library for GUI control and interface implementation 
// importing the Serial Library to enable a serial communication between your PC 
// and the Arduino
import processing.serial.*;
import controlP5.*;


//**************Initializing Variables *****************//

// Background Design Parameters// 
int Y_AXIS = 1;
int X_AXIS = 2;
color b1, b2, c1, c2;

// Background Image Parameters//
PImage img;



// Declaring a font style variable 
PFont font; 
String text; 



// Initializing a String Variable responsible for keeping track of the 
// currently selected pendulum component 
String PendComp="NONE";

// Initializing the Display Variables letting the User which motor controller 
// the user is currently modifying
String TM_Check="OFF";
String BM_Check="OFF";
String Cart_Check="OFF";

//Initilizing the display window's RGB values 
int TMr=0;
int TMg=0;
int TMb=0;
int BMr=0;
int BMg=0;
int BMb=0;
int Cartr=0;
int Cartg=0;
int Cartb=0;



// Initializing the Initial kp, ki and kd string variables for the different 
// motors that are used and preset in the arduino before the user 
// changes their values
String Kp_Int_BM;
String Ki_Int_BM;
String Kd_Int_BM;
String Kp_Int_TM;
String Ki_Int_TM;
String Kd_Int_TM;
String Kp_Int_Cart;
String Ki_Int_Cart;
String Kd_Int_Cart;
String Int_Con_Vals;

// initilizing string variales that will hold the new Kp, Ki, and Kd values 
// for display as the user enters them into the GUI
String Kp_Disp="Type Kp Vals in box below";
String Ki_Disp="Type Kd Vals in box below";
String Kd_Disp="Type Ki Vals in box below";

// These Strings will be used for Boolean operations later on in the code to check 
// if any new input has been entered into the selected motor of the double 
// pendulum
String Disp_Stat_TM="No New Intput";
String Disp_Stat_BM="No New Intput";
String Disp_Stat_Cart="No New Intput";

// Strings used to hold and retain displayed values for the kp,ki, and kd_Disp variables 
// to show when motors are selected 
String Kp_Disp_TM;
String Ki_Disp_TM;
String Kd_Disp_TM;
String Kp_Disp_BM;
String Ki_Disp_BM;
String Kd_Disp_BM;
String Kp_Disp_Cart;
String Ki_Disp_Cart;
String Kd_Disp_Cart;  
String Kp_Val;
String Ki_Val;
String Kd_Val;
int Point_Kp_Disp_W;
int Point_Ki_Disp_W;
int Point_Kd_Disp_W;
int Point_Kp_Disp_H;
int Point_Ki_Disp_H;
int Point_Kd_Disp_H;
boolean BackImage;


// Creates an object for the ControlP5 Library and the Serial Library
ControlP5 cp5; 
Serial myport;





// void setup runs once here just like it does in Arduino
void setup(){
  
// ************************ Inital Display Settings ***************// 


// Sets Size of Window 

size(displayWidth, displayHeight); 
surface.setSize(width/2,height);

Point_Kp_Disp_W=width/10;
Point_Ki_Disp_W=width/10*7;
Point_Kd_Disp_W=width/10;
Point_Kp_Disp_H=height/12;
Point_Ki_Disp_H=height/12;
Point_Kd_Disp_H=height/10*5;
// Loads Background image into variable
img=loadImage("matrix.jpg");

//sets style of font
font = createFont("calibri licrght bold", 20);


// ***************** Serial and Control properties ****// 
// creates an object for the ControlP5 Library
cp5= new ControlP5(this); 
ControlFont cf1 = new ControlFont(createFont("Arial",height/90));
  
//Identifies port number that arduino is connected to via USB
//The number inside the brackets correspond to the COM# of the USB port
String portName=Serial.list()[0];


print("Controller port");

// Initializes Serial Port Communication
// Here you can set the com port number and the baud rate 
// right now the baud rate is set to 9600, make sure this value is 
// same value that the arduino
myport= new Serial(this,portName,9600);

  
 
 
 //Initializes object for controlp5 library 
  cp5= new ControlP5(this); 
  
 
 // *********************** ControlP5 Textfields and Bangs ********// 
  // These lines govern the Text field entry areas in the GUI 
  cp5.addTextfield("Kp").setPosition(Point_Kp_Disp_W,Point_Kp_Disp_H+100).setSize(width/5,height/15).setAutoClear(false).setFont(cf1);
  cp5.addTextfield("Ki").setPosition(Point_Ki_Disp_W,Point_Ki_Disp_H+100).setSize(width/5,height/15).setAutoClear(false).setFont(cf1);
  cp5.addTextfield("Kd").setPosition(Point_Kd_Disp_W,Point_Kd_Disp_H+100).setSize(width/5,height/15).setAutoClear(false).setFont(cf1);
 
 // These are what defines the Bang properties
 // a Bang is basically a button that calls a function when pressed
 // These three in particular call the functions that sends data over the serial
 // port to the arduino
  cp5.addBang("Send_Kp").setPosition(Point_Kp_Disp_W,Point_Kp_Disp_H+200).setSize(width/5,height/15).setColorBackground(190).setFont(cf1).setColorBackground(color(0)).setColorForeground(color(255,0,0));
  cp5.addBang("Send_Ki").setPosition(Point_Ki_Disp_W,Point_Ki_Disp_H+200).setSize(width/5,height/15).setColorBackground(190).setFont(cf1).setColorBackground(color(0)).setColorForeground(color(255,0,0));
  cp5.addBang("Send_Kd").setPosition(Point_Kd_Disp_W,Point_Kd_Disp_H+200).setSize(width/5,height/15).setColorBackground(190).setFont(cf1).setColorBackground(color(0)).setColorForeground(color(255,0,0));
  
// These buttons allow the user to switch between motors 
  cp5.addBang("Set_Top_Pendulum").setPosition(Point_Ki_Disp_W,Point_Kp_Disp_H+height/3).setSize(100,height/15).setColorBackground(190).setFont(cf1);
  cp5.addBang("Set_Bottom_Pendulum").setPosition(Point_Ki_Disp_W,Point_Kp_Disp_H+height/3+height/6).setSize(100,height/15).setColorBackground(190).setFont(cf1);
  cp5.addBang("Set_Cart").setPosition(Point_Ki_Disp_W,Point_Kp_Disp_H+height/3+height/3).setSize(100,height/15).setColorBackground(190).setFont(cf1);
  cp5.addBang("Swing_up").setPosition(width/2-50,height/13*10).setSize(100,height/15).setColorBackground(190).setFont(cf1);
  cp5.addBang("Initialize_Con").setPosition(width/2-50,height/15*10).setSize(100,height/15).setColorBackground(190).setFont(cf1);
   
    cp5.addToggle("BackImage")
     .setPosition(width/8,height-height/10*2)
     .setSize(width/10,height/30)
     .setFont(cf1);
     ;
} 
  
void draw () {
  
    //*********************** Background Asthetics ************// 
  if (BackImage==true)  
  {
   img=loadImage("edge.jpg");
  }
  else if (BackImage==false){
    img=loadImage("matrix.jpg");
 }
 image(img,0,0,width,height);
   
  // ************************ Read Recieved *********************// 
  if (myport.available()>0) {
    // Reads string until a new line is read 
    String myString=myport.readStringUntil(10);
    if  (myString != null) {
      println(myString);
    }
  }
  textSize(height/90);
  fill(0);
  // Double Pendulum Section selection 
  rect(Point_Ki_Disp_W+100,Point_Kp_Disp_H+height/3,height/15,height/15);
  rect(Point_Ki_Disp_W+100,Point_Kp_Disp_H+height/3+height/6,height/15,height/15);
  rect(Point_Ki_Disp_W+100,Point_Kp_Disp_H+height/3+height/3,height/15,height/15);
  
  //Controller Value Display 
  rect(Point_Kp_Disp_W,Point_Kp_Disp_H,width/10*2,height/15);
  rect(Point_Kd_Disp_W,Point_Kd_Disp_H,width/10*2,height/15);
  rect(Point_Ki_Disp_W,Point_Ki_Disp_H,width/10*2,height/15);
  
  
  fill(TMr,TMg,TMb);
  text(TM_Check,Point_Ki_Disp_W+130,Point_Kp_Disp_H+height/3+height/20);
  fill(BMr,BMg,BMb);
  text(BM_Check,Point_Ki_Disp_W+130,Point_Kp_Disp_H+height/3+height*260/1200);
  fill(Cartr,Cartg,Cartb);
  text(Cart_Check,Point_Ki_Disp_W+130,Point_Kp_Disp_H+height/3+height*460/1200);
  textSize(height/90);
  fill(255);
  text(Kp_Disp, Point_Kp_Disp_W+10,Point_Kp_Disp_H+65);
  fill(255);
  text(Ki_Disp, Point_Ki_Disp_W+10,Point_Ki_Disp_H+65);
  fill(255);
  text(Kd_Disp, Point_Kd_Disp_W+10,Point_Kd_Disp_H+65);
  
  
  
}



// ************************ Code For Button Callbacks **********//


// *************************** This Section Contains the Code for the Buttons that Send PID Values to the Arduino Mega *****//
void Send_Kp(){
  
  String Kp_text=cp5.get(Textfield.class,"Kp").getText();
  Kp_Val=cp5.get(Textfield.class,"Kp").getText();
  float  Kp_Float= parseFloat(Kp_text)*10000;
         Kp_text=str(Kp_Float);
  if (PendComp=="TM"){
        Disp_Stat_TM="Info Sent";
      Kp_Disp_TM=Kp_Val;
      Kp_Disp=Kp_Val;}
        else if (PendComp=="BM"){
        Disp_Stat_BM="Info Sent";
      Kp_Disp_BM=Kp_Val;
    Kp_Disp=Kp_Val;}
        else if (PendComp=="Cart"){
        Disp_Stat_Cart="Info Sent";
      Kp_Disp_Cart=Kp_Val;
    Kp_Disp=Kp_Val;}
      
      
  
 myport.write(PendComp+"%"+"Kp "+ Kp_text+'\n');
  
  
}

void Send_Kd() {
  
 String Kd_text=cp5.get(Textfield.class,"Kd").getText();
 Kd_Val=cp5.get(Textfield.class,"Kd").getText();
 float  Kd_Float= parseFloat(Kd_text)*10000;
        Kd_text=str(Kd_Float);
 
 if (PendComp=="TM"){
        Disp_Stat_TM="Info Sent";
      Kd_Disp_TM=Kd_Val;
    Kd_Disp=Kd_Val;}
        else if (PendComp=="BM"){
        Disp_Stat_BM="Info Sent";
      Kd_Disp_BM=Kd_Val;
    Kd_Disp=Kd_Val;}
        else if (PendComp=="Cart"){
        Disp_Stat_Cart="Info Sent";
      Kd_Disp_Cart=Kd_Val;
    Kd_Disp=Kd_Val;}
        
 myport.write(PendComp +"%"+ "Kd "+ Kd_text+'\n');
 
}

void Send_Ki() {
  
 String Ki_text=cp5.get(Textfield.class,"Ki").getText();
 Ki_Val=cp5.get(Textfield.class,"Ki").getText();
 float  Ki_Float= parseFloat(Ki_text)*10000;
        Ki_text=str(Ki_Float);
        
        if (PendComp=="TM"){
        Disp_Stat_TM="Info Sent";
        Ki_Disp_TM=Ki_Val;
      Ki_Disp=Ki_Val;}
        else if (PendComp=="BM"){
        Disp_Stat_BM="Info Sent";
      Ki_Disp_BM=Ki_Val;
    Ki_Disp=Ki_Val;}
        else if (PendComp=="Cart"){
        Disp_Stat_Cart="Info Sent";
      Ki_Disp_Cart=Ki_Val;
    Ki_Disp=Ki_Val;}
        
        
 
 
 myport.write(PendComp+"%"+"Ki "+ Ki_text+'\n');
 
 
}


// *************** This Section Govers the Code that allows the user to switch between motors to adjust the PID values *****// 


void Set_Top_Pendulum() { 
  
  PendComp="TM"; 
 TM_Check="ON";
 BM_Check="OFF";
Cart_Check="OFF";
  TMr=0;
 TMg=255;
 TMb=0;
 BMr=255;
 BMg=0;
 BMb=0;
 Cartr=255;
 Cartg=0;
 Cartb=0;

  if (Disp_Stat_TM=="No New Intput"){
  Kp_Disp=Kp_Int_TM;
 Ki_Disp=Ki_Int_TM;
 Kd_Disp=Kd_Int_TM;
}
else{
   if (Kp_Disp_TM==null){
 Kp_Disp=Kp_Int_TM;}
 else{
Kp_Disp=Kp_Disp_TM;
 }
 
 if (Ki_Disp_TM==null){
Ki_Disp=Ki_Int_TM;}
else {
 Ki_Disp=Ki_Disp_TM;
}

if(Kd_Disp_TM==null) {
Kd_Disp=Kd_Int_TM;
 }
 else{
 Kd_Disp=Kd_Disp_TM;}
}

  
} 

void Set_Bottom_Pendulum() {
  PendComp="BM";
 TM_Check="OFF";
 BM_Check="ON";
 Cart_Check="OFF";
 TMr=255;
 TMg=0;
 TMb=0;
 BMr=0;
 BMg=255;
 BMb=0;
 Cartr=255;
 Cartg=0;
 Cartb=0;
 
 if (Disp_Stat_BM=="No New Intput"){
  Kp_Disp=Kp_Int_BM;
 Ki_Disp=Ki_Int_BM;
 Kd_Disp=Kd_Int_BM;
}
else{
   if (Kp_Disp_BM==null){
 Kp_Disp=Kp_Int_BM;}
 else{
Kp_Disp=Kp_Disp_BM;
 }
 
 if (Ki_Disp_BM==null){
Ki_Disp=Ki_Int_BM;}
else {
 Ki_Disp=Ki_Disp_BM;
}

if(Kd_Disp_BM==null) {
Kd_Disp=Kd_Int_BM;
 }
 else{
 Kd_Disp=Kd_Disp_BM;}
}

} 


void Set_Cart() { 
  PendComp="Cart";
TM_Check="OFF";
 BM_Check="OFF";
Cart_Check="ON";
 TMr=255;
 TMg=0;
 TMb=0;
 BMr=255;
 BMg=0;
 BMb=0;
 Cartr=0;
 Cartg=255;
 Cartb=0;
 if (Disp_Stat_Cart=="No New Intput"){
  Kp_Disp=Kp_Int_Cart;
 Ki_Disp=Ki_Int_Cart;
 Kd_Disp=Kd_Int_Cart;
}
else{
 
if (Kp_Disp_Cart==null){
 Kp_Disp=Kp_Int_Cart;}
 else{
Kp_Disp=Kp_Disp_Cart;
 }
 
 if (Ki_Disp_Cart==null){
Ki_Disp=Ki_Int_Cart;}
else {
 Ki_Disp=Ki_Disp_Cart;
}

if(Kd_Disp_Cart==null) {
Kd_Disp=Kd_Int_Cart;
 }
 else{
 Kd_Disp=Kd_Disp_Cart;}
}
} 

void Swing_up() {
  myport.write("$");
}

void Initialize_Con(){ 
  

  
  myport.write("@"); 
  
  while(myport.available()==0){
    print("retreiving data");
  }
  
ParseIntVals();
  
  
  }
  
// parsing function that breaks initial pid values string from arduino // 
void ParseIntVals() {
  
  print("\n");
  print("ParseIntVals Called");
  while (myport.available() !=0){
  if (myport.available()>0) {
     
    print("\n");
    print("conditional statement activated");
    print("\n");
  Int_Con_Vals=myport.readStringUntil(10);
   
    
    if (myport.available()==0){
    break;
  }
  
  }
  }
  print("\n");
  print("While loop broken!");
  print("\n"+"Values Recieved are:"+"||"+Int_Con_Vals+"||");
  
  
   int activateSplit=1;
    if  (activateSplit==1) {
   // String Int_Con_Vals=myport.readStringUntil(200);
    String Con_String_Array[]=Int_Con_Vals.split(",");
    Kp_Int_BM=Con_String_Array[0];
    Ki_Int_BM=Con_String_Array[1];
    Kd_Int_BM=Con_String_Array[2];
    Kp_Int_TM=Con_String_Array[3];
    Ki_Int_TM=Con_String_Array[4];
    Kd_Int_TM=Con_String_Array[5];
    Kp_Int_Cart=Con_String_Array[6];
    Ki_Int_Cart=Con_String_Array[7];
    Kd_Int_Cart=Con_String_Array[8];
    
    
 
    }
    }
