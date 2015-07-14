/*To do:
	- Get random maze generation to work better (maybe)
	- Bug checking
	- Make maze solving faster
*/
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <assert.h>
#include <fstream>
#include <array>
#include <cstdlib>
#include <stdlib.h> 

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
		for(unsigned int i=0; i<in[j].size(); i++){
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
	int first=m.solver.loc.first, second=m.solver.loc.second;
	switch(a){
		case Move::LEFT:
			assert(m.solver.loc.first>0 && check(m, Location{first-1,second}));
			m.solver.loc.first--;
			break;
		case Move::RIGHT:
			assert(m.solver.loc.first+1<m.x_lim && check(m, Location{first+1,second}));
			m.solver.loc.first++;
			break;
		case Move::BACKWARD:
			assert(m.solver.loc.second>0 && check(m, Location{first,second-1}));
			m.solver.loc.second--;
			break;
		case Move::FORWARD:
			assert(m.solver.loc.second+1<m.y_lim && check(m, Location{first,second+1}));
			m.solver.loc.second++;
			break;
		default:
			assert(0);
	}
	if(m.solver.loc==m.target)m.solver.fin=1;
	else m.solver.fin=0;
	return m;
}

vector<Move> get_possible_moves(const Maze a){
	int first=a.solver.loc.first;
	int second=a.solver.loc.second;
	vector<Move> possible_moves;
	if(a.solver.loc.first>0 && check(a, Location{first-1,second}))possible_moves.push_back(Move::LEFT);
	if(a.solver.loc.first+1<a.x_lim && check(a, Location{first+1,second}))possible_moves.push_back(Move::RIGHT);
	if(a.solver.loc.second>0 && check(a, Location{first,second-1}))possible_moves.push_back(Move::BACKWARD);
	if(a.solver.loc.second+1<a.y_lim && check(a, Location{first,second+1}))possible_moves.push_back(Move::FORWARD);
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

vector<Move> get_path(Maze a, Maze b, unsigned int max_path=40){
	vector<Move> path;
	pair<bool,vector<Move>> path_return;
	for(unsigned int i=0; i<max_path; i++){
		cout<<"Testing paths of length "<<i<<"\n";
		path_return=find_path(a,b,i); 
		if(path_return.first){
			path=path_return.second;
			return path;
		}
	} 
	cout<<"\nWarning: Path length exceeds "<<max_path-1<<": This calculation could take a lot of time to complete or an error may have occurred: line:"<<__LINE__<<"\n";
	exit(44); 
}

void print_maze(const Maze a, vector<Move> path=vector<Move>{}){
	if(a==Maze{})cout<<"Maze is empty\n";
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
			if(j==0 || j==a.y_lim+1 || i==0 || i==a.x_lim+1)maze[j][i]='X';
		}
	}
	Location l=a.solver.loc;
	for(unsigned int i=0; i<path.size(); i++){
		switch(path[i]){
			case Move::FORWARD:
				l.second++;
				break;
			case Move::BACKWARD:
				l.second--;
				break;
			case Move::LEFT:
				l.first--;
				break;
			case Move::RIGHT:
				l.first++;
				break;
			default:
				assert(0);
		}
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

Maze import_maze(const string filename="maze.txt"){
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
		int length=line.size();
		if(length>a.x_lim)a.x_lim=length;
		lines.push_back(line);
		if(line=="")l++;
	}
	for(unsigned int i=0; i<lines.size(); i++){
		int length=lines[i].size();
		if(length<a.x_lim)lines[i]+=" ";
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

struct Args_return{
	bool type, change_max, import_other, generate;
	int new_max, x_lim, y_lim;
	string filename;
	Args_return():type(0),change_max(0),import_other(0),generate(0),new_max(30),x_lim(10),y_lim(10),filename("maze.txt"){}
};

void check_all_args(string arg_str,Args_return& args,char *arg[], bool& valid){
	valid=1;
	string import_cmp="--import",usage_cmp="--usage",default_cmp="--default",max_path_cmp="--set-max-path-to=",gen_cmp="--generate";
	if(arg_str==default_cmp)args.type=0;
	else if(arg_str.substr(0,8)==import_cmp){
		args.type=1;
		if(arg_str.size()>arg_str.substr(0,8).size()){
			args.import_other=1;
			args.filename=arg_str.substr(9,15);
		}
	}
	else if(arg_str.substr(0,18)==max_path_cmp){
		args.change_max=1;
		args.new_max=atoi((arg_str.substr(18)).c_str());
	}
	else if(arg_str.substr(0,10)==gen_cmp){
		args.generate=1;
		if(arg_str.size()>arg_str.substr(0,10).size()){
			int colon_at=0;
			for(unsigned int i=0; i<arg_str.size(); i++)if(arg_str[i]==':'){
				colon_at=i;
				break;
			}
			args.x_lim=atoi((arg_str.substr(11,colon_at)).c_str());
			args.y_lim=atoi((arg_str.substr(colon_at+1)).c_str());
		}
	}
	else if(arg_str==usage_cmp){
		cout<<arg[0]<<" can be used with the following flags:\n";
		cout<<"        --default\n                To run the maze solver on the built-in maze (written in the code)\n";
		cout<<"        --import=<filename>\n                To run the maze solver on an imported maze from the given file (uses maze.txt by default)\n";
		cout<<"        --set-max-path-to=<integer>\n                To set the maximum length of the path that the program will try to find from the solver to the target.";
		cout<<"        --generate=<x_lim>:<y_lim>\n                To randomly generate a maze with the x and y limits set the user input or to ten by default(It will solve it as well).";
		exit(44);
	}
	else valid=0;
}

Args_return use_args(const int x,char *arg[]){
	Args_return args;
	if(x>1){
		string import_cmp="--import",usage_cmp="--usage",default_cmp="--default",max_path_cmp="--set-max-path-to=",gen_cmp="--generate";
		bool valid=0;
		string arg_1_str=string(arg[1]);
		check_all_args(arg_1_str,args,arg,valid);
		if(x>2){
			string arg_2_str=string(arg[2]);
			check_all_args(arg_2_str,args,arg,valid);
		}
		if(!valid){
			cout<<"\nInvalid usage (try: "<<arg[0]<<" --usage)";
			exit(44);
		}
	}
	return args;
}

int get_random(const unsigned int max){
	if(max==0)return 0;
	unsigned int random=(rand()%max);
	return random;
}

bool check_for_wall(const vector<Location> visited, const vector<Location> stack, const Location test){
	if(test==stack.back())return 0;
	for(unsigned int i=0; i<visited.size(); i++){
		int first=test.first, second=test.second;
		bool right=(stack.back()!=Location{first+1,second}), left=(stack.back()!=Location{first-1,second});
		bool forward=(stack.back()!=Location{first,second+1}),backward=(stack.back()!=Location{first,second-1});
		if(
			test==visited[i] ||
			right*(visited[i]==Location{first+1,second}) ||
			left*(visited[i]==Location{first-1,second}) ||
			forward*(visited[i]==Location{first,second+1}) ||
			backward*(visited[i]==Location{first,second-1})
		)return 0;
	}
	return 1;
}

Location update_stack(Location a, const Move b, const vector<Location> visited, const vector<Location> stack, const int first, const int second, const int Y_LIM, const int X_LIM){
	switch(b){
		case Move::FORWARD:
			assert(second+1<Y_LIM && check_for_wall(visited, stack, Location{first,second+1}));
			a.second++;
			break;
		case Move::BACKWARD:
			assert(second>0 && check_for_wall(visited, stack, Location{first,second-1}));
			a.second--;
			break;
		case Move::RIGHT:
			assert(first+1<X_LIM && check_for_wall(visited, stack, Location{first+1,second}));
			a.first++;
			break;
		case Move::LEFT:
			assert(first>0 && check_for_wall(visited, stack, Location{first-1,second}));
			a.first--;
			break;
		default:
			assert(0);		
	}
	return a;
}

pair<vector<Location>, bool> generator(const int X_LIM=10,const int Y_LIM=10, pair<vector<Location>, bool> generator_return=make_pair(vector<Location>{{0,0}},0), vector<Location> stack={}, int counter=0){
	if(counter==0){
		stack.push_back({0,0});
		generator_return.first={Location{0,0}};
		generator_return.second=0;
	}
	if(generator_return.second)return generator_return;
	if(counter>=X_LIM*Y_LIM+100000){
		generator_return.second=0;
		cout<<"Maze generation failed: attempted too many times("<<counter<<"): line:"<<__LINE__<<"\n";
		exit(44);
	}
	counter++;
	if(1){
		vector<Move> possible_moves;
		int first=stack.back().first, second=stack.back().second;
		if(first>0 && check_for_wall(generator_return.first, stack, Location{first-1,second}))possible_moves.push_back(Move::LEFT);
		if(first+1<X_LIM && check_for_wall(generator_return.first, stack, Location{first+1,second}))possible_moves.push_back(Move::RIGHT);
		if(second>0 && check_for_wall(generator_return.first, stack, Location{first,second-1}))possible_moves.push_back(Move::BACKWARD);
		if(second+1<Y_LIM && check_for_wall(generator_return.first, stack, Location{first,second+1}))possible_moves.push_back(Move::FORWARD);
		int random=get_random(possible_moves.size());
		if(possible_moves.size()>0){
			stack.push_back(update_stack(stack.back(),possible_moves[random],generator_return.first,stack,first,second,Y_LIM,X_LIM));
			generator_return.first.push_back(stack.back());
		}
		else{
			stack.pop_back();
		}
		generator_return.second=(stack.size()==0 && generator_return.first.size()>0);
		if(generator_return.second)return generator_return;
		generator_return=generator(X_LIM, Y_LIM, generator_return, stack, counter);
		if(generator_return.second)return generator_return;
	}
	return generator_return;
}

void invert(vector<Location>& v, const int X_LIM, const int Y_LIM){
	vector<Location> full;
	for(int i=0; i<X_LIM; i++){
		for(int j=0; j<Y_LIM; j++){
			full.push_back({i,j});
		}
	}
	vector<unsigned int> to_remove;
	for(unsigned int i=0; i<full.size(); i++){
		for(unsigned int j=0; j<v.size(); j++){
			if(full[i]==v[j])to_remove.push_back(i);
		}
	}
	for(unsigned int i=to_remove.size(); i>0; i--){
		full.erase(full.begin()+to_remove[i-1]);
	}
	v=full;
}

Maze maze_gen(const int X_LIM=10,const int Y_LIM=10){
	Maze a;
	a.x_lim=X_LIM;
	a.y_lim=Y_LIM;
	pair<vector<Location>,bool> generator_return=generator(X_LIM,Y_LIM);
	vector<Location> walls=((generator_return.first).size()>0)?generator_return.first:vector<Location>{};
	a.blocks=walls;
	invert(a.blocks,X_LIM,Y_LIM);
	vector<Location> possible_locs;
	for(int i=0; i<X_LIM; i++){
		for(int j=0; j<Y_LIM; j++){
			possible_locs.push_back(Location{i,j});
		}
	}
	vector<int> to_remove;
	for(unsigned int j=0; j<possible_locs.size(); j++){
		for(unsigned int i=0; i<a.blocks.size(); i++){
			if(possible_locs[j]==a.blocks[i])to_remove.push_back(j);
		}
	}
	for(unsigned int i=to_remove.size(); i>0; i--){
		possible_locs.erase(possible_locs.begin()+to_remove[i-1]);
	}
	if(possible_locs.size()<2){
		cout<<"Error: Not enough locations for the start and target to be set: line: "<<__LINE__<<"\n";
		exit(44);
	}
	int random=get_random(possible_locs.size());
	a.target=possible_locs[random];
	possible_locs.erase(possible_locs.begin()+random);
	a.solver.loc=possible_locs[get_random(possible_locs.size())];
	print_maze(a);
	return a;
}

int main(int x,char *arg[]){
	Args_return args=use_args(x,arg);
	int max_path=args.change_max?(args.new_max+1):45;
	cout<<"Welcome to this maze solver!\n('S' is the start. 'T' is the target. 'X' is a barrier.)\n\n";
	Maze maze, goal;
	vector<Move> path;
	if(args.generate){
		srand(time(NULL));
		maze=maze_gen(args.x_lim,args.y_lim);
	}
	else if(!args.type){
		maze.x_lim=X_LIMIT;
		maze.y_lim=Y_LIMIT;
		maze.blocks=BLOCKS;
		maze.solver.loc=SOLVER_ORIGIN;
		maze.target=TARGET_LOCATION;
	}
	else{
		maze=args.import_other?import_maze(args.filename):import_maze();
	}
	goal=make_goal(maze);
	path=get_path(maze, goal, max_path);
	print_maze(maze,path);
	cout<<"\nThe path used is:\n"<<path<<"\n";
	return 0;
}