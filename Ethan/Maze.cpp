#include<iostream>
using namespace std;
char letter();
bool start(){
	string e;
	//e="[X][][][][][][][][][]          [][][][][][][][]\n                   [][][][][][][]";
	//cout<<e<<"\n";
	char icecream=letter();
	if(icecream=='>'){
		
	}else if(icecream=='^'){
		
	}else if(icecream=='<'){
		
	}else if(icecream=='V'){
		
	}

	return 1;
}
int main(){
	string d;
	d="do you want to solve a maze Y/N";
	cout<<d<<"\n";
	getline(cin,d);
	if(d=="Y"){
		cout<<"Ok starting Maze... use > to mark right and ^ to mark up and V to mark down\n";
		while (start()){
			//do stuff
		}
	}else{
		cout<<"Ok no problem";
	}
}
char letter(){
	string key;
	getline(cin,key);
	return key[0];
	
	//return 4;
}

