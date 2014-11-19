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

void defineRobotVector(float ltheta, float lvelocity, float rtheta, float rvelocity, float btheta, float bvelocity){
	float lx = lvelocity*cos(ltheta);
	float ly = lvelocity*sin(ltheta);
	float rx = rvelocity*cos(rtheta);
	float ry = rvelocity*sin(rtheta);
	float bx = bvelocity*cos(btheta);
	float by = bvelocity*sin(btheta);
	float Ux = (lx + rx + bx)/3;
	float Uy = (ly + ry + by)/3;
	float Utheta = atan2(Uy, Ux);
	float Uvectorsqr = pow(Ux, 2) + pow(Uy, 2);
	float Uvector = sqrt(Uvectorsqr);
	
	float Dtheta = radiansdegrees(Utheta);
	
	cout<<Dtheta<<"	"<<Uvector<<"\n";
}

/*float defineTheta(float theta_one, float theta_two, theta_six){
	float theta_three; //Theta used in math
	float theta_four; //Theta used in math
	float theta_five; //Theta is bisector of theta_one and theta_two.
	float theta_seven; //Theta used in math.
	float theta_eight; //Theta used in math.
	float theta_nine; // Theta defines the robot's direction of motion
	
	if(abs(theta_one) > abs(theta_two)){
		theta_three = theta_one - theta_two;
		theta_four = theta_three / 2;
		theta_five = theta_four + theta_two;
	}else if(abs(theta_one) < abs(theta_two)){
		theta_three = theta_two - theta_one;
		theta_four = theta_three / 2;
		theta_five = theta_four + theta_one;
	}else{
		theta_five = theta_one;
	}
	if(abs(theta_five) > abs(theta_six)){
		theta_seven = theta_five - theta_six;
		theta_eight = theta_seven / 2;
		theta_nine = theta_eight + theta_six;
	}else if(abs(theta_five) < abs(theta_six)){
		theta_seven = theta_six - theta_five;
		theta_eight = theta_seven / 2;
		theta_nine = theta_eight + theta_five;
	}else{
		theta_nine = theta_five;
	}
	
	return theta_nine;
	
}*/

int main(){
	float ltheta = degreesradians(60);
	float lvelocity = 10;
	float rtheta = degreesradians(-60);
	float rvelocity = 10;
	float btheta = degreesradians(180);
	float bvelocity = 10;
	//float Utheta = defineTheta(ltheta, rtheta, btheta);
	
	
	defineRobotVector(ltheta, lvelocity, rtheta, rvelocity, btheta, bvelocity);
}