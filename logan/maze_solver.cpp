/*To do:
	- Get random maze generation to work
	- Get the get_random function to be more random
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

vector<Move> get_path(Maze a, Maze b, unsigned int max_path=100000000){
	vector<Move> path;
	pair<bool,vector<Move>> path_return;
	unsigned int i=0;
	for(; i<max_path; i++){
		path_return=find_path(a,b,i); 
		if(path_return.first){
			path=path_return.second;
			return path;
		}
	} 
	cout<<"\nWarning: Path length exceeds "<<i-1<<" -- This calculation could take a few more minutes to complete or an error may have occurred: line:"<<__LINE__<<"\n";
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

struct Args_return{
	bool type, change_max, import_other, generate;
	int new_max;
	string filename;
	Args_return():type(0),change_max(0),import_other(0),new_max(100000000),filename("maze.txt"){}
};

void check_both_args(string arg_str,Args_return& args,char *arg[], bool& valid){
	string import_cmp="--import",usage_cmp="--usage",default_cmp="--default",max_path_cmp="--set-max-path-to=",gen_cmp="--generate";
	if(arg_str==default_cmp){
		valid=1;
		args.type=0;
	}
	if(arg_str.substr(0,8)==import_cmp){
		valid=1;
		args.type=1;
		if(arg_str.size()>arg_str.substr(0,8).size()){
			args.import_other=1;
			args.filename=arg_str.substr(9,15);
		}
	}
	if(arg_str.substr(0,18)==max_path_cmp){
		valid=1;
		args.change_max=1;
		args.new_max=atoi((arg_str.substr(18)).c_str());
	}
	if(arg_str.substr(0,10)==gen_cmp){
		valid=1;
		args.generate=1;
	}
	if(arg_str==usage_cmp){
		valid=1;
		cout<<arg[0]<<" can be used with the following flags:\n 	--default\n 		To run the maze solver on the built-in maze (written in the code)\n	--import=<filename>\n		To run the maze solver on an imported maze from the given file (uses maze.txt by default)\n	--set-max-path-to=<integer>\n 		To set the maximum length of the path that the program will try to find from the solver to the target.";
		exit(44);
	}
}

Args_return use_args(const int x,char *arg[]){
	Args_return args;
	if(x>1){
		string import_cmp="--import",usage_cmp="--usage",default_cmp="--default",max_path_cmp="--set-max-path-to=",gen_cmp="--generate";
		bool valid=0;
		string arg_1_str=string(arg[1]);
		check_both_args(arg_1_str,args,arg,valid);
		if(x>2){
			string arg_2_str=string(arg[2]);
			check_both_args(arg_2_str,args,arg,valid);
		}
		if(!valid){
			cout<<"\nInvalid usage (check: "<<arg[0]<<" --usage)";
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
	//cout<<"NEW ";
	for(unsigned int i=0; i<visited.size(); i++){
		int first=test.first, second=test.second;
		bool right=(stack.back()!=Location{first+1,second}), left=(stack.back()!=Location{first-1,second}), forward=(stack.back()!=Location{first,second+1}),backward=(stack.back()!=Location{first,second-1});
		//cout<<"test:"<<test<<" visited:"<<visited[i]<<"left:"<<left<<" right:"<<right<<" forward:"<<forward<<" backward:"<<backward<<"\n";
		if(
			test==visited[i] ||
			right*(visited[i]==Location{first+1,second}) ||
			left*(visited[i]==Location{first-1,second}) ||
			forward*(visited[i]==Location{first,second+1}) ||
			backward*(visited[i]==Location{first,second-1})
		){
			//cout<<" returned:0\n";
			return 0;
		}
	}
	//cout<<" returned:1\n";
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

pair<vector<Location>, bool> generator(pair<vector<Location>, bool> generator_return=make_pair(vector<Location>{{0,0}},0), vector<Location> stack={}, const int X_LIM=10,const int Y_LIM=10, int counter=0){
	if(counter==0){
		stack.push_back({0,0});
		generator_return.first={Location{0,0}};
		generator_return.second=0;
	}
	if(generator_return.second){
		cout<<"\nfinal:"<<generator_return.first<<"\n";
		return generator_return;
	}
	if(0){//counter>=X_LIM*Y_LIM){
		generator_return.second=0;
		cout<<"Generation failed: "<<__LINE__<<"\n";
		exit(44);
	}
	counter++;
	if(1){
		vector<Move> possible_moves;
		int first=stack.back().first, second=stack.back().second;
		//cout<<"\nfinding{\n";
		//cout<<"LEFT:\n";
		if(first>0 && check_for_wall(generator_return.first, stack, Location{first-1,second})){
			possible_moves.push_back(Move::LEFT);
		}
		//cout<<"RIGHT:\n";
		if(first+1<X_LIM && check_for_wall(generator_return.first, stack, Location{first+1,second})){
			possible_moves.push_back(Move::RIGHT);
		}
		//cout<<"BACKWARD:\n";
		if(second>0 && check_for_wall(generator_return.first, stack, Location{first,second-1})){
			possible_moves.push_back(Move::BACKWARD);
		}
		//cout<<"FORWARD:\n";
		if(second+1<Y_LIM && check_for_wall(generator_return.first, stack, Location{first,second+1})){
			possible_moves.push_back(Move::FORWARD);
		}
		//cout<<"}found\n";
		int random=get_random(possible_moves.size());
		//cout<<"\nvisited"<<generator_return.first<<" \nstack"<<stack;
		if(possible_moves.size()>0){
			//cout<<"moves:"<<possible_moves<<"   rand:"<<possible_moves[random]<<"\n";
			stack.push_back(update_stack(stack.back(),possible_moves[random],generator_return.first,stack,first,second,Y_LIM,X_LIM));
			generator_return.first.push_back(stack.back());
		}
		else{
			stack.pop_back();
			//cout<<"OFF STACK";
		}
		generator_return.second=(stack.size()==0 && generator_return.first.size()>0);
		if(generator_return.second){
			return generator_return;
		}
		//cout<<"\ncounter: "<<counter<<"\n";
		generator_return=generator(generator_return, stack, X_LIM, Y_LIM, counter);
		if(generator_return.second)return generator_return;
	}
	//cout<<"return end visited:"<<generator_return.first<<"\n";
	return generator_return;
}

Maze maze_gen(const int X_LIM=10,const int Y_LIM=10){
	srand(time(NULL));
	Maze a;
	a.x_lim=X_LIM;
	a.y_lim=Y_LIM;
	pair<vector<Location>,bool> generator_return=generator();
	vector<Location> walls=((generator_return.first).size()>0)?generator_return.first:vector<Location>{};
	a.blocks=walls;
	cout<<"blocks:"<<a.blocks<<"\n\n";
	bool set=0;
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
	cout<<"possible_locs:"<<possible_locs<<"\n";
	while(!set){
		for(unsigned int i=0; i<possible_locs.size(); i++){
			int r1=get_random(X_LIM), r2=get_random(Y_LIM);
			if(Location{r1,r2}==possible_locs[i]){
				a.target={r1,r2};
				possible_locs.erase(possible_locs.begin()+i);
				set=1;
				break;
			}
		}
	}
	set=0;
	while(!set){
		for(unsigned int i=0; i<possible_locs.size(); i++){
			int r1=get_random(X_LIM), r2=get_random(Y_LIM);
			cout<<possible_locs[i]<<"   "<<Location{r1,r2}<<"\n";
			if(Location{r1,r2}==possible_locs[i]){
				a.solver.loc={r1,r2};
				set=1;
				break;
			}
		}
	}
	cout<<"\ntarget:"<<a.target<<"   solver:"<<a.solver.loc<<"\n";
	print_maze(a);
	return a;
}

int main(int x,char *arg[]){
	Args_return args=use_args(x,arg);
	int max_path=args.change_max?args.new_max+1:100000000;
	cout<<"Welcome to this maze solver!\n('S' is the solver's origin. 'T' is the target. 'X' is a barrier.)\n\n";
	Maze maze;
	if(args.generate)maze=maze_gen();
	if(!args.type){
		if(!args.generate){
			maze.x_lim=X_LIMIT;
			maze.y_lim=Y_LIMIT;
			maze.blocks=BLOCKS;
			maze.solver.loc=SOLVER_ORIGIN;
			maze.target=TARGET_LOCATION;
		}
		Maze goal=make_goal(maze);
		vector<Move> path;
		path=get_path(maze, goal, max_path);
		print_maze(maze,path);
		cout<<"\nThe path used is:\n"<<path<<"\n";
	}
	else if(args.type){
		maze=args.import_other?import_maze(args.filename):import_maze();
		Maze goal=make_goal(maze);
		vector<Move> path;
		path=get_path(maze, goal,max_path);
		print_maze(maze,get_path(maze,goal,max_path));
		cout<<"\nThe path used is:\n"<<path<<"\n";
	}
	return 0;
}