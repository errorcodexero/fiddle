/*TODO:
	- Generating large mazes doesn't work
	- Make maze solving faster
	- Bug checking
	- Get rid of in code maze
*/
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <assert.h>
#include <fstream>
#include <cstdlib>
#include <stdlib.h> 

using namespace std;

typedef pair<int,int> Location;
enum class Move{FORWARD, BACKWARD, RIGHT, LEFT};

//Edit the following to change the default maze (Alternatively, edit the accompanying maze.txt or generate a random maze):
static const int X_LIMIT=10, Y_LIMIT=10;
static const Location TARGET_LOCATION=Location{0,5}, SOLVER_ORIGIN=Location{0,0};
static const vector<Location> BLOCKS={Location{0,3}};
//End.

ostream& operator<<(ostream& o, Move a){
	#define X(name) if(a==Move::name)o<<""#name;
	X(FORWARD) X(RIGHT) X(BACKWARD) X(LEFT)
	#undef X
	return o;
}

struct Maze{//Contains the necessary maze information
	struct Solver{//Contains the necessary solver information
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
	return o<<">";
}

ostream& operator<<(ostream& o, Maze a){
	return o<<"Solver(loc:"<<a.solver.loc<<" fin:"<<a.solver.fin<<") target:"<<a.target<<" blocks("<<a.blocks<<") x_lim:"<<a.x_lim<<" y.lim:"<<a.y_lim;
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

ostream& operator<<(ostream& o,vector<vector<char>> in){//Special print-out for the maze vector of characters
	for(unsigned int j=0; j<in.size(); j++){
		for(unsigned int i=0; i<in[j].size(); i++){
			o<<in[j][i];
		}
		o<<"\n";
	}
	return o;
}

bool check_for_wall(const Maze a, const Location l){//Checks to see if a wall occupies a location
	for(unsigned int i=0; i<a.blocks.size(); i++){
		if(l==a.blocks[i])return 0;
	}
	return 1;
}

Maze update(const Move a, Maze m){//Updates a maze given a move
	int first=m.solver.loc.first, second=m.solver.loc.second;
	switch(a){
		case Move::LEFT:
			assert(first>0 && check_for_wall(m, Location{first-1,second}));
			m.solver.loc.first--;
			break;
		case Move::RIGHT:
			assert(first+1<m.x_lim && check_for_wall(m, Location{first+1,second}));
			m.solver.loc.first++;
			break;
		case Move::BACKWARD:
			assert(second>0 && check_for_wall(m, Location{first,second-1}));
			m.solver.loc.second--;
			break;
		case Move::FORWARD:
			assert(second+1<m.y_lim && check_for_wall(m, Location{first,second+1}));
			m.solver.loc.second++;
			break;
		default:
			assert(0);
	}
	m.solver.fin=(m.solver.loc==m.target);
	return m;
}

vector<Move> get_possible_moves(const Maze a){//Returns possible moves
	int first=a.solver.loc.first, second=a.solver.loc.second;
	vector<Move> possible_moves;
	if(first>0 && check_for_wall(a, Location{first-1,second})) possible_moves.push_back(Move::LEFT);
	if(first+1<a.x_lim && check_for_wall(a, Location{first+1,second})) possible_moves.push_back(Move::RIGHT);
	if(second>0 && check_for_wall(a, Location{first,second-1})) possible_moves.push_back(Move::BACKWARD);
	if(second+1<a.y_lim && check_for_wall(a, Location{first,second+1})) possible_moves.push_back(Move::FORWARD);
	return possible_moves;
}

vector<Move> find_path(const Maze a,bool& found, int max){//Recursive path finder
	vector<Move> path;
	found=a.solver.fin;
	if(found) return path;
	if(max==0) return path;
	max--;
	for(Move move:get_possible_moves(a)){
		path=find_path(update(move,a),found,max);
		if(found){
			path.insert(path.begin(),move);
			return path;
		}
	}
	return path;
}

vector<Move> get_path(const Maze a, unsigned int max_path=45){//Tries to get a path of the shortest length
	if(a.solver.loc==a.target)return vector<Move>{};
	for(unsigned int i=0; i<max_path; i++){
		bool found=0;
		cout<<"Testing paths of length "<<i<<"\n";
		vector<Move> path=find_path(a,found,i); 
		if(found) return path;
	} 
	cout<<"\nWarning: Path length exceeds "<<max_path-1<<": This calculation could take a lot of time to complete or an error may have occurred: line:"<<__LINE__<<"\n";
	exit(44); 
}

void add_border(Maze& a){//Ads a border to a given maze
	a.x_lim+=2;
	a.y_lim+=2;
	a.target=Location{a.target.first+1,a.target.second+1};
	a.solver.loc=Location{a.solver.loc.first+1,a.solver.loc.second+1};
	for(unsigned int i=0; i<a.blocks.size(); i++){
		a.blocks[i]=Location{a.blocks[i].first+1,a.blocks[i].second+1};
	}
	for(int i=0; i<a.x_lim; i++){
		a.blocks.push_back(Location{i,0});
		a.blocks.push_back(Location{i,a.y_lim-1});
	}
	for(int i=0; i<a.y_lim; i++){
		a.blocks.push_back(Location{0,i});
		a.blocks.push_back(Location{a.x_lim-1,i});
	}
}

vector<vector<char>> print_maze(Maze a, vector<Move> path=vector<Move>{},bool add_boundary=1,bool print=1){//Prints out a maze as a graphic
	if(add_boundary)add_border(a);
	vector<vector<char>> maze;
	for(int j=0; j<a.y_lim; j++){//Makes a maze-sized print-out vector
		maze.push_back(vector<char>{});
		for(int i=0; i<a.x_lim; i++){
			maze[j].push_back(' ');
		}
	}
	for(unsigned int i=0; i<a.blocks.size(); i++){
		maze[a.y_lim-a.blocks[i].second-1][a.blocks[i].first]='X';//draw blocks
	}
	Location l=a.solver.loc;
	for(unsigned int i=0; i<path.size(); i++){//Draw path
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
		maze[a.y_lim-l.second-1][l.first]='-';
	}
	maze[a.y_lim-a.solver.loc.second-1][a.solver.loc.first]='S';//Draw solver
	maze[a.y_lim-a.target.second-1][a.target.first]='T';//Draw target
	if(print)cout<<maze;
	return maze;
}

Maze import_maze(const string filename="maze.txt"){//Imports a maze from maze.txt or the given text file
	Maze a;
	ifstream maze;
	maze.open(filename);
	vector<string> lines;
	int iterator=0,blank_lines=0;
	while(!maze.eof()){
		iterator++;
		string line;
		getline(maze,line);
		for(unsigned int i=0; i<line.size(); i++){
			if(line[i]=='\r')line.erase(line.begin()+i);
		}
		int length=line.size();
		if(length==0)blank_lines++;
		if(length>a.x_lim)a.x_lim=length;
		lines.push_back(line);
	}
	if(iterator==blank_lines){
		cout<<"\nError: Imported file \""<<filename<<"\" does not contain a maze: line:"<<__LINE__<<"\n";
		exit(44); 
	}
	for(unsigned int i=0; i<lines.size(); i++){
		int length=lines[i].size();
		if(length<a.x_lim)lines[i]+=" ";
	}
	a.y_lim=iterator;
	for(int i=0; i<a.y_lim; i++){
		string line=lines[a.y_lim-1-i];
		for(int j=0; j<a.x_lim; j++){
			if(line[j]=='X')a.blocks.push_back(Location{j,i});
			else if(line[j]=='S')a.solver.loc=Location{j,i};
			else if(line[j]=='T')a.target=Location{j,i};	
		}
	}
	maze.close();
	cout<<"The imported maze is:\n";
	print_maze(a);
	return a;
}

struct Args_return{//A type used to store arguments
	bool type, change_max, import_other, generate, export_maze;
	int new_max, x_lim, y_lim;
	string filename,export_filename;
	Args_return():type(0),change_max(0),import_other(0),generate(0),export_maze(0),new_max(30),x_lim(10),y_lim(10),filename("maze.txt"),export_filename("maze.txt"){}
};

void check_all_args(string arg_str,Args_return& args,char *arg[], bool& valid){//Uses passed into arguments to set the necessary settings
	valid=1;
	string import_cmp="--import",usage_cmp="--usage",default_cmp="--default",max_path_cmp="--set-max-path-to=",gen_cmp="--generate",export_maze="--export";
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
			for(unsigned int i=0; i<arg_str.size(); i++){
				if(arg_str[i]==':'){
					colon_at=i;
					break;
				}
			}
			args.x_lim=atoi((arg_str.substr(11,colon_at)).c_str());
			args.y_lim=atoi((arg_str.substr(colon_at+1)).c_str());
		}
	}
	else if(arg_str==usage_cmp){
		cout<<arg[0]<<" can be used with the following flags:\n";
		cout<<"\t--default\n\t\tTo run the maze solver on the built-in maze (written in the code)\n";
		cout<<"\t--import=<filename>\n\t\tTo run the maze solver on an imported maze from the given file (uses \"maze.txt\" by default)\n";
		cout<<"\t--set-max-path-to=<integer>\n\t\tTo set the maximum length of the path that the program will try to find from the solver to the target.\n";
		cout<<"\t--generate=<x_lim>:<y_lim>\n\t\tTo randomly generate a maze with the x and y limits set the user input or to ten by default(It will solve it as well).\n";
		cout<<"\t--export=<filename>\n\t\tTo write the used maze to a given file (uses \"maze.txt\" by default).\n";
		exit(44);
	}
	else if(arg_str.substr(0,8)==export_maze){
		args.export_maze=1;
		if(arg_str.size()>arg_str.substr(0,9).size())args.export_filename=arg_str.substr(9);
	}
	else valid=0;
}

Args_return use_args(const int x,char *arg[]){//Determines what arguments to use
	Args_return args;
	for(int i=1; i<x; i++){
		bool valid=0;
		string arg_str=string(arg[i]);
		check_all_args(arg_str,args,arg,valid);
		if(!valid){
			cout<<"\nInvalid usage (try: "<<arg[0]<<" --usage)";
			exit(44);
		}
	}
	return args;
}

int get_random(const unsigned int max){//Returns a random integer less than the passed in integer 
	return (max>0)?(rand()%max):0;
}

bool check_for_adjacent_wall(const vector<Location> visited, const vector<Location> stack, const Location test){//Checks a location to see if there are any walls in adjacent locations 
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

Location update_location(Location a,const Move b,const vector<Location> visited,const vector<Location> stack,const int first,const int second,const int Y_LIM,const int X_LIM){//Updates a location (used in wall generation)
	switch(b){
		case Move::FORWARD:
			assert(second+1<Y_LIM && check_for_adjacent_wall(visited, stack, Location{first,second+1}));
			a.second++;
			break;
		case Move::BACKWARD:
			assert(second>0 && check_for_adjacent_wall(visited, stack, Location{first,second-1}));
			a.second--;
			break;
		case Move::RIGHT:
			assert(first+1<X_LIM && check_for_adjacent_wall(visited, stack, Location{first+1,second}));
			a.first++;
			break;
		case Move::LEFT:
			assert(first>0 && check_for_adjacent_wall(visited, stack, Location{first-1,second}));
			a.first--;
			break;
		default:
			assert(0);		
	}
	return a;
}

pair<vector<Location>, bool> wall_generator(const int X_LIM=10,const int Y_LIM=10,pair<vector<Location>,bool> generator_return=make_pair(vector<Location>{{0,0}},0),vector<Location> stack={},int counter=0){//generates the walls for a maze
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
		if(first>0 && check_for_adjacent_wall(generator_return.first, stack, Location{first-1,second})) possible_moves.push_back(Move::LEFT);
		if(first+1<X_LIM && check_for_adjacent_wall(generator_return.first, stack, Location{first+1,second})) possible_moves.push_back(Move::RIGHT);
		if(second>0 && check_for_adjacent_wall(generator_return.first, stack, Location{first,second-1})) possible_moves.push_back(Move::BACKWARD);
		if(second+1<Y_LIM && check_for_adjacent_wall(generator_return.first, stack, Location{first,second+1})) possible_moves.push_back(Move::FORWARD);
		int random=get_random(possible_moves.size());
		if(possible_moves.size()>0){
			stack.push_back(update_location(stack.back(),possible_moves[random],generator_return.first,stack,first,second,Y_LIM,X_LIM));
			generator_return.first.push_back(stack.back());
		}
		else{
			stack.pop_back();
		}
		generator_return.second=(stack.size()==0 && generator_return.first.size()>0);
		if(generator_return.second)return generator_return;
		generator_return=wall_generator(X_LIM, Y_LIM, generator_return, stack, counter);
		if(generator_return.second)return generator_return;
	}
	return generator_return;
}

vector<Location> invert(vector<Location> v, const int X_LIM, const int Y_LIM){//Inverts a vector of Locations to contain the opposite Locations within x/y boundaries
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
	return v;
}

Maze maze_gen(const int X_LIM=10,const int Y_LIM=10){//Generates a random maze
	Maze a;
	a.x_lim=X_LIM;
	a.y_lim=Y_LIM;
	a.blocks=invert(wall_generator(a.x_lim,a.y_lim).first,a.x_lim,a.y_lim);
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
	cout<<"The generated maze is:\n";
	print_maze(a);
	return a;
}

void export_maze(const Maze a, const string filename){
	cout<<"File \""<<filename<<"\" will be overwritten. Are you sure you want to export the generated maze?(y/n) ";
	char yn;
	cin.get(yn);
	if(yn!='y')exit(44);
	ofstream export_maze;
	export_maze.open(filename);	
	vector<vector<char>> maze=print_maze(a,{},0,0);
	for(unsigned int i=0; i<maze.size(); i++){
		for(unsigned int j=0; j<maze[i].size(); j++){
			export_maze<<maze[i][j];
		}
		if(i<maze.size()-1)export_maze<<"\r\n";
	}
	export_maze.close();
	cout<<"Export succeeded!\n";
}

int main(int x,char *arg[]){
	Args_return args=use_args(x,arg);
	Maze maze;
	cout<<"Welcome to this maze solver!\n('S' is the start. 'T' is the target. '-' is the path. 'X' is a barrier.)\n\n";
	if(args.generate){
		srand(time(NULL));
		maze=maze_gen(args.x_lim,args.y_lim);
	}
	else if(!args.type){
		cout<<"The default maze is:\n";
		maze.x_lim=X_LIMIT;
		maze.y_lim=Y_LIMIT;
		maze.blocks=BLOCKS;
		maze.solver.loc=SOLVER_ORIGIN;
		maze.target=TARGET_LOCATION;
		print_maze(maze);
	}
	else maze=args.import_other?import_maze(args.filename):import_maze();	
	vector<Move> path=get_path(maze, args.change_max?(args.new_max+1):45);
	cout<<"The solution is:\n";
	print_maze(maze,path);
	cout<<"\n\nThe path used is:\n"<<path<<"\n\n";
	if(args.export_maze)export_maze(maze,args.export_filename);
	return 0;
}