#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main() {
	for(int i=0; i<3; i++){
		cout<<"Password:"<<endl;
		string input; 
		cin>>input;
		if(input=="Password"){
			cout<<"Correct!"<<endl;
			ifstream hi2;
			hi2.open("hi2.txt");
			string anything;
			while(!hi2.eof()){
				getline(hi2, anything);
				cout<<anything<<endl;
			}
			break;
		} else{ 
			if(i<2){
				cout<<"Incorrect, "<<(2-i)<<" Tries Left "<<endl;
			}else{
				cout<<"Sorry, No More Tries"<<endl;
			}
		}
	}

	return 0;
}
