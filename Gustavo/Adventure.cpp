#include <iostream>
using namespace std;

int main(){
	string input;
	cout<<"Do you want to go left or right?";
	cin>>input;
	if(input=="left"){
		cout<<"You go left\n";
	}else if(input=="right"){
		cout<<"You fall into a pit\n";
		
	}else{
		cout<<"Invalid response\n";
		
	}
	
}
