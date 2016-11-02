#include <iostream>
#include <string>

using namespace std;

int main(){
	//Robot stats
	const int robotspeed=10; //feet per second
	
	//Field Stats (in feet)
	const int fieldl=52; 
	const int fieldw=27;
	const int cyclel=105;

	//Time (seconds)
	const int autotime=10;
	const int teletime=140;
	
	//Game elements
	const int bunnies=6;

	//Scoring methods(in points):
	int autobunny=15;
	int endbunny=15;
	int autocross=4;
	int cross=2;
	int dartshot=5;
	int crossespercycle=4;


	int autopoints;
	int telepoints;
	//string input;
	//getline(cin,input);
	//cout<<input<<endl;
	
	int i=0;
	
	if(i==0){
		int cyclespeed=cyclel/robotspeed;
		autopoints=crossespercycle*autocross*(autotime/cyclespeed);
		cout<<"Just crosses: "<<endl<<"Auto points: "<<autopoints<<endl<<"Tele points: "<<telepoints<<endl<<"Total match points: "<<telepoints+autopoints<<endl<<endl;
		i++;
	}
	if(i==1){
		cout<<"test"<<endl;
	}
	
	return 0;
	
}
