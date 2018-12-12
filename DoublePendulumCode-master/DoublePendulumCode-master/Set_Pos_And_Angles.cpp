#include "Set_Pos_And_Angles.h"
#include "Dp_Fun.h"

void Set_Pos_And_Angles::ZeroSetpoints() {
  double Bottom_Set_Angle = 0;
  double Top_Set_Angle = 0;
  double Cart_Set_X = 0;
}

// Set bottom angle in degree
// User can write position/angle functions in units of degrees, inches, and milliseconds
void Set_Pos_And_Angles::BM_Setpoint_At_t() {
Bottom_Set_Angle = 0;
//Bottom_Set_Angle = (double) 25*sin(1000*.25*2*3.14159*t); // note t is in ms
}

// Set top angle in degrees
// User can write position/angle functions in units of degrees, inches, and milliseconds
void Set_Pos_And_Angles::TM_Setpoint_At_t() {
Top_Set_Angle = 0;
//Top_Set_Angle = (double) 25*sin(1000*.5*2*3.14159*t); // note t is in ms
}

// Sets cart position in inches
// User can write position/angle functions in units of degrees, inches, and milliseconds
void Set_Pos_And_Angles::Cart_Setpoint_At_t() {
Cart_Set_X = 0;
//Cart_Set_X = (double) 2*sin(1000*.5*2*3.14159*t); // A*sin(2*pi*1000*f*t) // note t is in ms
}
