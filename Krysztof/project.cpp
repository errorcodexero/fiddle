#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>
using namespace std;

struct point {
	int x, y;
}start, end;
struct maze2d {
};	
int main () {
	srand(time(0));
	start.x=rand()%10;
	start.y=rand()%10;
	end.x=rand()%10;
	end.y=rand()%10;
	cout<<"Start"<<" "<<start.x<<","<<start.y<<endl;
	if (start.x<end.x) {
		cout<<"Go right"<<" "<<(end.x-start.x)<<" "<<"times."<<endl;
	} 
	else if (start.x>end.x) {
		cout<<"Go left"<<" "<<(start.x-end.x)<<" "<<"times."<<endl;
	} 
	if (start.y<end.y) {
		cout<<"Go up"<<" "<<(end.y-start.y)<<" "<<"times."<<endl;
	}
	else if (start.y>end.y) {
		cout<<"Go right"<<" "<<(start.y-end.y)<<" "<<"times."<<endl;
	}
	cout<<"End"<<" "<<end.x<<","<<end.y<<endl;
	return 0;
}
