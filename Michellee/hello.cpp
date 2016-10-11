#include<iostream>
using namespace std;
int main (){
	string s;
	s="b";
	getline(cin,s);
	cout<<s<<"\n";
	//cout<<"Hello world!\n";
	if(s=="1"){
		cout<<"right,right,right!\n";
	}
	if(s=="5") {
		cout<<"go left\n";
	}	
	if(s=="2"){
		cout<<"two right\n";
	}
	if(s=="3"){
		cout<<"one right\n";
	}
	if(s=="4"){
		cout<<"stay\n";
	}
}
//if(left,left,left)

