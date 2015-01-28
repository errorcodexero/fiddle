#include <iostream>

#define MaxLiftHeight 182.88 //six feet
#define MinLiftHeight 5.0 //minimum lift height above ground
#define MaxLevel 15.875 + (double(3) * 30.734) + 73.66 //step + 3 totes + can
#define MinLevel 0.0 //ground

using namespace std; 

class Height { //centimeters
	public:
		double ground = 0,
			   platform = 5.08,
			   step = 15.875,
			   tote = 30.734,
			   can = 73.66,
			   toteTolerance = 10,  //tolerance from the top of the tote
			   canTolerance = 30;   //tolerance from the top of the can
	
	private:
		
};

int mapToLiftLevel(int level, int minLevel, int maxLevel, int minLiftHeight, int maxLiftHeight) {
	return (level - minLevel) * (maxLiftHeight - minLiftHeight) / (maxLevel - minLevel) + minLiftHeight;
}

int mapToLiftLevel(int level, double minLevel, double maxLevel, double minLiftHeight,double maxLiftHeight) {
	return (level - minLevel) * (maxLiftHeight - minLiftHeight) / (maxLevel - minLevel) + minLiftHeight;
}

int getLiftHeight(int nTote, int base, int can = 0) {
	Height height;
	int heightLevel = (height.tote * nTote) + (height.can * can) + base - (can * height.canTolerance);
	
	if (nTote != 0) {
		heightLevel -= height.toteTolerance;
	}
	
	return mapToLiftLevel(heightLevel, MinLevel, MaxLevel, MinLiftHeight, MaxLiftHeight);
}