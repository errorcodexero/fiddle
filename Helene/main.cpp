#include <iostream>

using namespace std;

int main(){
	cout<<"Yo there"<<endl;
	cout<<"Left or right?"<<endl;
	string in;
	getline(cin, in);
	if(in == "right") {
		cout<<"You meet a lovely rabbit"<<endl;
		cout<<"Do you want to pick up a rabbit?"<<endl;
		getline(cin, in); 
		if(in == "yes") {
			cout<<"The rabbit has rabies and bites you. Three weeks later, you're foaming at the mouth during your yearly family gathering. You then bite your cousin. This causes an outbreak of rabies that eventually destroys mankind. The end."<<endl; 
		}
		if(in == "no") {
			cout<<"Good. You realize the rabbit has rabies and run away to live another day."<<endl;
		}
	}
	if(in == "left") {
		cout<<"You decapitate a deer"<<endl;
	}
	return 0;
}
