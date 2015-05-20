#include <fstream>

using namespace std;

int main() {
	ifstream data_file;
	data_file.open("NST_EST2014_ALLDATA.csv");
	string line;
	vector<vector<string>> region_data;
	getline(data_file, line);
	while (!data_file.eof()) {
		getline(data_file, line);
		vector<size_t> commas;
		int place = 0;
		while (place!=line.size()) {
			size_t found = line.find(",", place);
			if (found==string::npos) break;
			commas.push_back(found);
			place = found + 1;
		}
		vector<string> values;
		for (int i = 0; i<commas.size(); i++) {
			values.push_back(line.substr(commas[i], (commas[i+1]-commas[i])));
		}
		region_data.push_back(values);
	}
	data_file.close();
	ofstream test_file;
	test_file.open("test.txt");
	for(int i=0, i<region_data[0]; i++) {
		test_file<<region_data[0][i]<<endl;	
	}
	test_file.close();
	return 1;
} 
