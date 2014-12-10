#include<iostream>
#include<string>
using namespace std;

int main(/*int answer, char** argv*/){
	string answer;
	cout<<"What is the color of money?\n";
	cin>>answer;
	cout<<"\n";
	if (answer == "Green"){
		cout<<"Correct, Money is green\n";
	}
	else{ cout<<"No that is not the color of money\n";
	}
	
	/*int result1 = 5 + 7;
	cout<<result1<<"\n";
	if (result1 == 12){
		string result2 = "5 + 7 = 12 Yay, it is correct!";
		cout<<result2<<"\n";
	} 
	else{
		string result3 = "Not Correct, 5 + 7 = 12 :(" ;
		cout<<result3<<"\n";
	}*/
}
