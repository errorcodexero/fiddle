/*To do:
	- Auto/random generate maze functionality
	- Change maximum path length from command line as well as import file
	- Reconsider "--default" flag
*/
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <assert.h>
#include <fstream>
#include <array>
#include <cstdlib>

using namespace std;

typedef pair<int,int> Location;
enum class Move{FORWARD, BACKWARD, RIGHT, LEFT};

//Edit the following to change the default maze (Alternatively edit the accompanying maze.txt):
static const int X_LIMIT=10, Y_LIMIT=10;
static const Location TARGET_LOCATION=Location{0,5};
static const Location SOLVER_ORIGIN=Location{0,0};
static const vector<Location> BLOCKS={Location{0,3}};
//End.

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
		Solver():loc(Location{0,0}),fin(0){}
	};
	vector<Location> blocks;
	int x_lim,y_lim;
	Location target;
	Solver solver;
	Maze():blocks(vector<Location>{}),x_lim(0),y_lim(0),target(Location{0,0}){}
};

ostream& operator<<(ostream& o, Location a){
	return o<<"<"<<a.first<<" "<<a.second<<">";
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

ostream& operator<<(ostream& o, Maze a){
	o<<"Solver("<<a.solver.loc<<" "<<a.solver.fin<<") target:"<<a.target<<" blocks("<<a.blocks<<") X_LIMIT:"<<a.x_lim<<" Y_LIMIT:"<<a.y_lim;
	return o;
}

template<typename T>
bool operator==(vector<T> a, vector<T> b){
	for(unsigned int i=0; i<a.size(); i++){
		if(a[i]!=b[i])return 0; 
	
	}
	return 1;
}

bool operator==(Maze a, Maze b){
	return (a.x_lim==b.x_lim && a.y_lim==b.y_lim && a.solver.loc==b.solver.loc && a.solver.fin==b.solver.fin && a.blocks==b.blocks && a.target==b.target);
}

bool operator!=(Maze a, Maze b){
	return !(a==b);
}

ostream& operator<<(ostream& o,vector<vector<char>> in){
	for(unsigned int j=0; j<in.size(); j++){
		for(unsigned int i=0; i<in.size(); i++){
			o<<in[j][i];
		}
		cout<<"\n";
	}
	return o;
}

bool check(const Maze a, const Location l){
	if(a.blocks.size()==0)return 1;
	for(unsigned int i; i<a.blocks.size(); i++){
		if(l==a.blocks[i])return 0;
	}
	return 1;
}

Maze update(const Move a, Maze m){
	int first=m.solver.loc.first;
	int second=m.solver.loc.second;
	if(a==Move::LEFT){
		assert(m.solver.loc.first>0 && check(m, Location{first-1,second}));
		m.solver.loc.first--;
	}
	else if(a==Move::RIGHT){
		assert(m.solver.loc.first+1<m.x_lim && check(m, Location{first+1,second}));
		m.solver.loc.first++;
	}
	else if(a==Move::BACKWARD){
		assert(m.solver.loc.second>0 && check(m, Location{first,second-1}));
		m.solver.loc.second--;
	}
	else if(a==Move::FORWARD){
		assert(m.solver.loc.second+1<m.y_lim && check(m, Location{first,second+1}));
		m.solver.loc.second++;
	}
	if(m.solver.loc==m.target)m.solver.fin=1;
	else m.solver.fin=0;
	return m;
}

vector<Move> get_possible_moves(const Maze a){
	int first=a.solver.loc.first;
	int second=a.solver.loc.second;
	vector<Move> possible_moves;
	if(a.solver.loc.first>0 && check(a, Location{first-1,second})){
		possible_moves.push_back(Move::LEFT);
	}
	if(a.solver.loc.first+1<a.x_lim && check(a, Location{first+1,second})){
		possible_moves.push_back(Move::RIGHT);
	}
	if(a.solver.loc.second>0 && check(a, Location{first,second-1})){
		possible_moves.push_back(Move::BACKWARD);
	}
	if(a.solver.loc.second+1<a.y_lim && check(a, Location{first,second+1})){
		possible_moves.push_back(Move::FORWARD);
	}
	return possible_moves;
}

pair<bool,vector<Move>> find_path(Maze a, Maze b, int max=0){
	pair<bool,vector<Move>> path_return;
	if(a.solver.fin){
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

vector<Move> get_path(Maze a, Maze b){
	vector<Move> path;
	pair<bool,vector<Move>> path_return;
	unsigned int i=0;
	for(; i<100000000; i++){
		path_return=find_path(a,b,i); 
		if(path_return.first){
			path=path_return.second;
			return path;
		}
	} 
	cout<<"\nWarning: Path length exceeds "<<i<<" -- This calculation could take a few more minutes to complete or an error may have occurred: line:"<<__LINE__<<"\n";
	exit(44); 
}

void print_maze(const Maze a, vector<Move> path=vector<Move>{}){
	//if(a==Maze{})cout<<"Maze is empty\n";
	vector<vector<char>> maze;
	for(int j=0; j<a.y_lim+2; j++){//Makes a maze-sized print-out vector
		maze.push_back(vector<char>{});
		for(int i=0; i<a.x_lim+2; i++){
			maze[j].push_back(' ');
		}
	}
	maze[a.y_lim-a.solver.loc.second][a.solver.loc.first+1]='S';//Draw solver
	for(unsigned int i=0; i<a.blocks.size(); i++){
		maze[a.y_lim-a.blocks[i].second][a.blocks[i].first+1]='X';//draw block
	}
	for(int j=0; j<a.y_lim+2; j++){//Draw border
		for(int i=0; i<a.x_lim+2; i++){
			if(j==0 || j==a.y_lim+1)maze[j][i]='X';
			if(i==0 || i==a.x_lim+1)maze[j][i]='X';
		}
	}
	Location l=a.solver.loc;
	for(unsigned int i=0; i<path.size(); i++){
		if(path[i]==Move::FORWARD)l.second++;
		else if(path[i]==Move::BACKWARD)l.second--;
		else if(path[i]==Move::LEFT)l.first--;
		else if(path[i]==Move::RIGHT)l.first++;
		maze[a.y_lim-l.second][l.first+1]='-';
	}
	maze[a.y_lim-a.target.second][a.target.first+1]='T';//Draw target
	cout<<maze;
}

Maze make_goal(const Maze a){
	Maze b=a;
	b.solver.loc=a.target;
	b.solver.fin=1;
	return b;
}

Maze import_maze(string filename="maze.txt"){
	Maze a;
	a.solver.fin=0;
	ifstream maze;
	maze.open(filename);
	vector<string> lines;
	int k=0,l=0;
	while(!maze.eof()){
		k++;
		string line;
		getline(maze,line);
		for(unsigned int i=0; i<line.size(); i++){
			if(line[i]=='\r')line.erase(line.begin()+i);
		}
		a.x_lim=line.size();
		lines.push_back(line);
		if(line=="")l++;
	}
	if(k==l){
		cout<<"\nError: Imported file \""<<filename<<"\" does not contain a maze: line:"<<__LINE__<<"\n";
		exit(44); 
	}
	else{
		a.y_lim=k;
		for(int i=0; i<a.y_lim; i++){
			string line=lines[a.y_lim-1-i];
			for(int j=0; j<a.x_lim; j++){
				if(line[j]=='X')a.blocks.push_back(Location{j,i});
				else if(line[j]=='S')a.solver.loc=Location{j,i};
				else if(line[j]=='T')a.target=Location{j,i};	
			}
		}
	}
	maze.close();
	return a;
}

int main(int x,char *import[]){
	if(x!=2)cout<<"\nInvalid usage (check: "<<import[0]<<" --options)";
	else{
		char import_cmp[]={"--import"};
		char options_cmp[]={"--options"};
		char default_cmp[]={"--default"};
		if(string(import[1])==string(default_cmp)){
			cout<<"Welcome to this maze solver!\n('S' is the solver's origin. 'T' is the target. 'X' is a barrier.)\n\n";
			Maze maze;
			maze.x_lim=X_LIMIT;
			maze.y_lim=Y_LIMIT;
			maze.blocks=BLOCKS;
			maze.solver.loc=SOLVER_ORIGIN;
			maze.target=TARGET_LOCATION;
			Maze goal=make_goal(maze);
			vector<Move> path;
			path=get_path(maze, goal);
			print_maze(maze,path);
			cout<<"\nThe path used is:\n"<<path<<"\n";
		}
		else if(string(import[1])==string(import_cmp)){
			cout<<"Welcome to this maze solver!\n('S' is the solver's origin. 'T' is the target. 'X' is a barrier.)\n\n";
			Maze imported=import_maze();
			Maze goal=make_goal(imported);
			vector<Move> path;
			path=get_path(imported, goal);
			print_maze(imported,get_path(imported,goal));
			cout<<"\nThe path used is:\n"<<path<<"\n";
		}
		else if(string(import[1])==string(options_cmp)){
			cout<<import[0]<<" can be used with the following flags:\n        --default\n                To run the maze solver on the built-in maze (written in the code)\n \
			--import\n                To run the maze solver on an imported maze from maze.txt";
		}
		else cout<<import[0]<<": error: no such option: "<<import[1]<<"\n";
	}
	return 0;
}