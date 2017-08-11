#include <iostream>

#include <vector>

using namespace std;


bool in_vector(vector<string> vect, string str){
	for(int i=0; i<3; i++){
		if(str==vect[i]){
			return true;
		}
	}
	return false;
}


int main(){

	cout<<"Welcome to the 2nd Adventure Game" <<endl;
	vector<string> room_items={"Object 1","Object 2","Object 3"};
	vector<string> backpack;
	cout<<"What do you want to pick up?" <<endl;
	string response;
	getline(cin, response);
	cout<<in_vector(room_items, response)<<endl;
	
	
	
	
	return 0;
}
