#include <fstream>
#include <iostream>

#define DMAX 6
#define WIDTH 8
#define HEIGHT 7

struct Domino {
	int x,y,n1,n2;	
};

int factorial(int n) {
	if (n>1) return (n + factorial(n - 1));
	return 1;
}

int main() {
	Domino dominoes[2];//factorial(DMAX + 1)];
	std::cout<<dominoes.length<<std::endl;
	//ostream d(d.txt);
	//for
	
	//d.close();
	return 0;
}
