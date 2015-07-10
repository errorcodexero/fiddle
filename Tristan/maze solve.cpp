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

bool valid(point p,vector<point> lp){
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
 

twovectors getpoint(point p,vector<point> lp){
	twovectors q;
 
	if (valid(leftp(p))){
		if (lastpointvalid(p,lp){
			q.pref.push_back(leftp(p));
		}
		else{
			q.notpref.push_back(leftp(p));
		}	
	}
	if (valid(rightp(p))){
		if (lastpointvalid(p,lp){
			q.pref.push_back(rightp(p));
		}
		else{
			q.notpref.push_back(rightp(p));
		}	
	}
	if (valid(upp(p))){
		if (lastpointvalid(p,lp){
			q.pref.push_back(upp(p));
		}
		else{
			q.notpref.push_back(upp(p));
		}	
	}
	if (valid(downp(p))){
		if (lastpointvalid(p,lp){
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

	
int main(){
	
	point p; //declare a point type called p
	point e;
	int steps;
	int direction;
	twovectors v;
	vector<point> lstPoit;
	
	srand(time(NULL));

	e.x=4;
	e.y=1;
	
	p.x=1;
	p.y=1;
	
	steps = 0;

	lstPoit.push_back(p);

	while (p != e){
	
		v=getpoint(p,lstPoit,v);
		direction = rando(v.size());
		
		
		p = v[direction];

		lstPoit.push_back(p);
		
		cout << "got point:" << p << endl;
		
		steps++;
	}

	cout << "It took " << steps << " steps to reach the end" << endl;	
	
	return 0;
}











