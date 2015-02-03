//Author(s): Logan Traffas, Adrian Hardt
//For analogue output -- ***Note: change to PWM***
#include <iostream>
#include <vector>

using namespace std;

const float SUPPLIED_VOLTAGE=5.0;

float sensor_return(){
	float sensor_return=0.29298;
	return sensor_return;
}

double get_range(float SUPPLIED_VOLTAGE, float measured_voltage){
	return measured_voltage/(SUPPLIED_VOLTAGE/512);
}

int main(){
	float measured_voltage=0, range=0;
	measured_voltage=sensor_return();
	range=get_range(SUPPLIED_VOLTAGE, measured_voltage);
	cout<<range<<"in.";
	return 0;
}