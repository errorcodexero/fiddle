#include <stdlib.h>
#include<iostream>
using namespace std;
int main(){
	cout<<"Hello.\n";
	
	char cont='y';
	cout<<"Would you like to receive directions?(Type 'y' for yes and 'n' for no.)\n"; 
	cin>>cont;
	while(cont=='y'){
		
		double currentX;
		cout<<"What is your current x coordinate?\n";
		cin>> currentX;
	
		double currentY;
		cout<<"What is your current y coordinate?\n";
		cin>> currentY;
		
	
		double destinationX;
		cout<<"What is your destination's x coordinate?\n";
		cin>> destinationX;
	
		double destinationY;
		cout<<"What is your destination's y coordinate?\n";
		cin>> destinationY;
	
		double horizDist;
		horizDist=(destinationX-currentX);
		double vertDist;
		vertDist=(destinationY-currentY);
	
		if(horizDist==0 && vertDist==0){
			cout<<"You are already there.\n";
		}
		if(horizDist<0){
			cout<<"Move " <<abs(horizDist)<< " spaces left.\n";
		}
		if(horizDist>0){
			cout<<"Move " <<horizDist<< " spaces right.\n";
		}
		if(horizDist==0){
			cout<<"Don't move horizontally.\n";
		}
		if(vertDist==0){
			cout<<"Don't move vertically.\n";
		}
		if(vertDist>0){
			cout<<"Move " <<vertDist<< " spaces up.\n";
		}
		if(vertDist<0){
			cout<<"Move " <<abs(horizDist)<< " spaces down.\n";
		}
		
		cout<<"Would you like to receive directions again?(Type 'y' for yes and 'n' for no.)\n"; 
			cin>>cont;
		if(cont=='n'){
			break;
		}
		
	}
	
	cout<<"Bye.\n";
}