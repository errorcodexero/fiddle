#include<iostream>
#include<assert.h>

using namespace std;

void renderengine(int gridx, int gridy, int coordx, int coordy, int choice){
	string array [gridx] [gridy];
	string display;
	
	if(choice == 0){
		display = " ";
	}
	if(choice == 1){
		display = "1";
	}
	if(choice == 2){
		display = "2";
	}
	if(choice == 3){
		display = "3";
	}
	if(choice == 4){
		display = "4";
	}
	if(choice == 5){
		display = "5";
	}
	if(choice == 6){
		display = "6";
	}
	if(choice == 7){
		display = "7";
	}
	if(choice == 8){
		display = "8";
	}
	if(choice == 9){
		display = "-";
	}
	if(choice == 10){
		display = "!";
	}
	if(choice == 11){
		display = "?";
	}
	if(choice == 12){
		display = "X";
	}
	if(choice >= 13){
		cout<<"\n\nError: choice = "<<choice<<"\n\n";
		assert(0);
	}
	
	array [coordx] [coordy] = display;
	int county = 0;
	cout<<"\n\n";	
	while(county < gridy){
		int countx = 0;
		while(countx < gridx){
			cout<<array [countx] [county];
			countx++;
		}
		county++;
	}
	cout<<"\n\n";
}

int main(){
	renderengine(5, 5, 2, 2, 3);
}