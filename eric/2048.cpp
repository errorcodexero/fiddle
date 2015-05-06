#include<iostream>
#include<cassert>
#include<set>
#include<vector>
#include<type_traits>

using namespace std;

#define nyi { cout<<"nyi "<<__LINE__<<"\n"; exit(44); }

//vector<T> to_vector(Collection)nyi

/*template<typename Func,typename Collection>
auto filter(Func f,Collection v)->vector<
	std::remove_reference<
		decltype(*(v.begin()))
	>::type
>{
	/*vector<decltype(*v.begin())> r;
	for(auto a:v){
		if(f(a)) r|=a;
	}
	return r;*/
/*	nyi
}*/

typedef int Piece;

Piece new_piece(){
	if(rand()%2 == 0){
		return 2;
	}
	return 4;
}

typedef pair<int,int> Location;

set<Location> locations(){
	nyi
}

Location random_location(){
	return make_pair(rand()%4,rand()%4);
}

struct Board{
	Piece data[4][4];

	Board(){
		for(int i = 0; i < 4; i++){
			for(int k = 0; k < 4; k++){
				data[i][k] = 0;
			}
		}
	}

	Piece& operator[](Location l){
		return data[l.first][l.second];
	}

	Piece *begin()nyi
	Piece *end()nyi
};

ostream& operator<<(ostream& ,Board const& ){
	nyi
}

enum class Move{LEFT,RIGHT,UP,DOWN};

Move random_move()nyi

Board move(Board b, Move m){
	nyi
}



bool game_over(Board const& b){
	vector<Move> moves {Move::LEFT, Move::RIGHT, Move::UP, Move::DOWN};
	for(int i = 0; i < moves.size(); i++){
		if(move(b,moves[i]) != b){
			return false;
		}
	}
	return true;
}

unsigned filled(Board b){
	//auto f=filter([](Piece p){ return p!=0; },b);
	//return f.size();
	int count = 0;
	for(int i = 0; i < 4; i ++){
		for(int k = 0; k < 4; k++){
			if(b.data[i][k] != 0){
				count++;
			}
			
		}	
	}
	return count;
}

Board new_game(){
	Board r;
	while(filled(r)<2){
		r[random_location()]=new_piece();
	}
	return r;
}

Board apply(Board const&,Move)nyi

int main(){
	Board b=new_game();
	while(!game_over(b)){
		cout<<b<<"\n";
		b=apply(b,random_move());
	}
}

