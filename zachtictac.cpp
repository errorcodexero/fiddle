#include<stdlib.h>
#include <iostream>
using namespace std;

int display(string a, string b,	string c, string d, string e, string f, string g, string h, string i){

	cout<<"\n";
	cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
	cout<<"x        x        x        x\n";
	cout<<"x   "<<a<<"    x   "<<b<<"    x   "<<c<<"    x\n";
	cout<<"x        x        x        x\n";
	cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
	cout<<"x        x        x        x\n";
	cout<<"x   "<<d<<"    x   "<<e<<"    x   "<<f<<"    x\n";
	cout<<"x        x        x        x\n";
	cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
	cout<<"x        x        x        x\n";
	cout<<"x   "<<g<<"    x   "<<h<<"    x   "<<i<<"    x\n";
	cout<<"x        x        x        x\n";
	cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

}


void calculations(int x, string y){
	if( x = 1){
		if( y = "O"){
			a = "O";
		}else{
			a ="X";
		}
	}
	if( x = 2){
		if( y = "O"){
			b = "O";
		}else{
			b ="X";
		}
	}
	if( x = 3){
		if( y = "O"){
			c = "O";
		}else{
			c ="X";
		}
	}
	if( x = 4){
		if( y = "O"){
			d = "O";
		}else{
			d ="X";
		}
	}
	if( x = 5){
		if( y = "O"){
			e = "O";
		}else{
			e ="X";
		}
	}
	if( x = 6){
		if( y = "O"){
			f = "O";
		}else{
			f ="X";
		}
	}
	if( x = 7){
		if( y = "O"){
			g = "O";
		}else{
			g ="X";
		}
	}
	if( x = 8){
		if( y = "O"){
			h = "O";
		}else{
			h ="X";
		}
	}
	if( x = 9){
		if( y = "O"){
			i = "O";
		}else{
			i ="X";
		}
	}
	
	display(a, b, c, d, e, f, g, h, i);
}

/*void save(string a, string b,	string c, string d, string e, string f, string g, string h, string i){	
	if(a == "O" || "X");
		
}*/

int main (){
	int move_count = 0;
	while( move_count != 9){	
		cout<<"choose a number between '1'-'9'\n";
		int x;
		cin>>x;
		
		cout<<"choose an 'X' or 'O'\n";
		string y;
		cin>>y;
		
		
		calculations(x, y);		
		move_count++;
	}		
}
