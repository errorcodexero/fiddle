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

float definedegree(float theta){
	
}

void main(){
	float theta = 45; //degrees
}