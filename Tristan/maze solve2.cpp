

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
struct list{
point pt;
point prev;
bool v;
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


bool lastpointvalid(point p,vector<point> lp){
	
	bool valid = true;

	for (int i=0; i< (int)lp.size(); i++){
		if ( p == lp[i]){
			valid = false;
		}
	}
	return valid;
}

/////////////////////////////////////////////////////////////////////////////
// bounderies
//
// returns true if p is in the grid
/////////////////////////////////////////////////////////////////////////////
bool bounderies(point p){
	bool xvalid = p.x>=1 && p.x<=4;
	bool yvalid = p.y>=1 && p.y<=3;

	return xvalid && yvalid;
}

//////////////////////////////////////////////////////////////////////////////
// Walls
//
// returns true if p is not a wall
//////////////////////////////////////////////////////////////////////////////
bool Walls(point p){

	return !((p.y==1 && p.x==3) || (p.y==2 && p.x==3));

}

/////////////////////////////////////////////////////////////////////////////
// valid																   
//																		   
// returns true if p is not a wall or boundry                              
/////////////////////////////////////////////////////////////////////////////
bool valid(point p){
	return (Walls(p) && bounderies(p));
}
bool validpoint(vector<list> v,point q){
	int i;
	int max;
	bool p ;

	p=false;
	max = v.size();
	for(i=0; i<max; i++){
		if(v[i].pt == q){
			p = true;  // got it
			break;
		}
		
	}
	return valid(q) & !p;
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

int lastp(vector<list> v){
	int max;
	point p;
	int i;

	max = v.size();

	for (i=0; i<max; i++){
		if( !v[i].v){
			p = v[i].pt;
		}
	break;
	}
	assert(i<max);
	return i;
}
vector<point> getpoint(vector<list>){
	


int main(){
vector<point> pt;
vector<point> prev;

point p;
point e;
vector<list> info;
p.x = 1;
p.y = 1;

e.x = 1;
e.y = 4;

e = e;

p = p;

//while p != e{
//}






}
