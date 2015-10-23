#include<iostream>
using namespace std;

float calcTPL(float fl, float ts){
	//calculate time per length traveled
	//returns time in seconds;
	return fl / ts;
}

float calcTPW(float fw, float ts){
	//calculate time per width traveled
	//returns time in seconds
	return fw / ts;
}

int calcLPM(float gametime, float ts, float fl){
	//calculate lengths traveled per match
	//returns number of whole lengths
	float lap = 0;
	float y;
	float z;
	while(gametime != 0){
		y = calcTPL(fl, ts);
		lap++;
		gametime = gametime - y;
		if(gametime < 0){
			gametime = 0;
			lap = lap - 1;
		}
	}
	return lap;
}



int calcLPM(float gametime, float ts, float rs, float fl){
	//calculate lengths traveled per match ADVANCED VERSION
		//ADVANCED: Includes the rotation time at the end of the field
	//returns number of whole lengths
	float lap = 0;
	float x;
	float y;
	float z;
	while(gametime != 0){
		x = (rs/2); //time of 180 rotation
		y = calcTPL(fl, ts);
		y = y + x;
		lap++;
		gametime = gametime - y;
		if(gametime < 0){
			gametime = 0;
			lap = lap - 1;
		}
	}
	return lap;
}

float calcPrTT(float fl, float fw, float ts){
	//calculates time to travel the primeter
	//returns time in seconds
	
	float y = calcTPL(fl, ts);
	float z = calcTPW(fw, ts);

	float prim = y + y + z + z;
	return prim;
}


float calcPrTT(float fl, float fw, float ts, float rs){
	//calculates time to travel the primeter ADVANCED VERSION
		//ADVANCED: Includes the rotation time at end of field
	//returns time in seconds
	
	float y = calcTPL(fl, ts);
	float z = calcTPW(fw, ts);

	float prim = y + y + z + z + rs; 
	return prim;
}

void setVar(float& var, float input){
	var = input;
}

void setVar(int& var, int input){
	var = input;
}

int main(){
	float gametime = 0; //0 seconds
	float fl = 54; //field length = 54'
	float fw = 0; //field width = 0'
	float ts = 5; //travel speed = 5'/s
	float rs = 0; //0 seconds per rotation
	int ngp = 0; //number of game pieces
}

//system("xterm -e **);
//* = any terminal command to be run in the second terminal

