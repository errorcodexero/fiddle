#include <iostream>

using namespace std;

int main(){
	cout<<"Welcome to the Adventure Game" <<endl;
	cout<<"You are in a room with a table and small light."<<endl;
	string response;
	cout<<"What direction do you want to go in?"<<endl;
	cin>>response;
	if(response=="right"){
		cout<<"You discover a trapdoor in the floor."<<endl;
		cout<<"Do you want to go down?"<<endl;
		cin>>response;
		if(response=="no"){
				cout<<"There is nothing else to do in the room. You lose. :("<<endl;
			}
			if(response=="yes"){
			cout<<"Through the trapdoor there is another room with a locked door. You have no key. You lose. :("<<endl;
			}
	}
	if(response=="left"){
		cout<<"You fall and discover something on the floor."<<endl; 
		cout<<"Do you want to pick it up?"<<endl;
		cin>>response;
		if(response=="yes"){
			cout<<"It is a key, you stumble around the room some more and find a trap door in the floor."<<endl;
			cout<<"Do you want to go down?"<<endl;
			cin>>response;
			if(response=="yes"){
				cout<<"Through the trapdoor there is a room with a locked door."<<endl;
				cout<<"Do you want to try the key?"<<endl;
				cin>>response;
				if(response=="yes"){
					cout<<"It works! You are free! You win :)"<<endl;
				if(response=="no"){
				cout<<"There is nothing else in the room. You lose. :("<<endl;
				}
			}	
	}
			if(response=="no"){
				cout<<"There is nothing else in the room. You lose. :("<<endl;
			}
		}
		if(response=="no"){
			cout<<"You stumble around the room some more and find a trapdoor in the floor!"<<endl;
			cout<<"Do you want to go down?"<<endl;
			cin>>response;
			if(response=="no"){
				cout<<"There is nothing else to do in the room. You lose. :("<<endl;
			}
			if(response=="yes"){
			cout<<"Through the trapdoor there is another room with a locked door. You have no key. You lose. :("<<endl;
			}
		}
		
	}
	return 0; 

	
}
