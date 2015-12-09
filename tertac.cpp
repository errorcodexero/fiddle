#include <iostream>
#include <vector>
#include <string>
using namespace std;
enum class Board{UL,UC,UR,CL,CC,CR,LL,LC,LR};

string print(vector<Board> x, vector<Board> o){
	string ul=" ",uc=" ",ur=" ",cl=" ",cc=" ",cr=" ",ll=" ",lc=" ",lr=" ";	
	vector<Board> v={Board::UL,Board::UC,Board::UR,Board::CL,Board::CC,Board::CR,Board::LL,Board::LC,Board::LR};
	for(int i=0; i<x.size();i++){
		if(x[i]==Board::UL)ul="X";
		if(x[i]==Board::UC)uc="X";
		if(x[i]==Board::UR)ur="X";
		if(x[i]==Board::CL)cl="X";
		if(x[i]==Board::CC)cc="X";
		if(x[i]==Board::CR)cr="X";
		if(x[i]==Board::LL)ll="X";
		if(x[i]==Board::LC)lc="X";
		if(x[i]==Board::LR)lr="X";
	}
	for(int i=0; i<o.size();i++){
		if(o[i]==Board::UL)ul="O";
		if(o[i]==Board::UC)uc="O";
		if(o[i]==Board::UR)ur="O";
		if(o[i]==Board::CL)cl="O";
		if(o[i]==Board::CC)cc="O";
		if(o[i]==Board::CR)cr="O";
		if(o[i]==Board::LL)ll="O";
		if(o[i]==Board::LC)lc="O";
		if(o[i]==Board::LR)lr="O";
	}
	string s;
	s+="      X      X      \n";
	s+="  "+ul+"   X   "+uc+"  X  "+ur+"   \n";
	s+="      X      X      \n";
	s+="XXXXXXXXXXXXXXXXXXXX\n";	
	s+="      X      X      \n";
	s+="  "+cl+"   X  "+cc+"   X   "+cr+"  \n";
	s+="      X      X      \n";
	s+="XXXXXXXXXXXXXXXXXXXX\n";
	s+="      X      X      \n";
	s+="  "+ll+"   X  "+lc+"   X  "+lr+"   \n";
	s+="      X      X      \n";
	return s;
}
Board stob(string s){
	for(int i=0;i<s.size();i++){
		s[i]=toupper(s[i]);
	}
	if(s=="UL")return Board::UL;
	if(s=="UC")return Board::UC;
	if(s=="UR")return Board::UR;
	if(s=="CL")return Board::CL;
	if(s=="CC")return Board::CC;
	if(s=="CR")return Board::CR;
	if(s=="LL")return Board::LL;
	if(s=="LC")return Board::LC;
	if(s=="LR")return Board::LR;
	exit(44);
}
bool f(Board b, vector<Board> v){
	for(int i=0;i<v.size();i++){
		if(v[i]==b)return true;
	}
	return false;
}
bool fin(vector<Board> v){
	if(f(Board::UL,v) && f(Board::UC,v) && f(Board::UR,v)) return true;
	if(f(Board::CL,v) && f(Board::CC,v) && f(Board::CR,v)) return true;
	if(f(Board::LL,v) && f(Board::LC,v) && f(Board::LR,v)) return true;
	if(f(Board::UL,v) && f(Board::CL,v) && f(Board::LL,v)) return true;
	if(f(Board::UC,v) && f(Board::CC,v) && f(Board::LC,v)) return true;
	if(f(Board::UR,v) && f(Board::CR,v) && f(Board::LR,v)) return true;
	if(f(Board::UL,v) && f(Board::CC,v) && f(Board::LR,v)) return true;
	if(f(Board::UR,v) && f(Board::CC,v) && f(Board::LL,v)) return true;
	return false;
}
int main(){
	
	vector<Board> x,o;
	bool status=0;
	while(1){
		cout<<print(x,o)<<endl<<"Player 1 input place on board: ";
		string s;
		cin>>s;
		x.push_back(stob(s));
		if(fin(x) ||fin(o)){
			status=true;
			break;
		}
		vector<Board> v=x;
		for(int i=0;i<o.size(); i++){
			v.push_back(o[i]);
		}
		if(v.size()==9)break;
		cout<<print(x,o)<<endl<<"Player 2 input place on board: ";
		cin>>s;
		o.push_back(stob(s));
		if(fin(x) ||fin(o)){
			status=true;
			break;
		}
		v=x;
		for(int i=0;i<o.size(); i++){
			v.push_back(o[i]);
		}
		if(v.size()==9)break;
	}
	cout<<print(x,o)<<"\n";
	if(status)cout<<"CCCCCONGRATZZZZ!!!!!!11\n";
	else cout<<"YOU SUCK\n";
}
