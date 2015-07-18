#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <time.h> 
#include <assert.h>
#include <unistd.h>

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

	return !((p.y==1 && p.x==3) || (p.y==2 && p.x==3));

}

bool lastpointvalid(point p,vector<point> lp){
	
	bool valid = true;

	for (int i=0; i< (int)lp.size(); i++){
		if ( p == lp[i]){
			valid = false;
		}
	}
	return valid;
}

bool valid(point p){
	return (Walls(p) && bounderies(p));
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

void compValid(point l, vector<point> lp,twovectors & q){
	if (valid (l)){
		if (lastpointvalid(l,lp)){
			q.pref.push_back(l);
		}
		else{
			q.notpref.push_back(l);
		}	
	}
}
twovectors getpoint(point p,vector<point> lp){
	twovectors q;
	point l;

	l = leftp(p);

	compValid(l,lp,q);

	l = rightp(p);

	compValid(l,lp,q);

	l = upp(p);

	compValid(l,lp,q);

	l = downp(p);
	
	compValid(l,lp,q);
		
	return q;
}
int rando(int max){	
	return rand() % max;
}
vector<point> orderofpref(twovectors v){
	vector<point> p;
	if( v.pref.size() != 0){
		p = v.pref;
	}
	else{
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
	vector<point> location;
	
	srand(time(NULL));

	e.x=4;
	e.y=1;
	
	p.x=1;
	p.y=1;
	
	steps = 0;

	lastPoint.push_back(p);

	while (p != e){
		
		location.push_back(p);
		
		v=getpoint(p,lastPoint);

		cout << v.pref.size() << " preferred points and " << v.notpref.size() << " not preffered points" << endl;

		cout.flush();
		
		points = orderofpref(v);

		direction = rando(points.size());
		
		p = points[direction];

		lastPoint.push_back(p);
		
		cout << "got point:" << p << endl;
          cout << "potatoes and good << endl;
	
		cout << "step:" << location.size() << endl;
		
		cout << "last point " << location[steps] << endl;
		cout << "--------------------------------------------------------------------------------" << endl;

		steps++;
		
		sleep (1);

	}

	cout << "It took " << steps << " steps to reach the end" << endl;	
	
	return 0;
}
