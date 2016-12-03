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
	cout<< "Where are you now (0-5)?\n";
	int i=get_num();
	cout<< "Where do you want to be?\n";	
	int target_2=get_num();
	int difference =i -target_2;
	cout<<"difference: 0"<<difference<<"\n";
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
	}

}


