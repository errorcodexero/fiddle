#include <iostream>

#include <math.h>

#include <stdlib.h>

#include <vector>

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
bool bournderies(int x,int y){
	bool xvalid;
	bool yvalid;

	if(x>=1 && x<=4){
		xvalid = true;
	}else
		xvalid = false;
	
	if(y>=1 && y<=3){
		yvalid = true;
	}else{
		yvalid = false;
		
	}
	return xvalid && yvalid;
}

bool Walls(int x,int y){
	bool xvalid;
	bool yvalid;

	if(y==1 && x==3){
		xvalid = false;
		yvalid = false;
	}else if(y==2 && x==3){
		xvalid = false;
		yvalid = false;
	}else{
		xvalid = true;
		yvalid = true;
			
	}
	return xvalid && yvalid;
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
	v.push_back(leftp(p));
	v.push_back(rightp(p));
	v.push_back(upp(p));
	v.push_back(downp(p));
	return v;
}
int main(){
	
	//point start;
	//point end;
	point p;

	p.x=1;
	p.y=1;
		
	

	
	cout << "original " << p << endl;
	
	cout << "left " << leftp(p) << endl;

	cout << "right " << rightp(p) << endl;

	cout << "up " << upp(p) << endl;

	cout << "down " << downp(p) << endl;

	//while(start != end){

	//}
	return 0;
}
