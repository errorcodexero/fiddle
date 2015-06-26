#include <iostream>

#include <math.h>

#include <stdlib.h>

using namespace std;

int getnum(){
	string s;
	cout<<"Enter a value for an x,y for the start and end points"<<endl;
	getline(cin,s);

	return atoi(s.c_str());
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
	}else
		yvalid = false;
		
	}
	return xvalid && yvalid;
}

bool Walls(int x,int y){
	bool xvalid;
	bool yvalid;

	if(y=1 && x=3){
		xvalid = false;
		yvalid = false;
	}else if(y=2 && x=3){
		xvalid = false;
		yvalid = false;
	}else
		xvalid = true;
		yvalid = true;
			
	}return xvalid && yvalid;
}

int main(){

	int pointx;
	int goaly;
	int pointy;
	int goalx;
	int dtgx;
	int dtgy
	string dirx;
	string diry;
	int start;
	int end;
	int sp;
	while(start != end){
	
	}
	//reterive and convirt locations
	pointx=getnum();
	pointy=getnum();
	goalx=getnum();
	goaly=getnum();

	//calculte directions
	if(goalx<pointx){
		dirx = "left";
	}else if(goalx>pointx){
		dirx = "right";
	}else{
		dirx = "here";
	}
	if(goaly<pointy){
		diry= "down";
	}else if(goaly>pointy){
		diry = "up";
	}else{
		diry = "here";
	}
	//find the absalue value
	dtgx=fabsf(pointx-goalx);
	dtgy=fabsf(pointy-goaly);
	//tell the location
	cout<<dtgx<<" in the "<<dirx<<" direction and "<<dtgy<<" in the "<<diry<<" direction"<<endl;
	return 0;
}
