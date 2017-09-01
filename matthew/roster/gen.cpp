#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

int main(){
	random_device rd;
	default_random_engine generator;
	generator.seed(rd());
	uniform_int_distribution<int> uniform(80, 90);
	normal_distribution<double> normal(uniform(generator), 10.0);

	vector<string> names;
	ifstream roster_in("roster_names.txt");
	if(!roster_in.good()) {
		cout<<"Failed to open file."<<endl;
		return 0;
	}
	while(!roster_in.eof()) {
		string tmp;
		getline(roster_in, tmp);
		if(tmp.length()>0) names.push_back(tmp);
	}
	roster_in.close();

	ofstream roster_out("roster.txt");
	for(unsigned int i=0; i<names.size(); i++) {
		roster_out<<names[i]<<":";
		for(int j=0; j<6; j++) {
			roster_out<<round(normal(generator)*100)/100;
			if(j!=5) roster_out<<",";
		}
		roster_out<<"\n";
	}
	roster_out.close();

	return 0;
}
