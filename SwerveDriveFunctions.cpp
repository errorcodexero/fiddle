#include <iostream>
#include <math.h>

float distance(float wheelX,float wheelY,float pointX,float pointY) {
	int dX = pointX-wheelX;
	int dY = pointY-wheelY;
	return sqrt(dX*dX+dY*dY);
}

float wheelAngle(float wheelX,float wheelY,float pointX,float pointY) {
	int dX = pointX-wheelX;
	int dY = pointY-wheelY;
	return atan2(dY,dX)/(2*M_PI)*360+90;
}

float wheelsPos() {
//calculate the possition of the wheels
}

int main(){
	float X1 = 0;
	float Y1 = 0;
	float X2 = -100;
	float Y2 = 100;
	std::cout<<distance(X1,Y1,X2,Y2)<<"\n";
	std::cout<<wheelAngle(X1,Y1,X2,Y2)<<"\n";
}
