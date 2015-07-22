

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

vector<point> getpoint(point p,vector<point> lp){
	vector<points> q;
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


int main(){
vector<point> a;
vector<point> b:
}
