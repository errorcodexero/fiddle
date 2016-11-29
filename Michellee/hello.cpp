#include<iostream>
#include <stdlib.h>
using namespace std;
int main (){
	cout<< "Where are you now (0-5)?\n";
	string s;	
	getline(cin,s);
	cout<< "Where do you want to be?\n";
//int main_two (){	
	int i=atoi (s.c_str());
	cout<<" i is equal to "<<i<<"\n";
	string target;
	getline(cin,target);
	cout<<"start:"<<s<<"\n";
	cout<<"target:"<<target<<"\n";
	int target_2;
	target_2=atoi(target.c_str());
	//cout<<"target_2 "<<target_2<<"\n";
	int difference =i -target_2;
	cout<<"difference: 2"<<difference<<"\n";
	
	/*if(s=="0"&& target =="0"){
		cout<<"stay\n";
	}
	if (s=="0"&& target =="1"){
		cout<< "Go one right\n";
	}
	if (s=="0"&& target =="2"){
		cout<< "Go two right\n";
	}
	if (s=="0"&& target =="3"){
		cout<< "Go three right\n";
	}
	if (s=="0"&& target =="4"){
		cout<<"Go four right\n";
	}
	if (s=="0"&& target =="5"){
		cout<<"Go five right\n";
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
	}*/

}
//if(left,left,left)

