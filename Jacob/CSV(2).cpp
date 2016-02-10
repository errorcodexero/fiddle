#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include<vector>
using namespace std;

int main(){
	fstream f("logger.csv");
	if(f.good() == false){
		cout<<"No file available.";
		exit(1);
	}
	
	vector< vector<string> > v;
	
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
	
	for(vector<vector<string> >::iterator it = v.begin(); it != v.end(); ++it){
		for(vector<string>::iterator jt = it->begin(); jt != it->end(); ++jt){
			cout << *jt;
			cout << "\n";
		}
		cout << "\n";
	}
}
