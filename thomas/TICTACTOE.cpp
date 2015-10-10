//Tic tac toe
//spaces 0 1 2 3 4 5 6 7 8 
#include<iostream>
using namespace std;
enum class Space {x,o,BLANK};
ostream & operator<<(ostream & o, Space a){
	o<<"this is a space";
	return o;
}
int main(){
	Space a;
	a=Space::o;
	cout<<a<<"\n";
	
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxx
//x			x			 	 x
