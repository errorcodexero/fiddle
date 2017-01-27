#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>
using namespace std;

struct point {
	int x, y;
}start, end;	
const int X_LENGTH = 20, Y_LENGTH = 20;
void print_maze(point start, point end){	
	for(int y = 0; y<Y_LENGTH; y++){
		for(int x = 0; x<X_LENGTH; x++)
		if(y == start.y && x == start.x) cout<<"S";
		else if (y ==end.y && x == end.x) cout<<"E";
		else cout<<"X";
		cout<<endl;
	}
}
int main () {
	srand(time(0));
	start.x=rand()%X_LENGTH;
	start.y=rand()%X_LENGTH;
	end.x=rand()%X_LENGTH;
	end.y=rand()%X_LENGTH;
	cout<<"Start"<<" "<<start.x<<","<<start.y<<endl;
	print_maze(start,end);
	if (start.x<end.x) {
		cout<<"Go right"<<" "<<(end.x-start.x)<<" "<<"times."<<endl;
	} 
	else if (start.x>end.x) {
		cout<<"Go left"<<" "<<(start.x-end.x)<<" "<<"times."<<endl;
	} 
	if (start.y<end.y) {
		cout<<"Go down"<<" "<<(end.y-start.y)<<" "<<"times."<<endl;
	}
	else if (start.y>end.y) {
		cout<<"Go up"<<" "<<(start.y-end.y)<<" "<<"times."<<endl;
	}
	cout<<"End"<<" "<<end.x<<","<<end.y<<endl;
	return 0;
}
