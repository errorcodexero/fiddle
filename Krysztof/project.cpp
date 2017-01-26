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
	cout<<"start"<<" "<<start.x<<","<<start.y<<endl;
	if (start.x<end.x) {
		cout<<string(end.x-start.x, 'R')<<endl;
	} 
	else if (start.x>end.x) {
		cout<<string(start.x-end.x, 'L')<<endl;
	} 
	if (start.y<end.y) {
		cout<<string(end.y-start.y, 'U')<<endl;
	}
	else if (start.y>end.y) {
		cout<<string(start.y-end.y, 'D')<<endl;
	}
	cout<<"end"<<" "<<end.x<<","<<end.y<<endl;
	return 0;
}
