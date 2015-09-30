//Tic tac toe
//spaces 0 1 2 3 4 5 6 7 8 
#include<iostream>
using namespace std;
enum class Space {X,O,BLANK};
int main(){
	Space a;
	a=Space::x;
	cout<<a<<"\n";
}
ostream & operator<<(ostream & 0b, Space a){
	o<<"this is a space";
	return o;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxx
//x			x			     x
