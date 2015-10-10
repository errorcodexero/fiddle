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

int calcLPM_A(float gametime, float ts, float rs, float fl){
	//calculate lengths traveled per match AVANCED VERSION
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

float calcPrTT_A(float fl, float fw, float ts, float rs){
	//calculates time to travel the primeter ADVANCED VERSION
	//returns time in seconds
	
	float y = calcTPL(fl, ts);
	float z = calcTPW(fw, ts);

	float prim = y + y + z + z + rs; 
	return prim;
}

int main(){
	float gametime = 0; //0 seconds
	float fl = 54; //field length = 54'
	float fw = 0; //field width = 0'
	float ts = 5; //travel speed = 5'/s
	float rs = 0; //0 seconds per rotation
	
}

//system("xterm -e **);
//* = any terminal command to be run in the second terminal

