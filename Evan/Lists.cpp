#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector<string> split(string a){
	vector<string> jeremy;
	return jeremy;
}
ostream& operator<<(ostream& p, vector<string> a){
	for(auto elem:a){
		p<<elem;
	}
}	
int main(){
	 ifstream f("list");
	while(f.good()){
		string s;
		getline(f,s);
		cout<<s<<"\n";
		cout<<split("hello");
		
	}
}
