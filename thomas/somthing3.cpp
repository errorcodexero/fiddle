#include<iostream>
using namespace  std;
int main(){
	cout<<" hi \n";
	string s;
	getline(cin,s);
	cout<<s<<"\n";
	if(s=="1"){
		cout<<"try 2.\n";
	}
	if(s=="2"){
		cout<<"I predict 3.\n";
	}
	if(s=="3"){
		cout<<"skip to 10.\n";
	}
	if(s=="10"){
		cout<<"why not 11?\n";
	}
	if(s=="11"){
		cout<<"how about 12?\n";
	}
	if(s=="12"){
		cout<<"go to 1 again.\n";
	}
	if(s=="14"){
		cout<<" you find a secwet.\n";
	}
}
