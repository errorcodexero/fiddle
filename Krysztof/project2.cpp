#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <vector>

using namespace std;

struct point {
	int x, y;
}start, end;	
const int X_LENGTH = 20, Y_LENGTH = 20;
void print_maze(point start, point end, vector <point> visited){	
	for(int y = 0; y<Y_LENGTH; y++){
		string row="";
		for(int x = 0; x<X_LENGTH; x++){		
			if(y == start.y && x == start.x) {
				row+="S";
			}
			else if (y ==end.y && x == end.x) {
				row+="E";
			}
			else {
				bool unvisited=true;
				for(int i=0; i<visited.size(); i++) {
					point p=visited[i];
					if(y==p.y && x==p.x) {
						row+=" ";
						unvisited=false;
					}
				}
				if (unvisited)row+="x";
			}

		}
		cout<<row<<endl;
	}
}
int main () {
	vector <point> visited;
	srand(time(0));
	start.x=rand()%X_LENGTH;
	start.y=rand()%X_LENGTH;
	end.x=rand()%X_LENGTH;
	end.y=rand()%X_LENGTH;
	cout<<"Start"<<" "<<start.x<<","<<start.y<<endl;
	if (start.x<end.x) {
		for (int i=start.x; i<end.x; i++) {
			point p;
			p.x=i;
			p.y=start.y;
			visited.push_back(p);	
		}
		cout<<"Go right"<<" "<<(end.x-start.x)<<" "<<"times."<<endl;
	} 
	else if (start.x>end.x) {
		for (int i=start.x; i>end.x; i--) {
			point p;
			p.x=i;
			p.y=start.y;
			visited.push_back(p);	
		}
		cout<<"Go left"<<" "<<(start.x-end.x)<<" "<<"times."<<endl;
	} 
	if (start.y<end.y) {
		for (int i=end.y; i>=start.y; i--) {
			point p;
			p.y=i;
			p.x=end.x;
			visited.push_back(p);	
		}
		cout<<"Go down"<<" "<<(end.y-start.y)<<" "<<"times."<<endl;
	}
	else if (start.y>end.y) {
		for (int i=end.y; i<=start.y; i++) {
			point p;
			p.y=i;
			p.x=end.x;
			visited.push_back(p);	
		}
		cout<<"Go up"<<" "<<(start.y-end.y)<<" "<<"times."<<endl;
	}
	cout<<"End"<<" "<<end.x<<","<<end.y<<endl;
		print_maze(start,end,visited);
	return 0;
}
