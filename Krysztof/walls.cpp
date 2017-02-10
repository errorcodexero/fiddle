#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <vector>

using namespace std;

struct point {
	int x, y;
};	
const int X_LENGTH = 20, Y_LENGTH = 20;
point a() {
	point z;
	z.x=rand()%X_LENGTH;
	z.y=rand()%Y_LENGTH;
	return z;
}
vector <point> visited;
vector <point> find_path(point p1, point p2) {
	
	if (p1.x<p2.x) {
		for (int i=p1.x; i<p2.x; i++) {
			point p;
			p.x=i;
			p.y=p1.y;
			visited.push_back(p);
		}
		cout<<"Go right "<<(p2.x-p1.x)<<" times"<<endl;
	}
	else if (p1.x>p2.x) {
		for (int i=p1.x; i>p2.x; i--) {
			point p;
			p.x=i;
			p.y=p1.y;
			visited.push_back(p);
		}
		cout<<"Go left "<<(p1.x-p2.x)<<" times"<<endl;
	}
	if (p1.y<p2.y) {
		for (int i=p1.y; i<p2.y; i++) {
			point p;
			p.y=i;
			p.x=p2.x;
			visited.push_back(p);
		}
		cout<<"Go down "<<(p2.y-p1.y)<<" times"<<endl;
	}
	else if (p1.y>p2.y) {
		for (int i=p1.y; i>p2.y; i--) {
			point p;
			p.y=i;
			p.x=p2.x;
			visited.push_back(p);
		}
		cout<<"Go up "<<(p1.y-p2.y)<<" times"<<endl;
	}
	return visited;
}

void print_maze(point start,point mid, point end, vector <point> walls, vector <point> visited){	
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
				for(unsigned i=0; i<visited.size(); i++) {
					point p=visited[i];					
					if(y==p.y && x==p.x) {
						row+="-";
						unvisited=false;
					}
				}
				bool iswall=false;
				for(unsigned i=0; i<walls.size(); i++) {
					point p=walls[i];					
					if(y==p.y && x==p.x) {
						row+="x";
						iswall=true;
					}
				}
				if (unvisited && !iswall)row+=" ";

			}
		}
		cout<<row<<endl;
	}
}
int main () {
	point start, mid, end;
	vector <point> walls;
	srand(time(0));
	for (int x = 2; x<X_LENGTH;x++) {
		walls.push_back({x,5});
	}
	start=a();
	mid=a();
	end=a();
	cout<<"Start"<<" "<<start.x<<","<<start.y<<endl;
	find_path(start,mid);
	find_path(mid,end); 
	cout<<"End"<<" "<<end.x<<","<<end.y<<endl;
		print_maze(start,mid,end,walls,visited);
	return 0;
}
