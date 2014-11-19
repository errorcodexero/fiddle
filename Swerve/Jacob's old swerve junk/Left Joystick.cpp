// This program is the left joystick input.
// The left joystick controls the direction all wheels point in, in relation to the front of the robot.
// Rotation from the right joystick makes the wheels rotate so the robot rotates clockwise or counter clockwise, in relation to its center point.



#include<iostream>
#include<vector>
#include<math.h>
#include<sstream>

using namespace std;

//degree = 180/pi ////radians = pi/180
float degreesradians(float degrees){ //Give it a degree to receive it in radians.
	float radians = degrees * M_PI/180;
	return radians;
}

float radiansdegrees(float radians){ //Give it a radian to receive it in degrees.
	float degrees = radians * 180/M_PI;
	return degrees;
}

void findLeftJoyDegree(float joy_x, float joy_y){
	float theta=0;
	if(joy_x < 0 && joy_y < 0){
		atan2(joy_y/joy_x);
	}
}


void main(){
	float left_joystick_x;
	float left_joystick_y;
	
}
