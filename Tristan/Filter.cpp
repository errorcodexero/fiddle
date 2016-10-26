#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;
template<typename T>
ostream& operator<<(ostream & o,vector<T> v){
	for(auto i:v) cout << i << endl;
	return o;
}
template<typename T>
int wrap(T f,vector<int> i){
	cout<< "Using " << i << endl;
	return f(i);
}
bool iseven(int input){
	return (input%2==0);
}
bool divisablebythree(int input){
	return (input%3==0);

}
bool divisablebyfive(int input){
	return (input%5==0);
}
vector<int> evennumbers(vector<int> numbers){
	vector<int> even;
	for(int i:numbers){
		if(iseven(i)) even.push_back(i);
	}
	return even;
}
vector<int> ofthree(vector<int> numbers){
	vector<int> three;
	for(int i:numbers){
		if(divisablebythree(i)) three.push_back(i);
	}
	return three;
}

vector<int> offive(vector<int> numbers){
	vector<int> five;
	for(int i:numbers){
			if(divisablebyfive(i)) five.push_back(i);
	}
	return five;
}



int main(){
	vector<int> numbers;
	vector<int> three;
	vector<int> even;
	vector<int> five;
	
	for(int i=0;i<11;i++){
		numbers.push_back(i);
		cout <<"numbers: " << numbers[i] << endl;
	}
	for(int i:numbers) cout << i << " is " << iseven(i) << endl;
	even.push_back(wrap(evennumbers,numbers));
	three.push_back(wrap(ofthree,numbers));	
	five.push_back(wrap(offive,numbers));
	
	
	for(int i:even) cout << "Even #: " << i << endl;
	for(int i:three) cout << "# of 3: " << i << endl;
	for(int i:five) cout << "# of 5: " << i <<  endl;
	
	
}
