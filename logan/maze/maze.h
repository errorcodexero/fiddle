#include <string>
#include <vector>

using namespace std;

typedef pair<int,int> Location;
enum class Move{FORWARD, BACKWARD, RIGHT, LEFT};

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

struct Args_return{//A type used to store arguments
	bool import,change_max, import_other, export_maze;
	int x_lim, y_lim;
	string import_filename,export_filename;
	Args_return():import(0),change_max(0),import_other(0),export_maze(0),x_lim(10),y_lim(10),import_filename("maze.txt"),export_filename("maze.txt"){}	
};

ostream& operator<<(ostream& o, Move a);
ostream& operator<<(ostream& o, Location a);
ostream& operator<<(ostream& o, Maze a);
ostream& operator<<(ostream& o,vector<vector<char>> in);
template<typename T>
ostream& operator<<(ostream& o,vector<T> in);

bool operator==(Maze a, Maze b);
bool operator!=(Maze a, Maze b);
template<typename T>
bool operator==(vector<T> a, vector<T> b);

vector<vector<char>> print_maze(Maze a, vector<Move> path=vector<Move>{},bool add_boundary=1,bool print_line=0);

vector<Move> get_path(Maze a);

Maze import_maze(const string filename="maze.txt");

void estimator(const int A);

Maze maze_gen(const int X_LIM=10,const int Y_LIM=10);

void export_maze(const Maze a, const string filename);

int main(int x,char *arg[]);