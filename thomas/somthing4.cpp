#include <iostream>
#include <vector>
using namespace std;
int main(){
	vector<pair<int,int>> v{
		{10,11}, //0
		{11,10}, //1
		{11,12}, //2
		{12,11}, //2
		{11,15}, //3
		{15,11}, //4
		{13,12}, //5
		{12,13}, //6
		{16,12}, //7
		{12,16}, //8
		{16,15}, //9
		{15,16}, //10
		{17,16}, //11
		{16,17}, //12
		{14,15}, //13
		{15,14}, //14
	};
	cout<<" type command\n";
	string s;
	getline(cin,s);
	cout<<s<<"\n";
	if(s=="1"){
		cout<<" All windows/shades are open.\n";
	}
	if(s=="2"){
		cout<<" left window is open, shade is open, right window is closed.\n";
	}
	if(s=="3"){
		cout<<" left window is open, shade is closed, right window is open.\n";
	}
	if(s=="4"){
		cout<<" left window is closed , shade is open,right window is open.\n";
	}
	if(s=="5"){
		cout<<" left window is open, shade are closed, right window is closed.\n";
	}
	if(s=="1999"){
		cout<<" left window is closed, the shade are closed, right window.\n";
	}
	if(s=="18"){
		cout<<" left window is closed, the shades are closed, right window is closed.\n";
	}
	if(s=="132"){
		cout<<" left window is closed, the shades are open, right window is closed.\n";
	}
	for(int i=0; i<5;i++){
		
fcout<<"hi\n";
	}
	cout<<' ';
	cout<<v[0].first;
	cout<<' ';
	cout<<v[0].second;
	cout<<' ';
	cout<<v[1].first;
	cout<<' ';
	cout<<v[1].second;
	cout<<' ';
	cout<<v[2].first;
	cout<<' ';
	cout<<v[2].second;
	cout<<' ';
	cout<<v[3].first;
	cout<<' ';
	cout<<v[3].second;
	cout<<' ';
	cout<<v[4].first;
	cout<<' ';
	cout<<v[4].second;
	cout<<' ';
	cout<<v[5].first;
	cout<<' ';
	cout<<v[5].second;
	cout<<' ';
	cout<<v[6].first;
	cout<<v[6].second;
	cout<<v[7].first;
	cout<<v[7].second;
	cout<<v[8].first;
	cout<<v[8].second;
	
}
