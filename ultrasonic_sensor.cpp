//Author(s): Logan Traffas, Adrian Hardt
//For PWM output
#include <iostream>
#include <vector>

using namespace std;

double get_pulse_width(){//In microseconds
	double pulse_width=13230;//Change to actual values
	return pulse_width;
}

double get_range(float pulse_width){
	return pulse_width/147;
}

int main(){
	float pulse_width=get_pulse_width();
	float range=get_range(pulse_width);
	cout<<range;
	return 0;
}