#include <iostream>

#define MAX_LIFT_HEIGHT 182.88 //six feet
#define MIN_LIFT_HEIGHT 5.0 //minimum lift height above ground
#define MAX_LEVEL 15.875 + (double(3) * 30.734) + 73.66 //step + 3 totes + can
#define MIN_LEVEL 0.0 //ground


struct Height { //centimeters
	const double ground = 0,
		   platform = 5.08,
		   step = 15.875,
		   tote = 30.734,
		   can = 73.66,
		   toteTolerance = 10,  //tolerance from the top of the tote
		   canTolerance = 30;   //tolerance from the top of the can
		
};

int mapToLiftLevel(int level, double minLevel, double maxLevel, double minLiftHeight,double maxLiftHeight) {
	return (level - minLevel) * (maxLiftHeight - minLiftHeight) / (maxLevel - minLevel) + minLiftHeight;
}

int getLiftHeight(int nTote, int base, int can = 0) {
	Height height;
	int heightLevel = (height.tote * nTote) + (height.can * can) + base - (can * height.canTolerance);
	
	if (nTote != 0) {
		heightLevel -= height.toteTolerance;
	}
	
	return mapToLiftLevel(heightLevel, MIN_LEVEL, MAX_LEVEL, MIN_LIFT_HEIGHT, MAX_LIFT_HEIGHT);
}