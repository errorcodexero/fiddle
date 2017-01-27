#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

struct point {
	int x, y;
}start, end;

const int X_LENGTH = 20, Y_LENTGH = 20;

int wall[] ={0,1};

void print_maze(point start, point end) {
	for (int x=0; start.x>X_LENGTH; x++) {
	cout<<endl;	
	if (int x=0; start.x<X_LENGTH; x++) {
		cout<<rand()%1;
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
