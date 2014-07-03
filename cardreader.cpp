#include<fstream>
#include<sstream>
#include<cassert>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<vector>
#include<termios.h>
#include<stdio.h>
using namespace std;
ostream& operator<<(ostream& o, vector<string>v){
	int tom=0;
	int ted=1;
	for(string s:v){
		o<<ted<<".  :"<<s;
		tom++;
		ted++;
		
		if(tom<v.size())cout<<"\n";
	}
	cout<<"\n";
	return o;
}
ostream& operator<<(ostream& o, vector<vector<string>>vv){
	cout<<"[";
		int tom=0;
	for(vector<string> k:vv){
		o<<k;
		tom++;
		if(tom<vv.size())cout<<",";
	}
	cout<<"]\n";
	return o;
}
int main(){
	ifstream f("writeto.txt");
	string t;
	int lines=0;
	vector<string>g;
	while(f.good()){
		getline(f,t);
		g.push_back(t);
		lines++;
		cout<<t<<"\n";
	}
	int n=0;
	cout<<lines;
	vector<vector<string>>all;
	vector<string>ll;
	vector<string>numb;
	vector<string>name;
	vector<string>date;
	vector<string>party;
	int ue=0;
	for(string s:g){
		//cout<<s<<endl;
		n++;
		stringstream ss;
		int wo=1;
		int q=0;
		int l=0;
		while(q<s.size()){
			if(s[q]=='~'||q>s.size()){
				//cout<<n<<wo<<ss.str()<<"\n";
				ll.push_back(ss.str());
				if(ue==1){
					numb.push_back(ss.str());
				}
				if(ue==2){
					name.push_back(ss.str());
				}
				if(ue==3){
					date.push_back(ss.str());
				}
				if(ue==4){
					party.push_back(ss.str());
					ue=0;
				}
				ss.str("");
				ue++;
				wo++;	
				
			}
			else{
				ss<<s[q];
				//cout<<ss;
			}
			q++;
			//cout<<ss.str();
		}
		
		/*cout<<n<<wo<<ss.str()<<"\n";
		ll.push_back(ss.str());
		all.push_back(ll);
		cout<<ll<<endl;*/
		
	}
	//cout<<ll;
	cout<<"Numbers"<<endl<<endl<<endl<<numb;
	cout<<"Names"<<endl<<endl<<endl<<name;
	cout<<"Dates"<<endl<<endl<<endl<<date;
	cout<<"Party"<<endl<<endl<<endl<<party;
	cout<<"hi"<<name[33];
}