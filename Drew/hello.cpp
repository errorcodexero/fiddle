#include<iostream>
#include<stdlib.h>
using namespace std;
int main(){	
	string start_str;
	getline(cin, start_str);
	int start = atoi(start_str.c_str());
	string finish_str;
	getline(cin, finish_str);
	int finish = atoi(finish_str.c_str());
	cout<<"Start: "<<start<<"\n"; 
	cout<<"Finish: "<<finish<<"\n";

	if (start == 1 && finish == 1){
		cout<<"No Movement Needed\n";
	}
	if ((start == 1 && finish == 2) || (start == 2 && finish == 3) || (start == 3 && finish == 4) || (start == 4 && finish == 5)){
		cout<<"Go Right\n";
	}
	if ((start == 1 && finish == 3) || (start == 2 && finish == 4) || (start == 3 && finish == 5)){
		cout<<"Go Right Right\n";
	}
	if ((start == 1 && finish == 4) || (start == 2 && finish == 5)){
		cout<<"Go Right Right Right\n";
	}
	if (start == 1 && finish == 5)
		cout<<"Go Right Right Right Right\n";
	}
	if ((start == 2 && finish == 1) || (start == 3 && finish == 2) || (start == 4 && finish == 3) || (start == 5 && finish == 4)){
		cout<<"Go Left\n";
	}
	if ((start == 3 && finish == 1) || (start == 4 && finish == 2) || (start == 5 && finish == 3)){
		cout<<"Go Left Left\n";
	}
	if (start == 5 && finish == 5){
		cout<<"No Movement Needed\n";
	}
}