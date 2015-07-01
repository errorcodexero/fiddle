/*To do:
	- Make blocks work.
	- Maze printout
*/
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <assert.h>

using namespace std;

static const int X_LIMIT=10, Y_LIMIT=10;

typedef pair<int,int> Location;

enum class Move{FORWARD, BACKWARD, RIGHT, LEFT};

ostream& operator<<(ostream& o, Move in){
	#define X(name) if(in==Move::name)o<<""#name;
	X(FORWARD) X(RIGHT) X(BACKWARD) X(LEFT)
	#undef X
	return o;
}

struct Maze{
	struct Solver{
		Location loc;
		bool fin;
		Solver():loc(make_pair(0,0)),fin(0){}
	};
	vector<Location> blocks;
	int x_lim,y_lim;
	Location target;
	Solver solver;
	Maze():blocks(vector<Location>{}),x_lim(0),y_lim(0),target(Location{0,0}){}
};

template<typename T>
bool operator==(vector<T> a, vector<T> b){
	for(unsigned int i=0; i<a.size(); i++){
		for(unsigned int j=0; j<b.size(); j++){
			if(a[i]!=b[j])return 0; 
		}
	}
	return 1;
}

bool operator==(Maze a, Maze b){
	return (a.x_lim=b.x_lim && a.y_lim==b.y_lim && a.solver.loc==b.solver.loc && a.solver.fin==b.solver.fin && a.blocks==b.blocks && a.target==b.target);
}

bool operator!=(Maze a, Maze b){
	return !(a==b);
}

template<typename T>
ostream& operator<<(ostream& o,vector<T> in){
	o<<"<";
	for(unsigned int i=0; i<in.size(); i++){
		o<<in[i];
		if(i!=in.size()-1)o<<",";
	}
	o<<">";
	return o;
}

bool check(const Maze a, const Location l){
	for(unsigned int i; i<a.blocks.size(); i++){
		if(l==a.blocks[i])return 0;
	}
	return 1;
}

Maze update(Move a, Maze m){
	if(a==Move::LEFT){
		assert(m.solver.loc.first>0 );//&& check(m, Location{m.solver.loc.first--,m.solver.loc.second}));
		m.solver.loc.first--;
		cout<<"LOL"<<endl;
	}
	else if(a==Move::RIGHT){
		assert(m.solver.loc.first+1<m.x_lim );//&& check(m, Location{m.solver.loc.first++,m.solver.loc.second}));
		m.solver.loc.first++;
	}
	else if(a==Move::BACKWARD){
		assert(m.solver.loc.second>0 /*&& check(m, Location{m.solver.loc.first,m.solver.loc.second--})*/);
		m.solver.loc.second--;
	}
	else if(a==Move::FORWARD){
		assert(m.solver.loc.second+1<m.y_lim);// && check(m, Location{m.solver.loc.first,m.solver.loc.second++}));
		m.solver.loc.second++;
	}
	if(m.solver.loc==m.target)m.solver.fin=1;
	return m;
}

vector<Move> get_possible_moves(Maze a){
	vector<Move> possible_moves;
	if(a.solver.loc.first>0 && check(a, Location{a.solver.loc.first--,a.solver.loc.second})){
		possible_moves.push_back(Move::LEFT);
	}
	if(a.solver.loc.first+1<a.x_lim && check(a, Location{a.solver.loc.first++,a.solver.loc.second})){
		possible_moves.push_back(Move::RIGHT);
	}
	if(a.solver.loc.second>0 && check(a, Location{a.solver.loc.first,a.solver.loc.second--})){
		possible_moves.push_back(Move::BACKWARD);
	}
	if(a.solver.loc.second+1<a.y_lim && check(a, Location{a.solver.loc.first,a.solver.loc.second++})){
		possible_moves.push_back(Move::FORWARD);
	}
	return possible_moves;
}

pair<bool,vector<Move>> find_path(Maze a, Maze b, int max=0){
	pair<bool,vector<Move>> path_return;
	if(a==b){
		path_return.first=1;
		return path_return;
	}
	if(a!=b && max==0){
		path_return.first=0;
		return path_return;
	}
	max--;
	for(Move move:get_possible_moves(a)){
		path_return=find_path(update(move,a),b,max);
		if(path_return.first==1){
			path_return.second.insert(path_return.second.begin(),move);
			return path_return;
		}
	}
	return path_return;
}

vector<Move> get_instructions(Maze a, Maze b){
	vector<Move> path;
	pair<bool,vector<Move>> path_return;
	for(unsigned int i=0; i<1000; i++){
		path_return=find_path(a, b, i); 
		if(path_return.first){
			path=path_return.second;
			cout<<"path:"<<path<<endl;
			return path;
		}
	} 
	assert(0);
}

void print_maze(Maze /*a*/){
	
}

Maze make_goal(const Maze a){
	Maze b=a;
	b.solver.loc=a.target;
	b.solver.fin=1;
	return b;
}

int main(){
	Maze maze;
	maze.x_lim=X_LIMIT;
	maze.y_lim=Y_LIMIT;
	Location begin=make_pair(0,0);
	Location target=make_pair(0,5);
	maze.solver.loc=begin;
	maze.target=target;
	cout<<"Welcome to this maze solver!\n";
	Maze goal=make_goal(maze);
	vector<Move> instructions;
	instructions=get_instructions(maze, goal);
	return 0;
}