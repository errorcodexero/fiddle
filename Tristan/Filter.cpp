#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

bool iseven(int input){
	return (input%2==0);
}
bool divisablebythree(int input){
	return (input%3==0);

}
vector<int> evennumbers(vector<int> list){
	vector<int> even;
	for(int i:list){
		if(iseven(i) == 1) even.push_back(i);
	}
	return even;
}
vector<int> ofthree(vector<int> list){
	vector<int> three;
	for(int i:list){
		if(divisablebythree(i) ==1) three.push_back(i);
	}
	return three;


}

int main(){
	vector<int> list;
	vector<int> three;
	vector<int> even;
	
	for(int i=0;i<11;i++){
		list.push_back(i);
		cout <<"list: " << list[i] << endl;
	}
	for(int i:list) cout << i << " is " << iseven(i) << endl;
	even = evennumbers(list);
	three = ofthree(list);
	
	for(int i:even) cout << "Even #: " << i << endl;
	for(int i:three) cout << "# of 3: " << i << endl;
}
