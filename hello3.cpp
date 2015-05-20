#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <sstream>
using namespace std;
ostream&operator<<(ostream&o,vector<pair<int,int> > v){
	for(unsigned x = 0;x < v.size();x++){
		o<<v.at(x).first;
		o<<v.at(x).second<<"\n";
	}
	return o;
}

ostream&operator<<(ostream&o,map<pair<T,T>,vector<pair<T,T>>> v){
	for(pair<pair<int,int>,vector<pair<int,int>>> p:v){
		//o<<"Key X: "<<p.first.first<<" Key Y: "<<p.first.second<<"\n";
					
		
		//o<<"Option X: "<<x.first<<" Option Y: "<<x.second<<"\n";
		
	}
	return o;
}
osream&operator<<(ostream&o,pair<int,int> v){
	o<<"first: "<<v.first<<"\n";
	o<<"second: "<<v.second"\n";
	return o;
}
template<typename T>
ostream&operator<<(ostream& o,vector<T> v){
	o<<"(";
	for(T t:v){
		o<<t;
	}
	return o<<")";
}

ostream&operator<<(ostream&o,vector<vector<int> > v){
	if(v.size() > 0){
		unsigned boardLength = v.size();
		unsigned boardWidth = v.at(0).size();
		for(unsigned y = 0; y < boardLength; y++){
			std::cout<<"[";
			//change for statment to accept none rectangle arrays
			for(unsigned x = 0;x < boardWidth;x++){
				std::cout<<	","<<v.at(y).at(x);	
			}				
			std::cout<<"]";
			std::cout<<"\n";
		}
	}
	return o;
}
enum Dir{RIGHT,LEFT,UP,DOWN};
ostream&operator<<(ostream&o,vector<Dir> dir){

	for(int x = 0;x < (int)dir.size();x++){
		Dir a = dir[x];
		if(a == Dir::RIGHT){
		o<< "Right ";
		}else if(a == Dir::LEFT){
		o<< "Left ";
		}else if(a == Dir::UP){
		o<< "Up ";
		}else if(a == Dir::DOWN){
		o<< "Down ";
		}
	}
	o<< "Finish";
	return o;
}
/*
vector<Dir> tellPath(vector<Dir> instructions,vector<vector<int> >board,int x,int y,int end){
	unsigned boardLength = board.size();
	unsigned boardWidth = board.at(0).size();
	//std::cout<<"hi1 \n";
	int step = board[y][x]-1;
	//std::cout<<step<<"\n"<<end<<"\n"<<x<<"\n"<<y<<"\n";
	if(board[y][x] == end){
		return instructions;
	}
	//step == board[y][x]-1;
	if( (int)boardWidth > (1+x) && board[y][x+1] == step){
		instructions.push_back(Dir::RIGHT);
		//std::cout<<"hi3 \n";
		x += 1;
	}else if(0 <= (x-1)&&board[y][x-1] == step){
		instructions.push_back(Dir::LEFT);
		//std::cout<<"hi4 \n";
		x -= 1;
	}else if((int)boardLength > (1+y)&&board[y+1][x] == step){
		instructions.push_back(Dir::DOWN);
		//std::cout<<"hi5 \n";
		y += 1;
	}else if(0 <= (y-1)&&board[y-1][x] == step){
		instructions.push_back(Dir::UP);
		y -= 1;
	}else{
		//std::cout<<"error \n";
		//return"";
	}
	return tellPath(instructions,board,x,y,end);
}
vector<vector<int> > findPath(vector<vector<int> > board){
	unsigned boardLength = board.size();
	unsigned boardWidth = board.at(0).size();
	//std::cout<<"hi1 \n";
	
	for(int y = 0; y < (int)boardLength; y++){
		for(int x = 0;x < (int)boardWidth;x++){
			//std::cout<<"hi2 \n";
			 int step = board[y][x]+1;
			 if(step != 0){
				
				if( (int)boardWidth > (1+x) && board[y][x+1] > step){
					board[y][1+x] = step;
				
				}
				//std::cout<<"hi3 \n";
				if(0 <= (x-1)&&board[y][x-1] > step){
					board[y][x-1] = step;
					y-=2;
					break;
				}
				//std::cout<<"hi4 \n";
				if((int)boardLength > (1+y)&&board[y+1][x] > step){
					board[1+y][x] = step;
				
				}
				//std::cout<<"hi5 \n";
				if(0 <= (y-1)&&board[y-1][x] > step){
					board[y-1][x] = step;
					y-=2;
					break;
				}
				
			 }
			//std::cout<<"hi6 \n";
		}
	}
	//std::cout<<"hi7 \n";
	return board;
	auto boardLength = board.size();
	auto boardWidth = board.at(0).size();
	vector<vector<int> > endingPoints;
	vector<pair<int,int>> points;
	std::cout<<"hi1 \n";
	assert(board.size()==boardLength);
	for(unsigned y = 0; y < boardLength; y++){
		for(unsigned x = 0;x < boardWidth;x++){
			if(board.at(y).at(x) == step){
				pair<int,int> p;
				p.first = x;
				p.first = y;
				points.push_back(p);				
			}
		}
	}
	std::cout<<"hi2 \n";	
	for(unsigned x = 0;x < points.size();x++){
		std::cout<<"hi3 \n";
		if((int)boardWidth > ++points.at(x).first){
			auto xpoint = ++points.at(x).first;
			auto ypoint = points.at(x).second;
			if(board.at(xpoint).at(ypoint) > step){
				board.at(xpoint).at(ypoint) = step++;
			}
		}
		std::cout<<"hi4 \n";
		if(0 < --points.at(x).first){
			auto xpoint = --points.at(x).first;
			auto ypoint = points.at(x).second;
			if((int)board.at(xpoint).at(ypoint) > step){
				board.at(xpoint).at(ypoint) = step++;
			}
		}
		std::cout<<"hi5 \n";
		if((int)boardLength > ++points.at(x).second){
			auto xpoint = points.at(x).first;
			auto ypoint = ++points.at(x).second;
			if(board.at(xpoint).at(ypoint) > step){
				board.at(xpoint).at(ypoint) = step++;
			}
		}
		std::cout<<"hi6 \n";
		if(0 < --points.at(x).second){
			auto xpoint = points.at(x).first;
			auto ypoint = --points.at(x).second;
			if(board.at(xpoint).at(ypoint) > step){
				board.at(xpoint).at(ypoint) = step++;
			}
		}*/
		/*if((int)boardWidth > ++endingPoints.at(0).at(x)){
			if(board[endingPoints[1][x]][++endingPoints[0][x]] > step){
				board[endingPoints[1][x]][++endingPoints[0][x]] = step++;
			}
		}
		std::cout<<"hi3 \n";
		if(0 > --endingPoints.at(0).at(x)){
			if(board[endingPoints[1][x]][--endingPoints[0][x]] > step){
				board[endingPoints[1][x]][--endingPoints[0][x]] = step++;
			}
			
		}
		std::cout<<"hi4 \n";
		if((int)boardLength > ++endingPoints.at(1).at(x)){
			auto y = ++endingPoints.at(1).at(x);
			auto z = endingPoints.at(0).at(x);
			std::cout<<z<<"\n"<<y<<"\n";
			if(board.at(endingPoints.at(1).at(x)).at(endingPoints.at(0).at(x)) > step){
				//board[++endingPoints[1][x]][endingPoints[0][x]] = step++;
			}
		}
		std::cout<<"hi5 \n";
		if(0 > --endingPoints[1][x]){
			if(board[--endingPoints[1][x]][endingPoints[0][x]] > step){
				board[--endingPoints[1][x]][endingPoints[0][x]] = step++;
			}
		}*/
		
	//}
	//std::cout<<board;
	//return board;*/
//}
/*
int main(){

	srand(time(NULL));
	vector<vector<int> > board;
	
	board.push_back(vector<int>{1,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,-1,100,100,100,-1,100,100,100,-1,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,-1,100,100,100,-1,100,100,100,-1,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,-1,100,100,100,-1,100,100,100,-1,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,-1,100,100,100,-1,100,100,100,-1,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,-1,100,100,100,-1,100,100,100,-1,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	board.push_back(vector<int>{100,100,100,-1,100,100,100,-1,100,100,100});
	std::cout<<findPath(board)<<"\n";
	board = findPath(board);
	std::cout<<tellPath({},board,10,23-1,1);
	
	//int startX = rand() % 11;
	//int startY = rand() % 11;
	//srand(time(NULL));
	//int wallsX = 5;
	//int wallsY = 0;
	//int finishX = rand() % 11;
	//int finishY = rand() % 11;
	int walls[3][5] = {{-1,0,-3,0,0},
					   {0,0,-3,0,0},
					   {0,0,0,0,-2}};
	int startX = 0;
	int startY = 0;
	int finishX = 10;
	int finishY = 0;
	std::string instructions = "";
	std::cout<<string("startY: ")<< startX << string("\n");
	std::cout<<string("startX: ")<< startY << string("\n");
	std::cout<<string("finishX: ")<< finishX << string("\n");
	std::cout<<string("finishY: ")<< finishY << string("\n");
	
	int sX = startX;
	int sY = startY;
	int fX = finishX;
	int fY = finishY;
	int SizeArray = sizeof(walls)/sizeof(*walls);
	int SizeSizeArray = sizeof(*walls)/sizeof(**walls);
	instructions += addedInstructions;*/
	
	//std::cout<<instructions << string("\n");
/*
	}
*/
typedef pair<int,int> Location;
/*bool compare(Location A, Location B){
return (A.first == B.first&&A.second == B.second);
}*/
//template<typename T>
/*bool contains(vector<T> A,T B){
	for(int y = 0;y < T.size()){
		if(T[y] == Cont){
		return true;
		}
	}
}*/
string FindPath(
	map<Location,vector<Location>> Map,
	vector<Location> Used,Location Start,
	Location Finish,
	string instructions
	
){
	if(Start == Finish){
		return instructions;
	}
	vector<pair<int,int>> Options = Map[Start];
	for(unsigned int x = 0;x < Options.size();x++){
		bool used = false;
		//checks if the Options[x] is used
		if(0==Options.size()){
			return instructions;
		}
		for(unsigned int y = 0;y < Used.size();x++){
			if(Options[x] == Used[y]){
			break;
			used = true;
			}
		}
		if(!used){
			stringstream ss;
			ss<<instructions + " go to "<< Options[x].first<<","<<Options[x].second;
			instructions = ss.str();
			Used.push_back(Options[x]);
			FindPath(Map,Used,Options[x],Finish,instructions);
			break;
		}
	}	
	return instructions;

}

int main(){
	
	map<pair<int,int>,vector<pair<int,int>>> temp;
	temp[make_pair(0,0)] = {make_pair(1,0),make_pair(0,1)};
	temp[make_pair(0,1)] = {make_pair(0,0),make_pair(1,1)};
	temp[make_pair(1,0)] = {make_pair(0,0)};
	temp[make_pair(1,1)] = {make_pair(0,1)};
	cout<<temp;
	cout<<FindPath(temp,{},make_pair(0,0),make_pair(1,1),"");
	
}
