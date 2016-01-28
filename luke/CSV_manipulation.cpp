#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<vector>
using namespace std;

ostream& operator<<(ostream& o, vector<string> v){
	for(unsigned i = 0; i < v.size(); i++){
		o<<v[i]<<"\n";
	}
	return o;
}

int main(){
	fstream f("a.csv");
	if(f.good() == false){
		cout<<"No file available.";
		exit(1);
	}
	
	/*while(f.good()){
		string s;
		getline(f,s);
		cout<<s<<"\n";
	}*/
	
	//getcolNumList
	
	/*
	//User input
		int userCol;
		cout<<"Which col to list? ";
		cin>>userCol;
		int commaPos;
	
	while(f.good()){
		string s;
		getline(f,s);
		
		
		
		//For to parse through and find 
		for(int i = 0; i < userCol; i++){
			s = s.substr(commaPos = s.find(",")+1);
		}
		s = s.substr(0,s.find(","));
		cout<<s<<"\n";
	}*/
	vector<string> v;
	
	//Store Items in a vector
	while(f.good()){
		string s;
		getline(f,s);

		
		while(s.find(",") != string::npos){
			v.push_back(s.substr(0,s.find(",")));
			s = s.substr(s.find(",")+1);
		}
		v.push_back(s);
	}
	cout<<v;
	
}

