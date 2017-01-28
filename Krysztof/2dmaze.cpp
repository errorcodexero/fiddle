#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
using namespace std;

struct point {
	int x, y;
} start, end;
 const int X_LENGTH = 10, Y_LENGTH = 10;

int p [] = {0, 20};

void print_maze (point start, point end) {
	for(int y = 0; y<Y_LENGTH; y++){
		for(int x = 0; x<X_LENGTH; x++)
		if(y == start.y && x == start.x) cout<<"S";
		else if (y ==end.y && x == end.x) cout<<"E";
		for(y == p[0]) cout<<"T";
		cout<<endl;
	}
}

int main () {
	srand(time(0));
	start.x=rand()%X_LENGTH;	
	start.y=rand()%Y_LENGTH;
	end.x=rand()%X_LENGTH;
	end.y=rand()%Y_LENGTH;
	cout<<"Start: "<<start.x<<", "<<start.y<<endl;
	print_maze(start, end);
	return 0;
}
