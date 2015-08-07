

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
/////////////////////////////////////////////////////////////////////////////
// Structures
//
// All Structures
/////////////////////////////////////////////////////////////////////////////
struct point{
	int x;
	int y;
};

struct list{
point pt;
point prev;
bool v;
};
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// operatior point
//
// allow the use of diffrent things with the structure point
/////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// lastpointvalid
//
// returns true if the given point is not in the vector
/////////////////////////////////////////////////////////////////////////////
bool lastpointvalid(point p,vector<point> lp)
{
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

/////////////////////////////////////////////////////////////////////////////
// validpoint
//
// returns true if the given point is not a wall or boundry and has not been visited
/////////////////////////////////////////////////////////////////////////////
bool validpoint(vector<list> v,point q){
	int i;
	int max;
	bool p ;

	p=false;
	max = v.size();
	for(i=0; i<max; i++){
		if(v[i].pt == q){
			p = true;
			break;
		}
		
	}
	return valid(q) & !p;
}

/////////////////////////////////////////////////////////////////////////////
// [dir]p
//
// returns adjacent points
/////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////
// nextp
//
//returns next point that has not been visited
////////////////////////////////////////////////////////////////////////////
int nextp(vector<list> v){
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
/////////////////////////////////////////////////////////////////////////////
// getpoint
//
// given a point will return a vector of points that are valid
/////////////////////////////////////////////////////////////////////////////
vector<point> getpoint(vector<list> v,point p){
	point a;
	point b;
	point c;
	point d;
	vector<point> validpoints;
	
	a = leftp(p);
	b = rightp(p);
	c = upp(p);
	d = downp(p);

	if(validpoint(v,a)){
		validpoints.push_back(a);		
	}

	if(validpoint(v,b)){
		validpoints.push_back(a);		
	}

	if(validpoint(v,c)){
		validpoints.push_back(a);		
	}

	if(validpoint(v,d)){
		validpoints.push_back(a);		
	}
	
	return validpoints; 

}


int main(){
	//declarations	
	int lineofvector;
	point p;
	point e;
	vector<list> info;
	vector<point> nextpoint;
	list log;
	point f;
	
f.x = -1;//set
f.y = -1;//inital location for previus

p.x = 1;//set
p.y = 1;//location of start point

e.x = 1;//set
e.y = 4;//location of end point

log.prev = f; //sets a prev point 
log.pt = p; //set the original point
log.v = false; // set the visited to not visited
info.push_back(log); //Push the info to the vector of structures 


	while (p != e){
		lineofvector = nextp(info);//find the line of stored data that is next in line
	
		nextpoint = getpoint(info,p); // set a vector to have all posable points that are legal
	
		for (unsigned int i = 0; i < nextpoint.size(); i++){//loop tell for the size of the vector nextpoint
			log.prev = p; //store prev point
			log.v = false;//set the visisted to not visited
			log.pt = nextpoint[i];// the point that you are storing
			info.push_back(log);// store all the stored point
		}
	
		info[lineofvector].v = true;// set the visited status to visited
	
		assert(nextpoint.size() != 0);

		p = nextpoint[0];//save that loacation that you want to go to going to

		cout << p << endl; //print out the location if the point
	}
}
