#include <iostream>

using namespace std;



int main () {
	string direction;
	bool correct_input=false;
	while (!correct_input) { 
		cout<<"Left or Right?"<<endl;
		cin>>direction;
		if (direction=="Left") {
			cout<<"Cross the road." <<endl;
			correct_input=true;
		} else if (direction=="Right") {
			cout<<"Go to the mountain." <<endl;
			correct_input=true;
		} else {
			cout<<"Please choose one." <<endl;
		}
	}
		 
	return 0;
}
