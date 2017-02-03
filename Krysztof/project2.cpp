#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <vector>

using namespace std;

struct point {
	int x, y;
}start, end, mid;	
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
	start.y=rand()%Y_LENGTH;
	for (int i = 0; i<rand()%20; i++) {
		mid.x=rand()%X_LENGTH;
		mid.y=rand()%Y_LENGTH;
	}
	end.x=rand()%X_LENGTH;
	end.y=rand()%X_LENGTH;
	cout<<"Start"<<" "<<start.x<<","<<start.y<<endl;

	if (start.x<mid.x) {
		for (int i=start.x; i<mid.x; i++) {
			point p;
			p.x=i;
			p.y=start.y;
			visited.push_back(p);	
		}
		cout<<"Go right"<<" "<<(mid.x-start.x)<<" "<<"times."<<endl;
	} 
	else if (start.x>mid.x) {
		for (int i=start.x; i>mid.x; i--) {
			point p;
			p.x=i;
			p.y=start.y;
			visited.push_back(p);	
		}
		cout<<"Go left"<<" "<<(start.x-mid.x)<<" "<<"times."<<endl;
	}
	if (start.y<mid.y) {
		for (int i=mid.y; i>=start.y; i--) {
			point p;
			p.y=i;
			p.x=mid.x;
			visited.push_back(p);	
		}
		cout<<"Go down"<<" "<<(mid.y-start.y)<<" "<<"times."<<endl;
	}
	else if (start.y>mid.y) {
		for (int i=mid.y; i<=start.y; i++) {
			point p;
			p.y=i;
			p.x=mid.x;
			visited.push_back(p);	
		}
		cout<<"Go up"<<" "<<(start.y-mid.y)<<" "<<"times."<<endl;
	}	
	if (mid.x<end.x) {
		for (int i=mid.x; i<end.x; i++) {
			point p;
			p.x=i;
			p.y=mid.y;
			visited.push_back(p);	
		}
		cout<<"Go right"<<" "<<(end.x-mid.x)<<" "<<"times."<<endl;
	} 
	else if (mid.x>end.x) {
		for (int i=mid.x; i>end.x; i--) {
			point p;
			p.x=i;
			p.y=mid.y;
			visited.push_back(p);	
		}
		cout<<"Go left"<<" "<<(mid.x-end.x)<<" "<<"times."<<endl;
	} 

	if (mid.y<end.y) {
		for (int i=end.y; i>=mid.y; i--) {
			point p;
			p.y=i;
			p.x=end.x;
			visited.push_back(p);	
		}
		cout<<"Go down"<<" "<<(end.y-mid.y)<<" "<<"times."<<endl;
	}
	else if (mid.y>end.y) {
		for (int i=end.y; i<=mid.y; i++) {
			point p;
			p.y=i;
			p.x=end.x;
			visited.push_back(p);	
		}
		cout<<"Go up"<<" "<<(mid.y-end.y)<<" "<<"times."<<endl;
	}
	cout<<"End"<<" "<<end.x<<","<<end.y<<endl;
		print_maze(start,end,visited);
	return 0;
}
