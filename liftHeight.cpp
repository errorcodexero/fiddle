#include <iostream>
#include <string>
#include "liftHeight.h"

using namespace std; 

int intCan(string c) {
	return (c[0] == 'Y' || c[0] == 'y') ? 1 : 0;
}

int intBase(string b) {
	Height base;
	
	if (b[0] == 'G' || b[0] == 'g') {
		return base.ground;
	}
	else if (b[0] == 'P' || b[0] == 'p') {
		return base.platform;
	}
	else if (b[0] == 'S' || b[0] == 's') {
		return base.step;
	}
}

int main(){
	int nTote = 0;
	string base = "",
		   can = "";
	
	cout << endl << "Enter number of totes (0-3): ";
	cin >> nTote;
	cout << "Enter the base (Ground/Platform/Step): ";
	cin >> base;
	cout << "Is can on the stack? (Y/N) ";
	cin >> can;
	
	cout << endl << "Lift height will be " << getLiftHeight(nTote, intBase(base), intCan(can)) << " centimeters.";
	
	return 0;
}