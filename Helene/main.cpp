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
			cout<<"The rabbit has rabies and bites you. Three weeks later, you're foaming at the mouth during your yearly family gathering. You then bite your cousin. This causes an outbreak of rabies that eventually destroys mankind. Bad end."<<endl; 
		}
		if(in == "no") {
			cout<<"Good. You realize the rabbit has rabies and run away to live another day. Good end."<<endl;
		}
	}
	if(in == "left") {
		cout<<"You decapitate a deer. This isn't going to have any negative consequenses on you, but you should check your morals. You walk away. Do you turn left or right?"<<endl;
		getline(cin, in);
		if(in == "left") {
			cout<< "You come across a ginger bread house which reminds you of the witches house in Hansel and Gretel. Do you peep through the window?"<<endl;
			getline(cin, in);
		if(in == "right") {
			cout<< "You meet a traveler. Together, you too do not safe for work recreational activities which result in the munchies. Ten hours later after dozing off, you wake up without your wallet or keys. (Clearly, a) bad end."<<endl;
		}
	}
	return 0;
}
