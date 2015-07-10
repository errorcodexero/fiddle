#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <time.h> 

#define NYI {cout << "NYI " << __LINE__<<"\n"; exit(1);}
 

using namespace std;

struct point{
	int x;
	int y;
};
bool operator!=(point a,point b){
	return (a.x != b.x || a.y != b.y);
}
ostream&operator<<(ostream& o, point a){
	
	o<< a.x << "," << a.y << endl;
	
	return o;
}
bool bounderies(point p){
	bool xvalid;
	bool yvalid;

	if(p.x>=1 && p.x<=4){
		xvalid = true;

	}else
		xvalid = false;
	
	if(p.y>=1 && p.y<=3){
		yvalid = true;
	}else{
		yvalid = false;
		
	}
	return xvalid && yvalid;
}

bool Walls(point p){
	bool valid;

	if(p.y==1 && p.x==3){
		valid = false;
	}else if(p.y==2 && p.x==3){
		valid = false;
	}else{
		valid = true;
		
			
	}
	return valid;
}

bool valid(point p){
	if(Walls(p) && bounderies(p)){
		return true;
	}
	else{
		return false;
	}
}
int getnum(){
	string s;
	cout<<"Enter a value for an x,y for the start and end points"<<endl;
	getline(cin,s);

	return atoi(s.c_str());
}
point leftp(point p){
	return point{p.x-1,p.y};
}

point rightp(point p){
	return point{p.x + 1,p.y};
}

point upp(point p){
	return point{p.x,p.y + 1};
}

point downp(point p){
	return point{p.x,p.y - 1};
}

vector<point> getpoint(point p){
	vector<point> v;
	if (valid(leftp(p))){
		v.push_back(leftp(p));
	}
	if (valid(rightp(p))){
		v.push_back(rightp(p));
	}

	if (valid(upp(p))){
		v.push_back(upp(p));
	}
	
	if (valid(downp(p))){
		v.push_back(downp(p));
	}
	return v;
}
int rando(int max){
	int randnum;
	
	randnum = rand() % max;
	
	return randnum;
}

	
int main(){
	
	point p; //declare a point type called p
	point e;
	int steps;
	int direction;
	vector<point> v;
	
	srand(time(NULL));

	e.x=4;
	e.y=1;
	
	p.x=1;
	p.y=1;
	
	steps = 0;
	
	while (p != e){
	
		v=getpoint(p);
		direction = rando(v.size());
		
		
		p = v[direction];
		
		cout << "got point:" << p << endl;
		
		steps++;
	}

	cout << "It took " << steps << " steps to reach the end" << endl;	
	
	return 0;
}











