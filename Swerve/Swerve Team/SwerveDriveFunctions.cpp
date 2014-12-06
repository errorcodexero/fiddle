#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

#define TITLE(A) cout<<""#A<<":\n";

using namespace std;

struct Point {
	float x;
	float y;
};

struct Wheel {
	Point location;
	float angle;
	float radius;
	float power;
};

struct Joystick {
	Point p;
	float theta;
};

Point operator -(Point point1, Point point2) {
	Point point3;
	point3.x = point1.x-point2.x;
	point3.y = point1.y-point2.y;
	return point3;
}

ostream & operator<<(ostream&o,Joystick js){
	o<<js.p.x<<"\n"<<js.p.y<<"\n"<<js.theta;
	return o;
}

float turnRad(Point wheel, Point point) {
	Point test = wheel-point; 
	return sqrt(test.x*test.x+test.y*test.y);
}

float wheelAngle(Point wheel, Point point) {
	Point test = wheel-point;
	return atan2(test.y,test.x)/(2*M_PI)*360+90;
}

float input(string prompt) {
	string geti;
	std::cout<<prompt<<": ";
	getline(cin,geti);
	std::cout<<"\n";
	float i = atof(geti.c_str());
	return i;
}

float wheelPower(float thisRadius, float maxRadius) {
	return (thisRadius/maxRadius)*100;
}

void wheelSetup(Wheel &wheel, float inX, float inY, Point cent_rotat) {
	wheel.location.x = inX;
	wheel.location.y = inY;
	wheel.radius = turnRad(wheel.location,cent_rotat);
	wheel.angle = wheelAngle(wheel.location,cent_rotat);
}

float maxRad(float Rad1, float Rad2, float Rad3) {
	float test = max(Rad1, Rad2);
	return max(test, Rad3);
}

int main(){
	Wheel joyStick;
	Point center;
	center.x = 0;
	center.y = 0;
	float J1X;
	float J1Y;
	float angleA;

	Joystick testA;
	testA.p.x = 0;
	testA.p.y = 0;
	testA.theta = 0;
	Joystick testB;
	testB.p.x = 1;
	testB.p.y = 1;
	testB.theta = 1;
	Joystick testC;
	testC.p.x = -1;
	testC.p.y = -1;
	testC.theta = -1;
	Joystick testD

	vector <Joystick> JoyTests;
	JoyTests.push_back(testA);
	JoyTests.push_back(testB);	
	JoyTests.push_back(testC);
	
	for(unsigned i = 0; i < JoyTests.size(); i++) {
		std::cout<<JoyTests[i]<<"\n";
		std::cout<<wheelAngle(JoyTests[i].p,center)<<"\n";
	}

	/**while (J1X != 0 || J1Y != 0) {
		J1X = input();
		J1Y = input();
		//float theta = input();
		wheelSetup(joyStick, -J1X, -J1Y, center);
		if (joyStick.angle < 0) {
			joyStick.angle = 360 + joyStick.angle;
		}
		//std::cout<<joyStick.angle<<"\n";
		if(joyStick.angle < 45) {
			angleA = joyStick.angle;
		}else if(joyStick.angle < 90) {
			angleA = 90 - joyStick.angle;
		}else if(joyStick.angle < 135) {
			angleA = joyStick.angle - 90;
		}else if(joyStick.angle < 180) {
			angleA = 180 - joyStick.angle;
		}else if(joyStick.angle < 225) {
			angleA = joyStick.angle - 180;
		}else if(joyStick.angle < 270) {
			angleA = 270 - joyStick.angle;
		}else if(joyStick.angle < 315) {
			angleA = joyStick.angle - 270;
		}else{
			angleA = 360 - joyStick.angle;
		}
		std::cout<<angleA<<"\n";
	}

	/**Point cent_rotat;
	cent_rotat.x = input();
	cent_rotat.y = input();
	Wheel wheel_left;
	wheelSetup(wheel_left,-14.6,8.5,cent_rotat);
	Wheel wheel_right;
	wheelSetup(wheel_right,14.6,8.5,cent_rotat);
	Wheel wheel_back;
	wheelSetup(wheel_back,0,-17,cent_rotat);
	float referenceMax = maxRad(wheel_left.radius,wheel_right.radius,wheel_back.radius);
	wheel_left.power = wheelPower(wheel_left.radius,referenceMax);
	wheel_right.power = wheelPower(wheel_right.radius,referenceMax);
	wheel_back.power = wheelPower(wheel_back.radius,referenceMax);
	
	//std::cout<<wheel_left.x<<" "<<wheel_left.y<<"\n";

	std::cout<<"Left wheel's turn radius: "<<wheel_left.radius<<"\n";
	std::cout<<"Left wheel's turn angle: "<<wheel_left.angle<<"\n";
	std::cout<<"Left wheel's power: "<<wheel_left.power<<"\n";
	std::cout<<"Right wheel's turn radius: "<<wheel_right.radius<<"\n";
	std::cout<<"Right wheel's turn angle: "<<wheel_right.angle<<"\n";
	std::cout<<"Right wheel's power: "<<wheel_right.power<<"\n";
	std::cout<<"Back wheel's turn radius: "<<wheel_back.radius<<"\n";
	std::cout<<"Back wheel's turn angle: "<<wheel_back.angle<<"\n";
	std::cout<<"Back wheel's power: "<<wheel_back.power<<"\n";**/
}
