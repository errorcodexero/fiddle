#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int isNumber(string value) {
	int result = 0;
	vector<string> digits = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	for (unsigned int i=0; i<value.size(); i++) {
		bool passed = 0;
		for (unsigned int j=0; j<digits.size(); j++) {
			if (value.substr(i, 1)==digits[j]) {
				if (result==0) result = 1;
				passed = 1;
				break;
			} else if (result!=2) {
				passed = 0;
			}
		}
		if (passed==0) {
			if (value.substr(i, 1)=="." && result!=2) {
				result = 2;
			} else {
				result = 0;
				break;
			}
		}
	}
	return result;
}

void printRow(string out_file, vector<vector<string>> data, int row) {
	ofstream output_file;
	output_file.open(out_file);
	for (unsigned int i=0; i<data[row].size(); i++) {
		output_file<<endl<<data[row][i];	
	}
	output_file.close();
}

void printColumn(string out_file, vector<vector<string>> data, int column, string title) {
	ofstream output_file;
	output_file.open(out_file);
	output_file<<title<<endl<<"-----------------------";
	string test_value = data[0][column];
	int result = isNumber(test_value);
	vector<int> ints;
	vector<float> floats;
	for (unsigned int i=0; i<(data.size()-1); i++) {
		string value = data[i][column];
		if (result==1) ints.push_back(atoi(value.c_str()));
		if (result==2) floats.push_back(stof(value.c_str()));
		output_file<<endl<<value;
	}
	if (result!=0) {
		float average;
		output_file<<endl<<"-----------------------";
		if (result==1) {
			for (unsigned int i = 0; i<ints.size(); i++) {
				average+=ints[i];
			}
			average/=ints.size();
		} else {
			for (unsigned int i = 0; i<floats.size(); i++) {
				average+=floats[i];
			}
			average/=floats.size();
		}
		output_file<<endl<<"Average: "<<average;
	}
	output_file.close();
}

vector<string> parse_line(string line) {
	vector<size_t> commas;
	commas.push_back(0);
	unsigned int place = 0;
	while (place!=line.size()) {
		size_t found = line.find(",", place);
		if (found==string::npos) break;
		commas.push_back(found+1);
		place = found + 1;
	}
	vector<string> values;
	for (unsigned int i = 0; i<commas.size(); i++) {
		values.push_back(line.substr(commas[i], (commas[i+1]-(commas[i]+1))));
	}
	return values;
}

int main() {
	ifstream data_file;
	data_file.open("NST_EST2014_ALLDATA.csv");
	string line;
	vector<vector<string>> region_data;
	getline(data_file, line);
	vector<string> column_titles = parse_line(line);	
	while (!data_file.eof()) {
		getline(data_file, line);
		region_data.push_back(parse_line(line));
	}
	data_file.close();
	printColumn("test.txt", region_data, 3, column_titles[3]);
	return 1;
} 
