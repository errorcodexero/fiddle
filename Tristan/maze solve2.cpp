

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <time.h> 
#include <assert.h>
#include <unistd.h>

#define NYI {cout << "NYI " << __LINE__<<"\n"; exit(1);}

#define WIDTH 5
#define LENGTH 5

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
	bool walls[WIDTH][LENGTH];
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
ostream&operator<<(ostream& o, mapstruct const& map){
	
	return o<< map.width << "," << map.length << endl;
}
ostream&operator<<(ostream& o, list const& l){
	
	o<< "List prev:" << l.prev << "," << "List point:"<< l.pt << endl;
	return o;
}
template<typename T >
ostream&operator<<(ostream& o, vector<T> const& v){
	for(T a:v) {
		o<<a<<"\n";
	}
	return o;
}
enum direction { LEFT=0, RIGHT=1, UP=2, DOWN=3};
enum movedir { MFORWARD=0, MRIGHT=1, MLEFT=2, MBACK=3};
/////////////////////////////////////////////////////////////////////////////
string pbool(bool b){
	if(b)
		return "true";
	else 
		return "false";
}

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
///////////////////////////////////////////////////////////////////// ////////
bool bounderies(point p,mapstruct const& map){
		//cout << "BOUNDEIES"  << endl;
		//cout << endl;
		//cout << "bpoint:" << p << endl;
		//cout << "boundries x:" << "0 and " << map.width << endl;
		//cout << endl;
		//cout << "boundries y:" << "0 and " << map.length << endl;
		//cout << endl;
	bool xvalid = p.x >=0 && p.x < map.width;
	bool yvalid = p.y >=0 && p.y < map.length;
		//cout << "xvalid " << pbool(xvalid) << " and " << "yvalid " << pbool(yvalid) << endl;
		//cout << "-----------------------------------------------------------------------" << endl;
	return xvalid && yvalid;
}

//////////////////////////////////////////////////////////////////////////////
// Walls
//
// returns true if p is not a wall
//////////////////////////////////////////////////////////////////////////////
bool Walls(point p,mapstruct const& map){
		//cout << " WALLS " << endl;
		//cout << endl;
		//cout << "p.x:" << p.x << " " << "p.y:" << " " << p.y << endl;
		//cout << endl;
		//cout << "walls "  << pbool(map.walls[p.x][p.y]) << endl;
		//cout << "-----------------------------------------------------------------------" << endl;
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
		//cout << "VALIDPOINT" << endl;
		//cout << endl;
		//cout << "inputed point " << q << endl;
		//cout << endl;
	p=false;
	max = v.size();
	for(i=0; i<max; i++){
		if(v[i].pt == q){
			p = true;
			break;
		}
		
	}
		//cout << "returned " << pbool(valid(q,map)) << " and p " << pbool(p) << endl;
		//cout << "-----------------------------------------------------------------------" << endl;
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
/////////////////////////////////////////////////////////////////////////////
//getline
//
//request for ints and then input it into a string
////////////////////////////////////////////////////////////////////////////
int  getnum(){ 
	string s;
	//cout << "before getline" << endl;
	getline(cin,s);
	//cout << "calculations" << endl;
	return atoi(s.c_str());
	
}
void loadmap(mapstruct & a){
	a.width = WIDTH;
	a.length = LENGTH;

	for(int i=0; i < a.width; i++)
		for(int j=0; j < a.length; j++)
			a.walls[i][j] = false;

	for(int i=0; i < a.length-1; i ++) 
		a.walls[1][i] = true;
	
	for(int i=1; i <= a.length-1; i++)
		a.walls[3][i] = true;

}
direction whatdir(point a,point b){
	direction pos;
	if (a.x > b.x)
		pos = LEFT;
	else if (a.x < b.x)
		pos = RIGHT;
	else if (a.y > b.y)
		pos = UP;
	else if (a.y < b.y)
		pos = DOWN;
	else 
		assert(0);
	return pos;
}
movedir whatmove(direction one, direction two){
	movedir turn; 
	if(one == two)
		turn = MFORWARD;
	else if(one == RIGHT){
		if(two == UP)
			 turn = MLEFT;
		else if (two == DOWN)
			turn = MRIGHT;
	}
	else if(one == LEFT){
		if(two == UP)
			turn = MRIGHT;
		else if(two == DOWN)
			turn = MLEFT;
	}
	else if(one == UP){
		if (two == RIGHT)
			turn = MRIGHT;
		else if(two == LEFT)
			turn = MLEFT;
	}
	else if(one == DOWN){
		if(two == RIGHT)
			turn = MLEFT;
		else if(two == LEFT)
			turn = MRIGHT;
	}
	else
		assert(0);
	return turn;

}

int main(){
	//declarations	
	point p;
	point e;
	point f;
	list log;
	mapstruct map;
	bool endpoint;
	vector<list> info;
	vector<point> nextpoint;
	vector<point> path;
	int lastline;
	int lineofvector;
	int px = 0;
	int py = 0;
	int ex = 0;
	int ey = 0;
	direction currentdir = RIGHT;
	direction nextdir;
	movedir turn;

	loadmap(map);

	endpoint = false;
	
	cout << "Insert an int between 0 and " << (map.width -1) << " for the start postion ""x"" " << endl;
	//cout << "before" << endl;
	//px = 0;
 	px = getnum();
	//cout << "calculated" << endl;
	cout << "Insert an int between 0 and " << (map.length -1) << " for the start postion ""y"" " << endl;
	//py = 0;
	py = getnum();
	
	//cout << px << "," << py << " and " << map.width << "," << map.length << endl;
	while((map.walls[px][py]) || (px < 0 || px >= map.width) || (py < 0 || py >= map.length)) {

			cout << "The given points are either not in the grid or on a wall please give new points" << endl;
			cout << "Insert an int between 0 and " << map.width -1 << " for the start postion ""x"" " << endl;
			px = getnum();
			cout << "Insert an int between 0 and " << map.length -1 << " for the start postion ""y"" " << endl;
			py = getnum();
		
	}

	cout << "Insert an int between 0 and " << map.width -1 << " for the end postion ""x"" " << endl;
	//ex = WIDTH -1;
	 ex = getnum();
	cout << "Insert an int between 0 and " << map.length -1 << " for the end postion ""y"" " << endl;
	//ey = LENGTH -1; 
	ey = getnum();

       while((map.walls[ex][ey]) || (ex < 0 || ex >= map.width) || (ey < 0 || ey >= map.length)){
	
			cout << "The given points are either not in the grid or on a wall please give new points" << endl;
			cout << "Insert an int between 0 and " << map.width -1 << " for the end postion ""x"" " << endl;
			ex = getnum();
			cout << "Insert an int between 0 and " << map.length -1 << " for the end postion ""y"" " << endl;
			ey = getnum();

	}
	
	//printing out values before assigning them to points
	cout << "GIVEN POINTS:" << endl;
	cout << px << "," << py << endl;
	cout << ex << "," << ey << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	
	f.x = px - 1;//set
	f.y = py - 1;//inital location for previus

	p.x = px;//set
	p.y = py;//location of start point

	e.x = ex;//set
	e.y = ey;//location of end point

	cout << "INITAL POINTS" << endl;
	cout <<"prev inital:"<< f << "point inital:" << p << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	log.prev = f; //sets a prev point 
	log.pt = p; //set the original point
	log.v = false; // set the visited to not visited
	info.push_back(log); //Push the info to the vector of structures 
		//cout << "INFO(variable)" << endl;
		//cout << "info:" << info;
		//cout << "info's size:" << info.size() << endl;
		//cout << "-----------------------------------------------------------------------" << endl;
		//cout << "WHILE(!ENDPOINT)" << endl;
	while (!endpoint){
			//cout << "entering loop" << endl;
		lineofvector = nextp(info); //find the line of stored data that is next in line
			//cout << "line of vector:" << lineofvector << endl;
		p = info[lineofvector].pt;//save that loacation that you want to go to going to
			//cout << "current point " << p << endl;

		nextpoint = getpoint(info,p,map); // set a vector to have all posable points that are legal
			//cout << "nextpoint:" << nextpoint << endl;
			//cout << " Before FOR " << endl;
		for (unsigned int i = 0; i < nextpoint.size(); i++){//loop tell for the size of the vector nextpoint
				//cout << "in loop" << endl;
			log.prev = p; //store prev point
				//cout << "logged prev:" << log.prev << endl;
			log.v = false; //set the visisted to not visited
				//cout << "logged v" << endl;
			log.pt = nextpoint[i]; // the point that you are storing
				//cout << "logged point" << endl;
			if(log.pt == e){
				endpoint = true;
			}

			info.push_back(log); // store all the stored point
		}	
			
	
		info[lineofvector].v = true; // set the visited status to visited
			//cout << "before exit while" << endl;
	}
	cout << "-----------------------------------------------------------------------" << endl;

	cout << "PATH:" << endl << endl;

	lastline = findpoint(info,e);
	//cout << lastline << "last line" << endl;
	while(lastline != 0){
		//cout << info[lastline].prev << endl;
		path.push_back(info[lastline].pt);
		lastline = findpoint(info,info[lastline].prev);
		//cout << lastline << "saved vector" << endl;
	}

	path.push_back(info[0].pt);

	for(int i = path.size() - 1; i > 0;i--){
		
		//cout << dir(path[i],path[i-1]) << endl;

		nextdir = whatdir(path[i],path[i-1]);
		//cout << "nextdir:" << nextdir << endl;
		turn = whatmove(currentdir,nextdir);
		//cout << "turn:" << turn << endl;
		cout << pmovedir(turn) << endl;
		currentdir=nextdir;
	}
	
}
