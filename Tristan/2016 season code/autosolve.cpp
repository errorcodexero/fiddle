//Create A representation of the maze
//create an external file to be imported as the map for the robot to navigate
//
//
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <time.h> 
#include <assert.h>
#include <unistd.h>

#define NYI {cout << "NYI " << __LINE__<<"\n"; exit(1);}

#define WIDTH 27
#define LENGTH 54
#define WALLONE 3
#define STARTONE 0
#define STARTTWO 0
#define ENDONE 5
#define ENDTWO 0


using namespace std;

/////////////////////////////////////////////////////// //////////////////////
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
	bool walls[WIDTH][LENGTH];
};

struct list{
	point pt;
	point prev;
	bool v;
};

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

ostream&operator<<(ostream& o, mapstruct const& map){
	
	return o<< map.width << "," << map.length << endl;
}

ostream&operator<<(ostream& o, list const& l){
	
	o<< "List prev:" << l.prev << "," << "List point:"<< l.pt << endl;
	return o;
}

template<typename T >
ostream&operator<<(ostream& o, vector<T> const& v){
	for(T a:v)
		o<<a<<"\n";

	return o;
}

template<typename A, typename B>
ostream&operator<<(ostream& o, pair<A,B> const& p){
	o << "Pairs: " << p.first << "," << p.second << endl; 
	return o;
}


///////////////////////////////////////////////////////////////////////////////
//enums
//
//the enums for detremine the orentation 
//////////////////////////////////////////////////////////////////////////////
enum direction { LEFT=0, RIGHT=1, UP=2, DOWN=3};
enum movedir { MFORWARD=0, MRIGHT=1, MLEFT=2, MBACK=3};


ostream&operator<<(ostream& o, movedir const& p){
	if(p==MFORWARD)
		o<< "Forward";
	else if( p==MRIGHT)
		o<< "Right";
	else if (p==MLEFT)
		o<<"Left";
	else if (p==MBACK)
		o<<"Back";
	 
	return o;
}
//////////////////////////////////////////////////////////////////////////////
//pbool
//
//Takes in a boolian variable and returns a string that is ether TRUE or FALSE
//////////////////////////////////////////////////////////////////////////////
string pbool(bool b){
	if(b)
		return "true";
	else 
		return "false";
}
///////////////////////////////////////////////////////////////////////////////////////////
//pmovedir
//
//takes in a enum variable and returns a string that is the equivilent to the enum's values
///////////////////////////////////////////////////////////////////////////////////////////
string pmovedir(movedir a){
	string b;
	if(a == MLEFT)
		return "Left";
	else if(a == MRIGHT)
		return "Right";
	else if(a == MFORWARD)
		return "Forward";
	else if(a == MBACK)
		return "Back";
	else
		return "nothing was entered";
}
	
/////////////////////////////////////////////////////////////////////////////
// bounderies
//
// returns true if p is in the grid
/////////////////////////////////////////////////////////////////////////////
bool bounderies(point p,mapstruct const& map){
	bool xvalid = p.x >=0 && p.x < map.width;
	bool yvalid = p.y >=0 && p.y < map.length;
	return xvalid && yvalid;
}

//////////////////////////////////////////////////////////////////////////////
// Walls
//
// returns true if p is not a wall
//////////////////////////////////////////////////////////////////////////////
bool Walls(point p,mapstruct const& map){
 	return !map.walls[p.x][p.y];	
}
/////////////////////////////////////////////////////////////////////////////
// valid																   
//																		   
// returns true if p is not a wall or boundry                              
/////////////////////////////////////////////////////////////////////////////
bool valid(point p,mapstruct  const& map){
	return (bounderies(p,map) && Walls(p,map));
}

/////////////////////////////////////////////////////////////////////////////
// validpoint
//
// returns true if the given point is not a wall or boundry and has not been visited
/////////////////////////////////////////////////////////////////////////////
bool validpoint(vector<list>  const& v,point q,mapstruct const& map){
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
	return point{p.x,p.y - 1};
}

point downp(point p){
	return point{p.x,p.y + 1};
}
/////////////////////////////////////////////////////////////////////////////
// nextp
//

//returns next point that has not been visited
////////////////////////////////////////////////////////////////////////////
int nextp(vector<list> const& v){
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
vector<point> getpoint(vector<list> const& v,point p,mapstruct const& map){
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
int findpoint(vector<list> const& v,point q){
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
/////////////////////////////////////////////////////////////////////////////
//getline
//
//request for ints and then input them into a string
////////////////////////////////////////////////////////////////////////////
int  getnum(){ 
	string s;
	
	getline(cin,s);
	return atoi(s.c_str());
	
}
/////////////////////////////////////////////////////////////////////////////
//loadmap
//
//loads an array that is what the program navigates
////////////////////////////////////////////////////////////////////////////
void loadmap(mapstruct & a){
	a.width = WIDTH;
	a.length = LENGTH;

	for(int i=0; i < a.width; i++)
		for(int j=0; j < a.length; j++)
			a.walls[i][j] = false;
	
	//for(int i=0; i < a.length-1; i ++) 
		//a.walls[WALLONE][i] = true;	
	
}
/////////////////////////////////////////////////////////////////////////////////////////////
//whatdir
//
//takes in two points and determines dirction reletive to the first point and returns an enum
/////////////////////////////////////////////////////////////////////////////////////////////
direction whatdir(point a,point b){

	if (a.x > b.x)
		return LEFT;
	else if (a.x < b.x)
		return RIGHT;
	else if (a.y > b.y)
		return UP;
	else if (a.y < b.y)
		return DOWN;

	assert(0);
	
}
/////////////////////////////////////////////////////////////////////////////
//whatmove
//
//takes in two directions and then finds orentation based on that
////////////////////////////////////////////////////////////////////////////
movedir whatmove(direction one, direction two){
	if(one == two)
		return MFORWARD;
	else if(one == RIGHT){
		if(two == UP)
			 return MLEFT;
		else if (two == DOWN)
			return MRIGHT;
	}
	else if(one == LEFT){
		if(two == UP)
			return MRIGHT;
		else if(two == DOWN)
			return MLEFT;
	}
	else if(one == UP){
		if (two == RIGHT)
			return MRIGHT;
		else if(two == LEFT)
			return MLEFT;
	}
	else if(one == DOWN){
		if(two == RIGHT)
			return MLEFT;
		else if(two == LEFT)
			return MRIGHT;
	}

	assert(0);
	


}
/////////////////////////////////////////////////////////////////////////////
//invertvector
//
//takes in a vector and reverses its order
////////////////////////////////////////////////////////////////////////////
vector<point> invertvector(vector<point> v){
	vector<point> nv;
	for(int i = v.size() - 1; i > -1;i--)
		nv.push_back(v[i]);
	return nv;
}
/////////////////////////////////////////////////////////////////////////////
//findlist
//
//finds common orentations in secsession.
////////////////////////////////////////////////////////////////////////////
vector<pair<int,direction>> findlist(vector<direction> v){
	vector<pair<int,direction>> pairs;
	pair<int,direction> p;
	

	for(unsigned int i=0; i < v.size(); i++){//loops throught the vector.
		direction FCE;
		FCE = v[i];
		
		p.first=0;
		p.second = FCE;
		while(v[i] == FCE && i < v.size()){//finds common positions in secsession		
			p.first++;
			i++;
		}
		i--; //the for loop incerments too far so you need to go back to account for all of the elements
		pairs.push_back(p);
	}

	return pairs;
}
/////////////////////////////////////////////////////////////////////////////
//findlist2
//
//finds common relative orentations in secsession.
////////////////////////////////////////////////////////////////////////////
vector<pair<int,movedir>> findlist2(direction crdir,vector<pair<int,direction>> v,direction enddir){
	vector<pair<int,movedir>> pairs;
	pair<int,movedir> p;
	direction LCD = crdir;
	movedir turn;

	

	for(unsigned int i=0; i < v.size(); i++){//loops throught the vector.
		turn = whatmove(LCD,v[i].second);//figures out orentation

		if (turn != MFORWARD){
			p.first = 1;
			p.second = turn;
			pairs.push_back(p);
			LCD = v[i].second;	
		}
		p.first = v[i].first;
		p.second = MFORWARD;
		pairs.push_back(p);
	}
	if (LCD != enddir){
		p.first = 1;
		p.second = whatmove(LCD,enddir);
		pairs.push_back(p);
	}
	
	
	return pairs;
}
vector<pair<int,movedir>> solvemaze(point start,point end,direction startdir,direction enddir){
	//declarations	
	point p;
	point e;
	point f;
	list log;
	mapstruct map;	
	direction nextdir;
	vector<list> info;
	vector<point> nextpoint;
	vector<point> path;
	vector<point> ipath;
	vector<movedir> drivec;
	vector<movedir> fdrive;
	vector<pair<int,direction>> pear;
	vector<pair<int,movedir>> pear2;
	vector<movedir> finnalout;
	vector<direction> vnextdir;
	int lastline;
	int lineofvector;
	bool endpoint;
	

	loadmap(map);//loads the map the the robot will navigate

	endpoint = false;
	
	//printing out values before assigning them to points
	
	f.x = start.x - 1;//set
	f.y = start.y - 1;//inital location for previus

	p.x = start.x;//set px
	p.y = start.y;//location of start point py

	e.x = end.x;//set ex
	e.y = end.y;//location of end point ey

	//cout << "INITAL POINTS" << endl;
	//cout <<"prev inital:"<< f << "point inital:" << p << endl;
	//cout << "-----------------------------------------------------------------------" << endl;
	log.prev = f; //sets a prev point 
	log.pt = p; //set the original point
	log.v = false; // set the visited to not visited
	info.push_back(log);//Push the log to info 
		
	while (!endpoint){
			
		lineofvector = nextp(info); //find the line of stored data that is next in line

		p = info[lineofvector].pt;//save that loacation that you want to go to going to
			
		nextpoint = getpoint(info,p,map); // set a vector to have all posable points that are legal
			
		for (unsigned int i = 0; i < nextpoint.size(); i++){         //loop tell for the size of the vector nextpoint
				
			log.prev = p; //store prev point
				
			log.v = false; //set the visisted to not visited
				
			log.pt = nextpoint[i]; // the point that you are storing
				
			if(log.pt == e){
				endpoint = true; // set whether you have compleated the calculations to true
			}

			info.push_back(log); // store all the stored point
		}	
			
	
		info[lineofvector].v = true; // set the visited status to visited
			
	}
	//cout << "-----------------------------------------------------------------------" << endl;

	//cout << "PATH:" << endl << endl;

	lastline = findpoint(info,e);
	//cout << lastline << "last line" << endl;
	while(lastline != 0){
		//cout << info[lastline].prev << endl;
		path.push_back(info[lastline].pt);
		lastline = findpoint(info,info[lastline].prev);
		//cout << lastline << "saved vector" << endl;
	}

	ipath = invertvector(path); ////invert path
	

	//for (unsigned int i=0; i<ipath.size(); i++)	
		//cout << ">>" << ipath[i] << endl;

	for(unsigned int i = 0; i < ipath.size()-1;i++){ //loop through the vector and deturmine the route 
		nextdir = whatdir(ipath[i],ipath[i+1]); //figures out direction
		//cout << nextdir << endl;
		vnextdir.push_back(nextdir);
		
	}
	
	pear = findlist(vnextdir);
	
	pear2 = findlist2(startdir,pear,enddir);
		
	return pear2;	
}


int main(){
	point a;
	point b;
	direction c=RIGHT;
	direction  d=RIGHT;
	vector<pair<int,movedir>> FinalInstructions;
	
	a.x = STARTONE;
	a.y = STARTTWO;
	
	b.x = ENDONE;
	b.y = ENDTWO;

	FinalInstructions = solvemaze(a,b,c,d);

	cout << "Final:" << endl << FinalInstructions << endl;
}












