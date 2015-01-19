#include<iostream>
#include<cmath>
#include<cassert>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include "../swerve/gnuplot.h"

#define nyi { cout<<"NYI "<<__LINE__<<endl; exit(44); }

using namespace std;

template<typename T>
class Maybe{
	T *data;

	public:
	Maybe():data(nullptr){}
	explicit Maybe(T t):data(new T(t)){
		assert(data);
	}

	Maybe(Maybe const& m):data(nullptr){
		if(m.data) data=new T(*m.data);
	}

	Maybe& operator=(Maybe const& m){
		T *next;
		if(m.data){
			next=new T(*m.data);
		}else{
			next=nullptr;
		}
		delete data;
		data=next;
		return *this;
	}

	~Maybe(){ delete data; }

	operator bool()const{ return !!data; }

	T& operator*(){
		assert(data);
		return *data;
	}
};

template<typename T>
bool operator<(Maybe<T>,Maybe<T>)nyi

template<typename T>
ostream& operator<<(ostream&,Maybe<T>)nyi

template<typename A,typename B,typename C>
priority_queue<A,B,C> operator|=(priority_queue<A,B,C>& p,A a){
	p.push(a);
	return p;
}

template<typename T>
vector<T> reverse(vector<T> v){
	vector<T> r;
	for(int i=v.size()-1;i>=0;i--) r|=v[i];
	return r;
}

template<typename T>
queue<T>& operator|=(queue<T>& q,T t){
	q.push(t);
	return q;
}

template<typename K,typename V>
vector<V> values(map<K,V> m){
	vector<V> r;
	for(auto p:m) r|=p.second;
	return r;
}

template<typename K,typename V>
set<K> keys(map<K,V> m){
	set<K> r;
	for(auto a:m) r|=a.first;
	return r;
}

template<typename T>
vector<T> flatten(vector<vector<T>> v){
	vector<T> r;
	for(auto a:v) r|=a;
	return r;
}

template<typename T>
vector<T> flatten(vector<set<T>> v){
	vector<T> r;
	for(auto a:v) r|=to_vec(a);
	return r;
}

template<typename T>
ostream& operator<<(ostream& o,set<T> const& s){
	o<<"{";
	for(auto a:s) o<<" "<<a;
	return o<<" }";
}

template<typename A,typename B>
ostream& operator<<(ostream& o,pair<A,B> const& p){
	return o<<"("<<p.first<<","<<p.second<<")";
}

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
	return s;
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

template<typename Func,typename Collection>
auto mapf(Func f,Collection v)->vector<decltype(f(*begin(v)))>{
	vector<decltype(f(*begin(v)))> r;
	for(auto a:v) r|=f(a);
	return r;
}

#define MAP(a,b) mapf([](decltype(*begin(b)) elem){ return a(elem); },b)

template<unsigned DENOM>
class Fixed_point{
	char x;

	public:
	Fixed_point(double d):x(d*DENOM){}

	Fixed_point& operator+=(Fixed_point f){
		x+=f.x;
		return *this;
	}

	operator double()const{ return (double)x/DENOM; }
};

static const int DIVISIONS=8;
typedef Fixed_point<DIVISIONS> Distance;
static const double GRID_SIZE=1.0/DIVISIONS;

struct Location{
	Distance x,y;
};

bool operator==(Location a,Location b){
	return a.x==b.x && a.y==b.y;
}

bool operator<(Location a,Location b){
	if(a.x<b.x) return 1;
	if(a.x>b.x) return 0;
	return a.y<b.y;
}

Location operator+(Location a,Location b){
	a.x+=b.x;
	a.y+=b.y;
	return a;
}

ostream& operator<<(ostream& o,Location a){
	return o<<"Loc("<<a.x<<","<<a.y<<")";
}

static const int SPEEDS=4;//# of nonzero speeds in the same dir; should be >=1

class Speed{
	char x;

	public:
	explicit Speed(int i):x(i){
		assert(i>=-SPEEDS && i<=SPEEDS);
	}

	operator int()const{ return x; }

	double frac()const{ return x/(double)SPEEDS; }
};

vector<Speed> all_speeds(){
	vector<Speed> r;
	for(int i=-SPEEDS;i<=SPEEDS;i++) r|=Speed{i};
	return r;
}

#include "rotation.h"

struct State{
	Location location;
	Rotation rotation;
	Speed speed;
};

bool operator<(State a,State b){
	if(a.location<b.location) return 1;
	if(b.location<a.location) return 0;
	if(a.rotation<b.rotation) return 1;
	if(b.rotation<a.rotation) return 0;
	return a.speed<b.speed;
}

bool operator==(State a,State b){
	return a.location==b.location && a.rotation==b.rotation && a.speed==b.speed;
}

bool operator!=(State a,State b){
	return !(a==b);
}

ostream& operator<<(ostream& o,State const& s){
	o<<"State(";
	o<<s.location<<"rot:"<<s.rotation<<",speed:"<<s.speed;
	return o<<")";
}

static const double TIMESTEP=.05;//seconds
static const double MAX_SPEED=12;//ft/s
static const double MAX_ROT_SPEED=40;//RPM
//static const double MAX_SPEED=24;//ft/s
//static const double MAX_ROT_SPEED=180;//RPM
static const double MAX_ROT_PER_TIMESTEP=MAX_ROT_SPEED*TIMESTEP/60*ROTATION_COUNTS;

static const auto check=[](){
	auto dist_per_timestep=MAX_SPEED*TIMESTEP*DIVISIONS;
	assert(dist_per_timestep>=1);
	cout<<"Dist per timestep:"<<dist_per_timestep<<endl;
	cout<<"Max rot:"<<MAX_ROT_PER_TIMESTEP<<endl;
	assert(MAX_ROT_PER_TIMESTEP>=1);
	return 0;
}();

set<Rotation> available_rotations(Rotation current){
	set<Rotation> r;
	for(int i=-MAX_ROT_PER_TIMESTEP;i<=MAX_ROT_PER_TIMESTEP;i++){
		r|=(current+i);
	}
	return r;
}

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
	o<<m.loc<<m.rot<<","<<m.speed;
	return o<<")";
}

Location location(Move m){ return m.loc; }

vector<Location> locations(set<Move> s){
	return mapf(location,s);
}

//actually, displacements
vector<Location> available_loc(Rotation r,Speed speed){
	double dist_per_timestep=speed.frac()*TIMESTEP*MAX_SPEED;
	auto max_x_diff=sin(r.rad())*dist_per_timestep;
	auto max_y_diff=cos(r.rad())*dist_per_timestep;
	/*int steps=1+max(max_x_diff,max_y_diff)/GRID_SIZE;
	vector<Location> out;
	for(int i=0;i<=steps;i++){
		out|=Location{max_x_diff*i/steps,max_y_diff*i/steps};
	}
	return out;//these aren't garunteed to be unique.
	*/
	return vector<Location>{Location{max_x_diff,max_y_diff}};
}

vector<Speed> available_speeds(Speed speed){
	/*if(speed==2) return vector<Speed>{Speed{1},Speed{2}};
	if(speed==1) return vector<Speed>{Speed{0},Speed{1},Speed{2}};
	if(speed==0) return vector<Speed>{Speed{-1},Speed{0},Speed{1}};
	if(speed==-1) return vector<Speed>{Speed{-2},Speed{-1},Speed{0}};
	if(speed==-2) return vector<Speed>{Speed{-1},Speed{-2}};
	assert(0);*/
	set<Speed> r;
	auto x=(int)speed;
	//for(int i=0;i<SPEEDS;i++){
	int i=1;
		if(x+i<=SPEEDS){
			r|=Speed{x+i};
		}
		if(x-i>=-SPEEDS){
			r|=Speed{x-i};
		}
	//}
	return to_vec(r);
}

set<Move> available_moves(Rotation rot0,Speed speed){
	set<Move> r;
	for(auto rot:available_rotations(rot0)){
		for(auto loc:available_loc(rot0,speed)){
			for(auto accel:available_speeds(speed)){
				r|=Move{loc,rot,accel};
			}
		}
	}
	return r;
}

map<pair<Rotation,Speed>,set<Move>> move_lookup_table(){
	map<pair<Rotation,Speed>,set<Move>> r;
	for(auto speed:all_speeds()){
		for(auto rotation:all_rotations()){
			r[make_pair(rotation,speed)]=available_moves(rotation,speed);
		}
	}
	return r;
}

set<Location> single_move_offsets(){
	auto m=mapf(location,flatten(values(move_lookup_table())));
	return to_set(m);
}

vector<State> next(State current){
	auto moves=move_lookup_table()[make_pair(current.rotation,current.speed)];
	return mapf(
		[current](Move move)->State{
			return State{
				current.location+move.loc,
				move.rot,
				move.speed
			};
		},
		to_vec(moves)
	);
}

double dist(Location a,Location b){
	auto dx=a.x-b.x;
	auto dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}

double calc_dist(State a,State b){
	return dist(a.location,b.location);
}

pair<vector<State>,unsigned> a_star(State initial,State goal){
	unsigned visited=0;
	map<State,Maybe<State>> prev;
	prev[initial]=Maybe<State>();

	map<State,unsigned> dist;
	dist[initial]=0;

	struct Compare{
		map<State,unsigned> &dist;
		State goal;

		Compare(map<State,unsigned> &m,State goal1):dist(m),goal(goal1){}

		unsigned min_dist(State s){
			auto f=dist.find(s);
			if(f==dist.end()){
				cout<<s<<endl;
				nyi
			}
			//return f->second+calc_dist(s,goal)/MAX_SPEED;
			return f->second+calc_dist(s,goal)/MAX_SPEED;
			//return calc_dist(s,goal)/MAX_SPEED;
		}

		bool operator()(State a,State b){
			return min_dist(a)>min_dist(b);
			/*auto f=dist.find(a);
			auto g=dist.find(b);
			nyi;*/
		}
	};

	//auto f=[](State,State){ return 0; };

	//priority_queue<State,vector<State>,decltype(f)> p();
	priority_queue<State,vector<State>,Compare> p(Compare{dist,goal});
	p|=initial;
	//set<State> visited1;
	
	while(p.size()){
		auto at=p.top();
		p.pop();
		//while(!p.empty() && p.top()==at) p.pop();
		//if(visited1.count(at)) continue;
		//visited1|=at;
		visited++;

		if(at==goal){
			vector<State> r;
			r|=at;
			while(prev[at]){
				at=*prev[at];
				r|=at;
			}
			return make_pair(reverse(r),visited);
		}

		//cout<<"at:"<<at<<endl;
		auto d=dist[at];

		for(auto n:next(at)){
			//if(n==at) continue;
			//assert(n!=at);
			auto f=prev.find(n);
			if(f==prev.end()){
				prev[n]=Maybe<State>(at);
				dist[n]=1+d;
				//cout<<"Adding:"<<n<<endl;
				p|=n;
			}
		}
	}
	nyi
}

template<typename Goal>
pair<vector<State>,unsigned> bfs(State initial,Goal goal){
	unsigned visited=0;
	queue<State> to_visit;
	to_visit|=initial;

	map<State,Maybe<State>> prev;
	prev[initial]=Maybe<State>();

	while(to_visit.size()){
		auto at=to_visit.front();
		to_visit.pop();
		visited++;
		if(goal(at)){
			vector<State> v;
			v|=at;
			while(prev[at]){
				at=*prev[at];
				v|=at;
			}
			return make_pair(reverse(v),visited);
		}

		//cout<<"at "<<at<<endl;

		for(auto n:next(at)){
			auto f=prev.find(n);
			if(f!=prev.end()) continue;
			to_visit|=n;
			prev[n]=Maybe<State>(at);
		}
	}
	nyi
}

Location location(State s){ return s.location; }

vector<Location> locations(vector<State> v){
	return MAP(location,v);
}

pair<double,double> to_pair(Location a){ return make_pair(a.x,a.y); }

int main(){
	State initial{{0,0},Rotation{0},Speed{0}};
	//cout<<initial<<endl;
	//cout<<available_moves(Rotation{0},Speed{0}).size()<<endl;
	auto m=move_lookup_table();
	//cout<<m.size()<<endl;
	/*for(auto a:keys(m)){
		cout<<a<<endl;
	}*/
	cout<<flatten(values(m)).size()<<endl;
	cout<<to_set(flatten(values(m))).size()<<endl;
	/*for(auto speed:all_speeds()){
		cout<<speed<<":"<<available_speeds(speed)<<endl;
	}
	for(auto rot:all_rotations()){
		cout<<rot<<":"<<available_rotations(rot)<<endl;
	}*/
	//cout<<Location{2,3}+Location{2,2}<<endl;
	//cout<<available_moves(Rotation{0},Speed{0})<<endl;
	//cout<<locations(available_moves(Rotation{0},Speed{0}))<<endl;
	//cout<<single_move_offsets()<<endl;
	State goal{{12,0},Rotation{0},Speed{0}};
	auto r=bfs(initial,[](State s){ return s.location==Location{3,0}; });
	//cout<<r<<endl;
	for(auto a:r.first){
		cout<<a<<endl;
	}
	cout<<r.first.size()<<" "<<r.second<<endl;
	show_plot(mapf(to_pair,locations(r.first)));
	/*auto r2=a_star(initial,goal);
	for(auto a:r2.first) cout<<a<<endl;
	cout<<r2.first.size()<<" "<<r2.second<<endl;*/
}
