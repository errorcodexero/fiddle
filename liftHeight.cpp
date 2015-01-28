#include <iostream>
#include <string>
#include "liftHeight.h"

using namespace std; 

int intCan(string c) {
	int can = 0;
	
	if (c[0] == 'Y' || c[0] == 'y') {
		can = 1;
	}
	
	return can;
}

int intBase(string b) {
	Height base;
	int height = 0;
	
	if (b[0] == 'G' || b[0] == 'g') {
		height = base.ground;
	}
	else if (b[0] == 'P' || b[0] == 'p') {
		height = base.platform;
	}
	else if (b[0] == 'S' || b[0] == 's') {
		height = base.step;
	}
	
	return height;
}

int main(){
	int nTote = 0,
		liftHeight;
	string base,
		   can;
	
	cout << endl << "Enter number of totes (0-3): ";
	cin >> nTote;
	
	cout << "Enter the base (Ground/Platform/Step): ";
	cin >> base;
	
	cout << "Is can on the stack? (Y/N) ";
	cin >> can;
	
	liftHeight = getLiftHeight(nTote, intBase(base), intCan(can));
	
	cout << endl << "Lift height will be " << liftHeight << " centimeters.";
	
	return 0;
}