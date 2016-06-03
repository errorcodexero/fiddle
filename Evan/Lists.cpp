#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
vector<string> split(string a){
	vector<string> r;
	stringstream ss;
	for(auto c:a){
		if(c==','){
			r.push_back(ss.str());
			ss.str("");
		}else{
			ss<<c;
		}
	}
	r.push_back(ss.str());
	return r;
	vector<string> jeremy;
	return jeremy;
}
ostream& operator<<(ostream& p, vector<string> a){
	for(auto elem:a){
		p<<elem<<"\n";
	}
}	
int main(){
	 ifstream f("list");
	while(f.good()){
		string s;
		getline(f,s);
		//cout<<s<<"\n";
		cout<<split(s);
		//cout<<"\n";
		
	}
}
