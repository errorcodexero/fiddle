#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <time.h> 
#include <assert.h>

#define NYI {cout << "NYI " << __LINE__<<"\n"; exit(1);}
 

using namespace std;

struct point{
	int x;
	int y;
};
struct twovectors{
	vector<point> notpref;
	vector<point> pref;
};
bool operator!=(point a,point b){
	return (a.x != b.x || a.y != b.y);
}
ostream&operator<<(ostream& o, point a){
	
	o<< a.x << "," << a.y << endl;
	
	return o;
}

bool operator==(point a,point b){
	return (a.x == b.x && a.y == b.y);
}

bool bounderies(point p){
	bool xvalid = p.x>=1 && p.x<=4;
	bool yvalid = p.y>=1 && p.y<=3;

	return xvalid && yvalid;
}

bool Walls(point p){
	bool valid;

	valid = !((p.y==1 && p.x==3) || (p.y==2 && p.x==3));
	return valid;
}

bool lastpointvalid(point p,vector<point> lp){
	int valid;
	int i;
	
	valid = true;

	for (i=0; i< (int)lp.size(); i++){
	if ( p == lp[i]){
		valid = false;
	}
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
point leftp(point p){
	return point{p.x - 1,p.y};
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
vector<point> nearpoints(point p){
	vector<point> p;

	p.push_back(leftp(p));

	p.push_back(rightp(p));

	p.push_back(upp(p));

	p.push_back(downp(p));

	return p;
}
twovectors getpoint(point p,vector<point> lp){
	twovectors q;
	vector nowall;
	point b;

	b = nowall[0];
	
	if (valid(leftp(p))){
		nowall.push_back(left
		if (lastpointvalid(p,lp)){
			q.pref.push_back(leftp(p));
		}
		else{
			q.notpref.push_back(leftp(p));
		}	
	}
	if (valid(rightp(p))){
		if (lastpointvalid(p,lp)){
			q.pref.push_back(rightp(p));
		}
		else{
			q.notpref.push_back(rightp(p));
		}	
	}
	if (valid(upp(p))){
		if (lastpointvalid(p,lp)){
			q.pref.push_back(upp(p));
		}
		else{
			q.notpref.push_back(upp(p));
		}	
	}
	if (valid(downp(p))){
		if (lastpointvalid(p,lp)){
			q.pref.push_back(downp(p));
		}
		else{
			q.notpref.push_back(downp(p));
		}	
	}
	
	return q;
}
int rando(int max){
	int randnum;
	
	randnum = rand() % max;
	
	return randnum;
}
vector<point> orderofpref(twovectors v){
	vector<point> p;
	if( v.pref.size() != 0){
		p = v.pref;
	}
	else if( v.pref.size() == 0){
		p = v.notpref;
	}
	assert(p.size() != 0);
	
	return p;
}

int main(){
	
	point p;
	point e;
	int steps;
	int direction;
	twovectors v;
	vector<point> lastPoint;
	vector<point> points;
	
	srand(time(NULL));points = orderofpref(v);

	e.x=4;
	e.y=1;
	
	p.x=1;
	p.y=1;
	
	steps = 0;

	lastPoint.push_back(p);

	while (p != e){
	
		v=getpoint(p,lastPoint);
			
		points = orderofpref(v);
		

		direction = rando(points.size());
		
		
		p = points[direction];

		lastPoint.push_back(p);
		
		cout << "got point:" << p << endl;
		
		steps++;
	}

	cout << "It took " << steps << " steps to reach the end" << endl;	
	
	return 0;
}
