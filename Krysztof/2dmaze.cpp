#include <iostream>
#include <time.h>
#include <cstdlib>
#include <vector>
using namespace std;

double p[] = {1, 2, 3, 4, 5};

vector<int> a(p, p+5);

int main () {
	cout<<a[0];
	return 0;
}
