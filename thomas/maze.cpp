#include <iostream>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
using namespace std;

struct point {
	int x;
	int y;
};

int main(){
	vector<vector<int>> maze{
		{0,0,1,0},
		{0,0,1,0},
		{0,0,0,0}
	};
	point bob;
	bob.x=0;
	bob.y=0;
	
	point goal;
	goal.x=4;
	goal.y=0;

	while(true){
		if (bob.x<goal.x){
			bob.x++;
			cout<<"move right/n";
		} else if(bob.x>goal.x){
			bob.x--;
			cout<<"move left/n";
		}
	}
}
