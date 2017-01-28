#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

struct point {
	int x, y;
}start, end;

const int X_LENGTH = 20, Y_LENGTH = 20;

int wall[] ={0,1};

void print_maze(point start, point end){	
	for(int y = 0; y<Y_LENGTH; y++){
		for(int x = 0; x<X_LENGTH; x++)
		if(y == start.y && x == start.x) cout<<"S";
		else if (y ==end.y && x == end.x) cout<<"E";
		else 
		cout<<endl;
	}
}
int main() {
	srand(time(0));
	start.x=rand()%X_LENGTH;
	start.y=rand()%X_LENGTH;
	end.x=rand()%X_LENGTH;
	end.y=rand()%X_LENGTH;
	print_maze(start, end);
	return 0;
}
