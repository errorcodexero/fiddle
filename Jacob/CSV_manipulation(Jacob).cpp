#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<vector>
using namespace std;

ostream& operator<<(ostream& o, vector<string> v){
	for(auto element : v){
		//for(unsigned t = 0; t < t.size(); t++){
			o<<element<<"\n";
		//}
	}
	return o;
}

ostream& operator<<(ostream& o, vector< vector<string> > v){
	for(auto element : v){
		//for(unsigned t = 0; t < t.size(); t++){
			o<<element<<"\n";
		//}
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
	vector< vector<string> > v;

	//Store Items in a vector
	while(f.good()){
		string s;
		getline(f,s);

		vector<string> temp;
		while(s.find(",") != string::npos){
			temp.push_back(s.substr(0,s.find(",")));
			s = s.substr(s.find(",")+1);
		}
		temp.push_back(s);
		v.push_back(temp);
	}
	cout<<v;
	
}

