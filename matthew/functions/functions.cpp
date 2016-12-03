#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<typename Func, typename T>
vector<T> filter(Func f, vector<T> v) {
	vector<T> outputs;
	for (unsigned i = 0; i < v.size(); i++) if (f(v[i])) outputs.push_back(v[i]);
	return outputs;
}

template<typename Func, typename T>
auto map(Func f, vector<T> v) {
	T x;
	vector<decltype(f(x))> outputs;
	for (unsigned i = 0; i < v.size(); i++) outputs.push_back(f(v[i]));
	return outputs;
}

bool even(int i) {
	return i % 2 == 0;
}

double trim(double d) {
	return min(fabs(d), 1.0) * (d/fabs(d));
}

int main() {
	vector<int> numbers = {0, 2, 4, 3, 6, 1, 23};
	vector<int> evens = filter(even, numbers);
	cout<<"Filter:"<<endl;
	for (unsigned i = 0; i < evens.size(); i++) cout<<evens[i]<<" ";
	cout<<endl;
	
	vector<double> numbers2 = {.01, .43, -.12, -1.0, 3.0, -10.0, .23, -.38126};
	vector<double> trimmed = map(trim, numbers2);
	cout<<"Map:"<<endl;
	for (unsigned i = 0; i < trimmed.size(); i++) cout<<trimmed[i]<<" ";
	cout<<endl;
}
