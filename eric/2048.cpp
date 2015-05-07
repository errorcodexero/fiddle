#include<iostream>
#include<cassert>
#include<set>
#include<vector>
#include<type_traits>
#include<array>

using namespace std;

#define nyi { cout<<"nyi "<<__LINE__<<"\n"; exit(44); }

template<typename T>
vector<T>& operator|=(vector<T>& v,T t){
	v.push_back(t);
	return v;
}

template<typename T>
set<T>& operator|=(set<T>& s,T t){
	s.insert(t);
	return s;
}

vector<unsigned> range(unsigned a){
	vector<unsigned> r;
	for(unsigned i=0;i<a;i++) r|=i;
	return r;
}

template<typename T>
T choose(vector<T> v){
	assert(v.size());
	return v[rand()%v.size()];
}

typedef int Piece;

Piece new_piece(){
	if(rand()%2 == 0){
		return 2;
	}
	return 4;
}

typedef pair<int,int> Location;

set<Location> locations(){
	set<Location> r;
	for(auto x:range(4)){
		for(auto y:range(4)){
			r|=pair<int,int>(x,y);
		}
	}
	return r;
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

	Piece operator[](Location l)const{
		return data[l.first][l.second];
	}

	Piece *begin()nyi
	Piece *end()nyi
};

ostream& operator<<(ostream& o,Board const& b){
	for(auto row:range(4)){
		for(auto col:range(4)){
			o<<b[pair<int,int>(row,col)]<<"\t";
		}
		o<<"\n";
	}
	return o;
}

bool operator==(Board const& a,Board const& b){
	for(auto l:locations()){
		if(a[l]!=b[l]) return 0;
	}
	return 1;
}

bool operator!=(Board const& a,Board const& b){
	return !(a==b);
}

enum class Move{LEFT,RIGHT,UP,DOWN};

static const vector<Move> MOVES{Move::LEFT, Move::RIGHT, Move::UP, Move::DOWN};

ostream& operator<<(ostream& o,Move a){
	#define X(NAME) if(a==Move::NAME) return o<<""#NAME;
	X(LEFT) X(RIGHT) X(UP) X(DOWN)
	#undef X
	assert(0);
}

Move random_move(){
	return choose(MOVES);
}

array<Piece,4> collapse(array<Piece,4> a){
	vector<Piece> used;
	for(auto elem:a){
		if(elem) used|=elem;
	}
	vector<Piece> after;
	for(unsigned i=0;i<used.size();i++){
		bool collapse=i+1<used.size() && used[i]==used[i+1];
		if(collapse){
			after|=used[i]*2;
			i++;
		}else{
			after|=used[i];
		}
	}
	array<Piece,4> r;
	for(auto& a:r) a=0;
	for(unsigned i=0;i<after.size();i++) r[i]=after[i];
	return r;
}

Board left(Board b){
	Board r;
	for(unsigned row:range(4)){
		array<Piece,4> this_row;
		for(unsigned col=0;col<4;col++){
			auto l=make_pair(row,col);
			this_row[col]=b[l];
		}
		auto after=collapse(this_row);
		for(unsigned col=0;col<4;col++){
			r[make_pair(row,col)]=after[col];
		}
	}
	return r;
}

Board right(Board b){
	Board r;
	for(unsigned row:range(4)){
		array<Piece,4> this_row;
		for(auto col:range(4)){
			this_row[3-col]=b[make_pair(row,col)];
		}
		auto after=collapse(this_row);
		for(auto col:range(4)){
			r[make_pair(row,col)]=after[3-col];
		}
	}
	return r;
}

Board up(Board b){
	Board r;
	for(auto col:range(4)){
		array<Piece,4> a;
		for(auto row:range(4)){
			a[row]=b[make_pair(row,col)];
		}
		auto after=collapse(a);
		for(auto row:range(4)){
			r[make_pair(row,col)]=after[row];
		}
	}
	return r;
}

Board down(Board b){
	Board r;
	for(auto col:range(4)){
		array<Piece,4> a;
		for(auto row:range(4)){
			a[3-row]=b[make_pair(row,col)];
		}
		auto after=collapse(a);
		for(auto row:range(4)){
			r[make_pair(row,col)]=after[3-row];
		}
	}
	return r;
}
Board move(Board b, Move m){
	switch(m){
		case Move::LEFT: return left(b);
		case Move::RIGHT: return right(b);
		case Move::UP: return up(b);
		case Move::DOWN: return down(b);
		default: assert(0);
	}
}

bool game_over(Board const& b){
	for(unsigned i = 0; i < MOVES.size(); i++){
		if(move(b,MOVES[i]) != b){
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

vector<Location> unoccupied(Board b){
	vector<Location> r;
	for(auto l:locations()){
		if(!b[l]) r|=l;
	}
	return r;
}

Board add_random(Board b){
	b[choose(unoccupied(b))]=new_piece();
	return b;
}

template<typename Func>
unsigned try_game(Func f,bool print){
	Board b=new_game();
	Board old=b;
	unsigned moves=0;
	while(!game_over(b)){
		if(b!=old){
			b=add_random(b);
			moves++;
		}
		if(print)cout<<b<<"\n";
		auto move1=f(b);
		if(print)cout<<move1<<"\n";
		old=b;
		b=move(b,move1);
	}
	if(print)cout<<moves<<"\n";
	return moves;
}

template<typename T>
T sum(vector<T> v){
	T r=0;
	for(auto a:v) r+=a;
	return r;
}

template<typename T>
T mean(vector<T> v){
	return sum(v)/v.size();
}

Move ai_random(Board){
	return choose(MOVES);
}

Move upper_left(Board b){
	if(move(b,Move::LEFT)!=b) return Move::LEFT;
	if(move(b,Move::UP)!=b) return Move::UP;
	if(move(b,Move::RIGHT)!=b) return Move::RIGHT;
	return Move::DOWN;
}

int main(){
	srand(time(NULL));
	vector<unsigned> results;
	for(unsigned i=0;i<1000;i++){
		results|=try_game(ai_random,0);
	}
	cout<<mean(results)<<"\n";
}
