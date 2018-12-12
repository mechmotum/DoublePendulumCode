# DoublePendulumCode
This README includes a high level description of how each file works. The structure of the double pendulum code is such that a user can easily add custom controllers, set the gains during operation, and specify positions and angles for the device as a function of time. 
Each file is internally commented in detail, and so in order to modify files it is recommended to read through the comments.

Pendulum_Code.ino
This file is called to run the code. After setting up initial values, the setup loop waits for the user to open the associated Processing GUI and run the initialization and start sequences via GUI inputs. Once complete, the main loop runs, identifying the current time t, then finding user specified set positions and angles, system states, and controller outputs. Then appropriate PWM values are sent.

Controller library:
The controller library allows users to create new controllers inside the CPP file. Follow the structure within the .h file to make the controller functions public, and then call the controllers inside the main loop to test them out. Note that the gains of new controllers need to be added to the Serial_Com library so that they can be adjusted while the code is running using the GUI.

Serial_Com library:
This library contains functions relating to serial communication. In order to respond to user inputs from Processing GUI, the arduino must take a serial input (string), and manipulate it to identify what the user wants.

Set_Pos_And_Angles library:
The user can specify position of the cart and the angles of the two pendulum bars as a function of time in this library. The positions and angles are found and used in the main loop. Units are milliseconds, inches, and degrees.

DP_Fun library:
This library contains assorted functions required for operation. Functions include computing system states, sending PWM signals, checking if user-specified inputs are safe, initializing variables, swinging up the pendulum, counting encoder ticks to compute states, and more. The intention is that a user never needs to interract with this library, and that the user can focus on customizing and tuning controllers, and sending different inputs as functions of time. 
