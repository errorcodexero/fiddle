#include <iostream>
using namespace std;
int main(){
	pair < int, int > start, end;
	start=make_pair(9,9);
	end=make_pair(1,5);
	cout << start.first << " " << start.second << endl;
	cout << end.first << " " << end.second << endl;
	while(start.first<end.first){
		start.first++;
}
	while(start.first>end.first){
		start.first--;
}
	while(start.second<end.second){
		start.second++;
}
	while(start.second>end.second){
		start.second--;
}
	cout << start.first << " " << start.second << endl;
	cout << end.first << " " << end.second << endl;



	return 0;
}

