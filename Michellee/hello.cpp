#include<iostream>
#include <stdlib.h>
using namespace std;
int get_num(){
	string f;
	getline (cin,f);
	int s=atoi (f.c_str());
	return s;
}
int main (){
	
	cout<< "Where in the \"x\" axis are you now (0-5)?\n";
	int current_x_value=get_num();
	cout<< "Where in the \"x\" axis do you want to be (0-5)?\n";	
	int target_2_wanted_x_value=get_num();
	int difference_x = current_x_value -target_2_wanted_x_value;
	
	cout<< "Where in the \"y\" axis are you now (0-5)?\n";
	int current_y_value=get_num();
	cout<< "Where in the \"y\" axis do you want to be (0-5)?\n";	
	int target_2_wanted_y_value=get_num();
	int difference_y = current_y_value -target_2_wanted_y_value;
	pair<int,int> at;
	at.first=current_x_value ;
	at.second=current_y_value;
	int target;
	while (at.first!=target_2_wanted_x_value || at.second!=target_2_wanted_y_value){
		if (at.first >target){
			cout<< "Go left\n";
			at.first--;
		}
	}
}


