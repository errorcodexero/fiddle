#include<iostream>
#include <stdlib.h>
using namespace std;

int addtwo(int x, int y){
	int sum;
	sum=x+y;
	return sum;

}
int main (){
	cout<< "Where are you now (0-5)?\n";
	string s;
	
	getline(cin,s);
<<<<<<< HEAD
	cout<<s<<"\n";
	//cout<<"Hello world!\n";
	
	cout<<"x+y="<< addtwo(3,5)<<"\n";
	if(s=="1"){
		cout<<"right,right,right!\n";
=======
	cout<< "Where do you want to be?\n";
	string target;
	getline(cin,target);
	cout<<"start:"<<s<<"\n";
	cout<<"target:"<<target<<"\n";
	
	
	if(s=="0"&& target =="0"){
		cout<<"stay\n";
>>>>>>> cf1293fa9d7618cb22d97fdba66bfb93ab65a7d0
	}
	if(s=="5") {
		cout<<"Go one left\n";
	}	
	if(s=="2"){
		cout<<" Go two right\n";
	}
	if(s=="3"){
		cout<<"Go one right\n";
	}
	if(s=="4"){
		cout<<"stay\n";
	}

}
//if(left,left,left)

