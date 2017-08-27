#include <iostream>
#include <ctime>

using namespace std;

int main(){
	cout<<"Enter query."<<endl;
	string in;
	getline(cin, in);
	if(in == "What time is it?" || in == "Time?" || in == "Que tiempo hace?" || in == "what time is it" || in == "what time is it?" || in == "What time is it" || in == "what time" || in == "What time" || in == "what time?" || in == "time" || in == "time?") {
		time_t t = time(0);
		cout<<ctime(&t)<<endl;
	}
	return 0;
}
