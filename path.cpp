#include<iostream>
#include<cmath>
#include<cassert>
#include<vector>
#include<set>
#include<map>

#define nyi { cout<<"NYI "<<__LINE__<<endl; exit(44); }

using namespace std;

template<typename T>
ostream& operator<<(ostream& o,vector<T> const& v){
	o<<"[ ";
	for(auto a:v) o<<a<<" ";
	return o<<"]";
}

template<typename T>
vector<T>& operator|=(vector<T>& v,T t){
	v.emplace_back(move(t));
	return v;
}

template<typename T>
vector<T>& operator|=(vector<T>& v,vector<T> t){
	for(auto a:t) v|=a;
	return v;
}

template<typename T>
set<T>& operator|=(set<T>& s,T t){
	s.insert(t);
}

template<typename T>
set<T> to_set(vector<T> v){
	set<T> r;
	for(auto a:v) r|=a;
	return r;
}

template<typename T>
vector<T> to_vec(set<T> s){
	vector<T> r;
	for(auto a:s) r|=a;
	return r;
}

template<unsigned DENOM>
class Fixed_point{
	char x;

	public:
	Fixed_point(double d):x(d*DENOM){}

	operator double()const{ return (double)x/DENOM; }
};

static const int DIVISIONS=8;
typedef Fixed_point<DIVISIONS> Distance;
static const double GRID_SIZE=1.0/DIVISIONS;

struct Location{
	Distance x,y;
};

bool operator<(Location a,Location b){
	if(a.x<b.x) return 1;
	if(a.x>b.x) return 0;
	return a.y<b.y;
}

ostream& operator<<(ostream& o,Location a){
	return o<<"Loc("<<a.x<<","<<a.y<<")";
}

static const unsigned ROTATION_COUNTS=32;

class Rotation{
	unsigned char x;

	public:
	explicit Rotation(unsigned a):x(a%ROTATION_COUNTS){}

	operator unsigned()const{ return x; }

	double rad()const{
		return M_PI*2*x/ROTATION_COUNTS;
	}
};

Rotation operator+(Rotation r,int a){
	int next=(int)r+a;
	if(next<0) next+=ROTATION_COUNTS;
	return Rotation(next);
}

vector<Rotation> all_rotations(){
	vector<Rotation> r;
	for(unsigned i=0;i<ROTATION_COUNTS;i++) r|=Rotation(i);
	return r;
}

class Speed{
	char x;

	public:
	explicit Speed(int i):x(i){
		assert(i>=-2 && i<=2);
	}

	operator int()const{ return x; }

	double frac()const{ return x/2; }
};

/*ostream& operator<<(ostream& o,Speed a){
	nyi
}*/

vector<Speed> all_speeds(){
	vector<Speed> r;
	for(int i=-2;i<=2;i++) r|=Speed{i};
	return r;
}

struct State{
	Location location;
	Rotation rotation;
	Speed speed;
};

ostream& operator<<(ostream& o,State const& s){
	o<<"State(";
	o<<s.location<<s.rotation<<","<<s.speed;
	return o<<")";
}

static const double TIMESTEP=.05;//seconds
static const double MAX_SPEED=12;//ft/s
static const double MAX_ROT_SPEED=100;//RPM

static const int MAX_ROT_PER_TIMESTEP=MAX_ROT_SPEED*TIMESTEP*ROTATION_COUNTS;

vector<Rotation> available_rotations(Rotation current){
	vector<Rotation> r;
	for(int i=-MAX_ROT_PER_TIMESTEP;i<=MAX_ROT_PER_TIMESTEP;i++){
		r|=(current+i);
	}
	return r;
}

class Accel{
	//should be in range -1 to 1
	public:
	explicit Accel(int);
};

struct Move{
	Location loc;
	Rotation rot;
	Speed speed;
};

bool operator<(Move a,Move b){
	if(a.loc<b.loc) return 1;
	if(b.loc<a.loc) return 0;
	if(a.rot<b.rot) return 1;
	if(b.rot<a.rot) return 0;
	return a.speed<b.speed;
}

ostream& operator<<(ostream& o,Move m){
	o<<"Move(";
	o<<m.loc<<m.rot<<m.speed;
	return o<<")";
}

//actually, displacements
vector<Location> available_loc(Rotation r,Speed speed){
	double dist_per_timestep=speed.frac()*TIMESTEP;
	auto max_x_diff=sin(r.rad())*dist_per_timestep;
	auto max_y_diff=cos(r.rad())*dist_per_timestep;
	int steps=1+max(max_x_diff,max_y_diff)/GRID_SIZE;
	vector<Location> out;
	for(int i=0;i<=steps;i++){
		out|=Location{max_x_diff*i/steps,max_y_diff*i/steps};
	}
	return out;//these aren't garunteed to be unique.
}

vector<Speed> available_speeds(Speed speed){
	if(speed==2) return vector<Speed>{Speed{1},Speed{2}};
	if(speed==1) return vector<Speed>{Speed{0},Speed{1},Speed{2}};
	if(speed==0) return vector<Speed>{Speed{-1},Speed{0},Speed{1}};
	if(speed==-1) return vector<Speed>{Speed{-2},Speed{-1},Speed{0}};
	if(speed==-2) return vector<Speed>{Speed{-1},Speed{-2}};
	assert(0);
}

vector<Move> available_moves(Rotation rot0,Speed speed){
	vector<Move> r;
	for(auto rot:available_rotations(rot0)){
		for(auto loc:available_loc(rot0,speed)){
			for(auto accel:available_speeds(speed)){
				r|=Move{loc,rot,accel};
			}
		}
	}
	return r;
}

map<pair<Rotation,Speed>,vector<Move>> move_lookup_table(){
	map<pair<Rotation,Speed>,vector<Move>> r;
	for(auto speed:all_speeds()){
		for(auto rotation:all_rotations()){
			r[make_pair(rotation,speed)]=to_vec(to_set(available_moves(rotation,speed)));
		}
	}
	return r;
}

template<typename K,typename V>
vector<V> values(map<K,V> m){
	vector<V> r;
	for(auto p:m) r|=p.second;
	return r;
}

template<typename T>
vector<T> flatten(vector<vector<T>> v){
	vector<T> r;
	for(auto a:v) r|=a;
	return r;
}

int main(){
	State initial{{0,0},Rotation{0},Speed{0}};
	cout<<initial<<endl;
	cout<<to_set(available_moves(Rotation{0},Speed{0})).size()<<endl;
	auto m=move_lookup_table();
	cout<<m.size()<<endl;
	cout<<flatten(values(m)).size()<<endl;
	cout<<to_set(flatten(values(m))).size()<<endl;
}
