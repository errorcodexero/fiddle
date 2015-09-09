#include <iostream>
#include<stdlib.h>
using namespace std;
enum class Dir{LEFT,RIGHT,UP,DOWN};
ostream& operator<<(ostream& o, Dir d){
	if(d == Dir::LEFT){
		o << "LEFT" << endl;
	}
	if(d == Dir::RIGHT){
		o << "RIGHT" << endl;
	}
	if(d == Dir::UP){
		o << "UP" << endl;
	}
	if(d == Dir::DOWN){
		o << "DOWN" << endl;
	}
	return o;
}
void check_for_wall (pair < int, int > p){
	if(p.first == 2 && p.second == 0){
		cout << "Sorry, you hit a wall!" << endl;
		exit(0);	
	}
}
int main(){
	pair < int, int > start, end;
	start=make_pair(0,0);
	end=make_pair(5,5);
	cout << start.first << " " << start.second << endl;
	cout << end.first << " " << end.second << endl;
	cout << " " << endl;
	while(start.first != end.first || start.second != end.second){
		Dir nextmove;
		if(start.first<end.first){
			nextmove = Dir::RIGHT;
		}
		if(start.first>end.first){
			nextmove = Dir::LEFT;
		}
		if(start.second<end.second){
			nextmove = Dir::UP;
		}
		if(start.second>end.second){
			nextmove = Dir::DOWN;
		}
		cout << nextmove << endl;
		if(nextmove == Dir::LEFT){
			start.first --;
		}
		if(nextmove == Dir::RIGHT){
			start.first ++;
		}
		if(nextmove == Dir::UP){
			start.second ++;
		}
		if(nextmove == Dir::DOWN){
			start.second --;
		}
	}
	/*while(start.first<end.first){
		start.first++;
		cout << start.first << " " << start.second << "  Go Right" << endl;
		check_for_wall(start);
	}
	while(start.first>end.first){
		start.first--;
		cout << start.first << " " << start.second << "  Go Left" << endl;
		check_for_wall(start);
	}
	while(start.second<end.second){
		start.second++;
		cout << start.first << " " << start.second << "  Go Up" << endl;
		check_for_wall(start);	
	}
	while(start.second>end.second){
		start.second--;
		cout << start.first << " " << start.second << "  Go Down" << endl;
		check_for_wall(start);
	}
	*/


	return 0;
}

