#include <iostream>
#include <string>

#define MAX_LIFT_HEIGHT 72 //six feet
#define MIN_LIFT_HEIGHT 2.0 //minimum lift height above ground
#define MAX_LEVEL 6.25 + (double(3) * 12.1) + 29 //step + 3 totes + can
#define MIN_LEVEL 0.0 //ground

using namespace std; 

struct Height { //inches
	double ground = 0,
		   platform = 2,
		   step = 6.25,
		   tote = 12.1,
		   can = 29,
		   toteTolerance = 4,  //tolerance from the top of the tote
		   canTolerance = 12;  //tolerance from the top of the can
		
};

double mapToLiftLevel(int level, double minLevel, double maxLevel, double minLiftHeight,double maxLiftHeight) {
	return (level - minLevel) * (maxLiftHeight - minLiftHeight) / (maxLevel - minLevel) + minLiftHeight;
}

double getLiftHeight(int nTote, int base, int can = 0) {
	Height height;
	double heightLevel = (height.tote * nTote) + (height.can * can) + base - (can * height.canTolerance);
	
	if (nTote != 0) {
		heightLevel -= height.toteTolerance;
	}
	
	return mapToLiftLevel(heightLevel, MIN_LEVEL, MAX_LEVEL, MIN_LIFT_HEIGHT, MAX_LIFT_HEIGHT);
}

bool intCan(string c) {
	return c[0] == 'Y' || c[0] == 'y' && (c.length() != 0 || c[0] == '\n');
}

int intBase(string b) {
	Height base;
	
	if (b.length() != 0 || b[0] == '\n') {
		if (b[0] == 'P' || b[0] == 'p') {
			return base.platform;
		}
		else if (b[0] == 'S' || b[0] == 's') {
			return base.step;
		}
	}
	
	return base.ground;
}

int main(){
	int nTote = 0;
	string base,
		   can;
	
	cout << endl << "Enter number of totes (0-3): ";
	cin >> nTote;
	cout << "Enter the base (Ground/Platform/Step): ";
	cin >> base;
	cout << "Is can on the stack? (Y/N) ";
	cin >> can;
	
	cout << endl << endl << "Lift height will be " << getLiftHeight(nTote, intBase(base), intCan(can)) << " inches.";
	
	return 0;
}