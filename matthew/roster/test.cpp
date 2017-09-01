#include <iostream>
#include <string>
#include <random>

using namespace std;

int main(){
	const int nrolls = 10000;
	const int nstars = 1000;

	random_device rd;
	default_random_engine generator;
	generator.seed(rd());
	uniform_int_distribution<int> uniform(80, 90);
	normal_distribution<double> normal(uniform(generator),10.0);
	

	int p[100]={};
	
	for (int i=0; i<nrolls; ++i) {
		double num = round(normal(generator)*100)/100;
		cout<<num<<endl;
		//cout<<num<<endl;
		if ((num>0.0)&&(num<100.0)) ++p[int(num)];
	}

	for (int i=0; i<100; ++i){
		cout<<i<<"-"<<(i + 1)<<": ";
		cout<<string(p[i]*nstars/nrolls,'*')<<endl;
	}

	return 0;
}
