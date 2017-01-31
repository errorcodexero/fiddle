#include <iostream>

using namespace std;

double celsius_to_fahrenheit (double celsius) {
	return celsius*1.8+32;
}

int main () {
	double celsius;
	cout<<"Enter celsius value";
	cin>>celsius;
	cout<<celsius_to_fahrenheit(celsius)<<"\n";
	
	return 0;
}
