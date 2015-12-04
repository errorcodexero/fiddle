#include <iostream> 
#include <string>
using namespace std;
int main(){
	cout<<"Type something."<<endl;
	int i=0;
	string input;
	getline(cin,input);
	cout<<"How many times would you like to repeat?"<<endl;
	int x=0;
	string repeatNum;
	getline(cin,repeatNum);
	while(x<atoi(repeatNum.c_str())){
		cout<<input<<endl;
		i++;
	}
}
