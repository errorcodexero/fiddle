

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
struct mapstruct{
	int width;
	int length;
	bool walls[6][4];
};
struct list{
	point pt;
	point prev;
	bool v;
};
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// operatior
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
ostream&operator<<(ostream& o, mapstruct map){
	
	o<< map.width << "," << map.length << "." << endl;

	return o;
}
ostream&operator<<(ostream& o, list l){
	
	o<< "prev:" << l.prev << "," << "point:"<< l.pt << "." << endl;
	return o;
}
template<typename T >
ostream&operator<<(ostream& o, vector<T> v){
	for(T a:v) {
		o<<a<<"\n";
	}
	return o;
}
/////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////
// bounderies
//
// returns true if p is in the grid
/////////////////////////////////////////////////////////////////////////////
bool bounderies(point p,mapstruct map){
	cout << "bpoint:" << p << endl;
	cout << "boundries: 0 and" << map.width << endl;
	cout << "boundries: 0 and" << map.length << endl;
	bool xvalid = p.x>=0 && p.x< map.width;
	bool yvalid = p.y>=0 && p.y< map.length;
	cout << "xvalid:" << xvalid << "yvalid:" << yvalid << endl;
	return xvalid && yvalid;
}

//////////////////////////////////////////////////////////////////////////////
// Walls
//
// returns true if p is not a wall
//////////////////////////////////////////////////////////////////////////////
bool Walls(point p,mapstruct map){
	cout << "p.x:" << p.x << " " << "p.y" << p.y << endl;
	cout << "walls"  << map.walls[p.x][p.y] << endl;
 	return map.walls[p.x][p.y];	

}

/////////////////////////////////////////////////////////////////////////////
// valid																   
//																		   
// returns true if p is not a wall or boundry                              
/////////////////////////////////////////////////////////////////////////////
bool valid(point p,mapstruct map){
	return (Walls(p,map) && bounderies(p,map));
}

/////////////////////////////////////////////////////////////////////////////
// validpoint
//
// returns true if the given point is not a wall or boundry and has not been visited
/////////////////////////////////////////////////////////////////////////////
bool validpoint(vector<list> v,point q,mapstruct map){
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
	return valid(q,map) && !p;
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
	int i;

	max = v.size();

	for (i=0; i<max; i++){
		if( !v[i].v){
			break;
		}
	}
	assert(i<max);
	return i;
}
/////////////////////////////////////////////////////////////////////////////
// getpoint
//
// given a point will return a vector of points that are valid
/////////////////////////////////////////////////////////////////////////////
vector<point> getpoint(vector<list> v,point p,mapstruct map){
	point a;
	point b;
	point c;
	point d;

	vector<point> validpoints;
	
	a = leftp(p);
	b = rightp(p);
	c = upp(p);
	d = downp(p);

	if(validpoint(v,a,map)){
		validpoints.push_back(a);		
	}

	if(validpoint(v,b,map)){
		validpoints.push_back(b);		
	}

	if(validpoint(v,c,map)){

		validpoints.push_back(c);		
	}

	if(validpoint(v,d,map)){
		validpoints.push_back(d);		
	}
	
	return validpoints; 

}

/////////////////////////////////////////////////////////////////////////////
//Find Point
//
//finds point
////////////////////////////////////////////////////////////////////////////
int findpoint(vector<list> v,point q){
	int max;
	int i;

	max = v.size();

	for (i=0; i<max; i++){
		if( v[i].pt == q){

			break;
		}
	}
	assert(i<max);
	return i;
}
string dir(point p, point q){
	string s;

	if(q.x < p.x){
	
		s = "Left";
	}
	else if(q.x > p.x){
	
		s = "Right";
	}
	else if(q.y < p.y){
		s = "Up";

	}	
	else if(q.y > p.y){
		s = "Down";
	}
	return s;
}
int  getnum(){
	string s;
	getline(cin,s);
	return atoi(s.c_str());
}
void loadmap(mapstruct & a){
	a.width = 6;
	a.length = 4;

	for(int i=0; i < a.length; i++)
		for(int j=0; j < a.width; j++)
			a.walls[i][j] = false;

	a.walls[2][0] = true;
	a.walls[2][1] = true;
	a.walls[2][2] = true;
	a.walls[4][0] = true;
	a.walls[4][1] = true;
	
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
	bool endpoint;
	int lastline;
	vector<point> path;
	int px = -15;
	int py = -15;
	int ex = -15;
	int ey = -15;
	mapstruct map;
	
	loadmap(map);

	endpoint = false;
	/////////////////////////////////////////////////////////////////////////////
	//getline
	//
	//request for ints and then input it into a string
	////////////////////////////////////////////////////////////////////////////
	cout << "Insert an int between 1 and 6 for the start postion ""x"" " << endl;
	px = getnum();
	cout << "Insert an int between 1 and 4 for the start postion ""y"" " << endl;
	py = getnum();
	
	cout << px << "," << py << " and " << map.width << "," << map.length << endl;
	while((map.walls[px][py]) || (px < 0 || px >= map.width) || (py < 0 || py >= map.length)) {

			cout << "The given points are either not in the grid or on a wall please give new points" << endl;
			cout << "Insert an int between 1 and 6 for the start postion ""x"" " << endl;
			px = getnum();
			cout << "Insert an int between 1 and 4 for the start postion ""y"" " << endl;
			py = getnum();
		
	}

	cout << "Insert an int between 1 and 6 for the end postion ""x"" " << endl;
	ex = getnum();
	cout << "Insert an int between 1 and 4 for the end postion ""y"" " << endl;
	ey = getnum();

       while((map.walls[ex][ey]) || (ex < 0 || ex >= map.width) || (ey < 0 || ey >= map.length)){
	
			cout << "The given points are either not in the grid or on a wall please give new points" << endl;
			cout << "Insert an int between 1 and 6 for the end postion ""x"" " << endl;
			ex = getnum();
			cout << "Insert an int between 1 and 4 for the end postion ""y"" " << endl;
			ey = getnum();

	}

	//printing out values before assigning them to points
	cout << "Start and end points:" << endl;
	cout << px << "," << py << endl;
	cout << ex << "," << ey << endl;
	 
	f.x = px - 1;//set
	f.y = py - 1;//inital location for previus

	p.x = px;//set
	p.y = py;//location of start point

	e.x = ex;//set
	e.y = ey;//location of en/d point
	cout <<"f:"<< f << "p:" << p << endl;
	log.prev = f; //sets a prev point 
	log.pt = p; //set the original point
	log.v = false; // set the visited to not visited
	info.push_back(log); //Push the info to the vector of structures 
	cout << "info:" << info << endl;
	cout << "info's size:" << info.size() << endl;
	
	while (!endpoint){
		
		lineofvector = nextp(info); //find the line of stored data that is next in line
		cout << "line of vector:" << lineofvector << endl;
		p = info[lineofvector].pt;//save that loacation that you want to go to going to
		
		nextpoint = getpoint(info,p,map); // set a vector to have all posable points that are legal
		cout << "nextpoint:" << nextpoint << endl;
		cout << " Before for loop" << endl;
		for (unsigned int i = 0; i < nextpoint.size(); i++){//loop tell for the size of the vector nextpoint
		cout << "in loop" << endl;
			log.prev = p; //store prev point
			cout << "logged prev:" << log.prev << endl;
			log.v = false; //set the visisted to not visited
			cout << "logged v" << endl;
			log.pt = nextpoint[i]; // the point that you are storing
			cout << "logged point" << endl;
			if(log.pt == e){
				endpoint = true;
			}

			info.push_back(log); // store all the stored point
		}
		
	
		info[lineofvector].v = true; // set the visited status to visited

	}

	cout << "PATH:" << endl << endl;

	lastline = findpoint(info,e);
	cout << lastline << "last line" << endl;
	while(lastline != 0){
		cout << info[lastline].prev << endl;
		path.push_back(info[lastline].pt);
		lastline = findpoint(info,info[lastline].prev);
		cout << lastline << "saved vector" << endl;
	}

	path.push_back(info[0].pt);

	for(int i = path.size() - 1; i > 0;i--){
		
		cout << dir(path[i],path[i-1]) << endl << endl;
	}
	
}
