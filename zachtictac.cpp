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

int display(string symbols[]){

	cout<<"\n";
	cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
	cout<<"x        x        x        x\n";
	cout<<"x   "<<symbols[0]<<"    x   "<<symbols[1]<<"    x   "<<symbols[2]<<"    x\n";
	cout<<"x        x        x        x\n";
	cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
	cout<<"x        x        x        x\n";
	cout<<"x   "<<symbols[3]<<"    x   "<<symbols[4]<<"    x   "<<symbols[5]<<"    x\n";
	cout<<"x        x        x        x\n";
	cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
	cout<<"x        x        x        x\n";
	cout<<"x   "<<symbols[6]<<"    x   "<<symbols[7]<<"    x   "<<symbols[8]<<"    x\n";
	cout<<"x        x        x        x\n";
	cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";

}
	
/*bool O_has_won(string symbols[]){
	return ((symbols[0]=="O") && (symbols[1]=="O") && (symbols[2]=="O")) || // top row
	       ((symbols[3]=="O") && (symbols[4]=="O") && (symbols[5]=="O")) || // middle row
	       ((symbols[6]=="O") && (symbols[7]=="O") && (symbols[8]=="O")) || // bottom row
	       //horizontal O
	       ((symbols[0]=="O") && (symbols[3]=="O") && (symbols[6]=="O")) || // left column
               ((symbols[1]=="O") && (symbols[4]=="O") && (symbols[7]=="O")) || // middle column
	       ((symbols[2]=="O") && (symbols[5]=="O") && (symbols[8]=="O")) || // right column
	       //vertical O
	       ((symbols[0]=="O") && (symbols[4]=="O") && (symbols[8]=="O")) || // top left to bottem right 
               ((symbols[6]=="O") && (symbols[4]=="O") && (symbols[2]=="O")) ; // bottem left to top right
}
bool X_has_won(string symbols[]){	       
	       ((symbols[0]=="X") && (symbols[1]=="X") && (symbols[2]=="X")) || // top row
	       ((symbols[3]=="X") && (symbols[4]=="X") && (symbols[5]=="X")) || // middle row
	       ((symbols[6]=="X") && (symbols[7]=="X") && (symbols[8]=="X")) || // bottom row
	       //horizontal X
	       ((symbols[0]=="X") && (symbols[3]=="X") && (symbols[6]=="X")) || // left column
               ((symbols[1]=="X") && (symbols[4]=="X") && (symbols[7]=="X")) || // middle column
	       ((symbols[2]=="X") && (symbols[5]=="X") && (symbols[8]=="X")) || // right column
	       //vertical X
	       ((symbols[0]=="X") && (symbols[4]=="X") && (symbols[8]=="X")) || // top left to bottem right 
               ((symbols[6]=="X") && (symbols[4]=="X") && (symbols[2]=="X")) ; // bottem left to top right
	       
}*/
bool somebody_has_1(string symbols[], string who){	       
	       ((symbols[0]==who) && (symbols[1]==who) && (symbols[2]==who)) || // top row
	       ((symbols[3]==who) && (symbols[4]==who) && (symbols[5]==who)) || // middle row
	       ((symbols[6]==who) && (symbols[7]==who) && (symbols[8]==who)) || // bottom row
	       //horizontal X
	       ((symbols[0]==who) && (symbols[3]==who) && (symbols[6]==who)) || // left column
               ((symbols[1]==who) && (symbols[4]==who) && (symbols[7]==who)) || // middle column
	       ((symbols[2]==who) && (symbols[5]==who) && (symbols[8]==who)) || // right column
	       //vertical X
	       ((symbols[0]==who) && (symbols[4]==who) && (symbols[8]==who)) || // top left to bottem right 
               ((symbols[6]==who) && (symbols[4]==who) && (symbols[2]==who)) ; // bottem left to top right
	       








}
//void calculations(int x, string y, string &a, string &b, string &c, string &d, string &e, string &f, string &g, string &h, string &i){
void calculations(int x, string y, string symbols[]){
	
	symbols[x-1] = y;
	display(symbols);
	if (somebody_has_1(symbols, "O")){
		
		cout<<"O has 1 \n";
		exit(0);
	} else if (somebody_has_1(symbols, "X")){
		cout<<"X has 1 \n";
		exit(0);
	}

/*
	if( x == 1){
		if( y == "O"){
			symbols[0] = "O";
		}else{
			symbols[0] ="X";
		}
	}
	if( x ==  2){
		if( y == "O"){
			symbols[1] = "O";
		}else{
			b ="X";x
		}
	}
	if( x ==  3){
		if( y == "O"){
			c = "O";
		}else{
			c ="X";
		}
	}
	if( x == 4){
		if( y == "O"){
			d = "O";
		}else{
			d ="X";
		}
	}
	if( x == 5){
		if( y == "O"){
			e = "O";
		}else{
			e ="X";
		}
	}
	if( x == 6){
		if( y == "O"){
			f = "O";
		}else{
			f ="X";
		}
	}
	if( x == 7){
		if( y == "O"){
			g = "O";
		}else{
			g ="X";
		}
	}
	if( x == 8){
		if( y == "O"){
			h = "O";
		}else{
			h ="X";
		}
	}
	if( x == 9){
		if( y == "O"){
			i = "O";
		}else{
			i ="X";
		}
	}
	
	display(a, b, c, d, e, f, g, h, i);
*/
}

/*void save(string a, string b,	string c, string d, string e, string f, string g, string h, string i){	
	if(a == "O" || "X");
		
}*/

int main (){
	string a=" ", b=" ", c=" ", d=" ", e=" ", f=" ", g=" ", h=" ", i=" ";
	const int numSymbols = 9;
	string symbol[numSymbols];
	for(int index=0; index < numSymbols; index++) {
		symbol[index] = " ";
	}	
	int move_count = 0;

	int player = 1; // 1 = P1, 2 = P2
	while( move_count != 9){	
		string y;
		
		cout<<"Player: "<<player<<" \n";
		
		if(player == 1){
			y = "O";
			player = 2;
		} else {
			y = "X";
			player = 1;
		}
		
		cout<<"choose a number between '1'-'9'\n";
		int x;
		cin>>x;
		if ((x >= 1) && (x <=9)){



			/*cout<<"choose an 'X' or 'O'\n";
			string y;
			cin>>y;*/
			
			calculations(x, y, symbol);		
			move_count++;
		}		

	}
}

