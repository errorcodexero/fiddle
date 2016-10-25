#include<iostream>
#include <stdlib.h>
using namespace std;
int main (){
	cout<< "Where are you now (0-5)?\n";
	string s;
	
	getline(cin,s);
	cout<< "Where do you want to be?\n";
	string target;
	getline(cin,target);
	cout<<"start:"<<s<<"\n";
	cout<<"target:"<<target<<"\n";
	
	
	if(s=="0"&& target =="0"){
		cout<<"stay\n";
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

