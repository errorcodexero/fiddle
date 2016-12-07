#include<iostream>
#include <stdlib.h>
using namespace std;
int get_num(){
	string f;
	getline (cin,f);
	int s=atoi (f.c_str());
	return s;
	cout<<"f is equal to "<<f<<"\n";
	//exit(5);//
}
int main (){
	
	cout<< "Where in the \"x\" axis are you now (0-5)?\n";
	int current_x_value=get_num();
	cout<< "Where in the \"x\" axis do you want to be (0-5)?\n";	
	int target_2_wanted_x_value=get_num();
	int difference_x = current_x_value -target_2_wanted_x_value;
	/*cout<<"difference: 0"<<difference<<"\n";
	if (difference==0){
		cout<<"stay\n";
	}
	if (difference==1){
		cout<<"go left\n";
	}
	if (difference==2){
		cout<<"go left two\n";
	}
	if (difference==3){
		cout<<"go left three\n";
	}
	if (difference==4){
		cout<<"go left four\n";
	}
	if (difference==5){
		cout<<"go left five\n";
	}
	if (difference==-1){
		cout<<"go right one\n";
	} 
	if (difference==-2){
		cout<<"go right two\n";
	} 
	if (difference==-3){
		cout<<"go right three\n";
	}
	if (difference==-4){
		cout<<"go right four\n";
	}
	if (difference==-5){
		cout<<"go right five\n";
	}*/
cout<< "Where in the \"y\" axis are you now (0-5)?\n";
	int current_y_value=get_num();
	cout<< "Where in the \"y\" axis do you want to be (0-5)?\n";	
	int target_2_wanted_y_value=get_num();
	int difference_y = current_y_value -target_2_wanted_y_value;
	int at;
	int target;
	while (at!=target){
		if (at>target){
			cout<< "go left\n";
			at --;
			cout<<"Go left"<<difference_x<<"\n";
		}
	}

	/*cout<<"difference: 0"<<difference<<"\n";
	if (difference==0){
		cout<<"stay\n";
	}
	if (difference==1){
		cout<<"go left\n";
	}
	if (difference==2){
		cout<<"go left two\n";
	}
	if (difference==3){
		cout<<"go left three\n";
	}
	if (difference==4){
		cout<<"go left four\n";
	}
	if (difference==5){
		cout<<"go left five\n";
	}
	if (difference==-1){
		cout<<"go right one\n";
	} 
	if (difference==-2){
		cout<<"go right two\n";
	} 
	if (difference==-3){
		cout<<"go right three\n";
	}
	if (difference==-4){
		cout<<"go right four\n";
	}
	if (difference==-5){
		cout<<"go right five\n";
	}*/

}


