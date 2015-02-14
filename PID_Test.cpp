#include <iostream>
#include <stdio.h>
#include <cmath>
//#include "liftHeight.cpp"

using namespace std;

/*
SetPoint: How high I want the lift to go
PID Controller: Calculates how much the lift should move (power)
Controller Input: The value that the PID Controller gives
Disturbances: Weight on lift; Snags in chain; Momentum
Process: Speed that lift will go to change its height
Measured Process Variable: Speed of lift
Process Variable: Current height of lift
Sensor: Encoders

											  Disturbances
												   ↓
Set_Point → PID_Controller → Controller_Input → Process → Process_Variable
				  ↑							   	  				 ↓
		Measured_Process_Variable   ←   ←	←	←	←	←  ←   Sensor



		  → → Error (SP - PV) → → Proportional → → 
		  ↑										 ↑
Set_Point → → Error (SP - PV) → → Integral → → → → → Add all Three (Or all Used) → → Controller_Input
		  ↓										 ↑
		  → → Error (SP - PV) → → Derivative → → →
*/

struct PID_Controller {
	double p = 0.01, //Proportional
		   i = 0.01, //Integral
		   d = 0.0; //Derivative
};

double Proportional(double error, PID_Controller pid) {
	return pid.p * error;
}

double Integral(double error, PID_Controller pid, double rate, double integral) {
	integral += rate * error;
	
	return integral * pid.i;
}

double Derivative(double error, PID_Controller pid) {
	
	return 0.0;
}

PID_Controller PID(double error, PID_Controller pid, double rate, double integral) {
	PID_Controller test;
	test.p = Proportional(error, pid);
	test.i = Integral(error, pid, rate, integral);
	test.d = Derivative(error, pid);
	
	return test;
}

#ifdef TEST_PID

int main() {
	int currentHeight = 0,
		desiredHeight = 0;
	double set_point = 0.0,
		   controller_input = 0.0,
		   disturbances = 0.0,
		   measured_process_variable = 0.0,
		   process = 0.0,
		   process_variable = 0.0,
		   error = 0.0,
		   power = 0.0,
		   integral = 0.0;
	PID_Controller original,
				   value;
	
	cout << endl << "Enter current height (0 - 100): ";
	cin >> currentHeight;
	cout << "Enter desired height(0 - 100): ";
	cin >> desiredHeight;
	
	set_point = desiredHeight;
	process_variable = currentHeight;
	
	for(int i = 0; i < 30; i++)	{
		error = set_point - process_variable;
		value = PID(error, original, 1.0, integral);
		integral += value.i;
		power = value.p + value.i + value.d;
		
		process_variable > set_point ? power = -original.p : power = original.p;
		power >= 0 ? process_variable++ : process_variable--;
		
		cout << endl << "Time Step: " << i << endl << "Error: " << error << endl << "Power: " << power << endl << "Current Height: " << process_variable << endl;
	}
	
	return 0;
}

#endif