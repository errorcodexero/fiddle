#include <iostream>
using namespace std;
int main(){
	char postition;
	int guess=50;
	while(true){
		cout<<"is it "<<guess<<"?(y,h,l)";
		cin>>postition;
		if(postition=='y')break;
		if(postition=='h')guess = guess+guess/2;
		if(postition=='l')guess = guess-guess/2;
	}
	return 0;
}

