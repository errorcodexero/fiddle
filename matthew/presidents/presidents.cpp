//Created by Matthew Macovsky
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

class President {
	public:
		string name;
		string years;
		string party;
};

class Config {
	public:
		int presidents;
		int quizzes;
		int guesses;
};

string getSuffix(int number) {
	switch(number) {
		case 1:
			return "st";
		case 2:
			return "nd";
		case 3:
			return "rd";
		default:
			return "th";
	}
	assert(0);
}

Config getConfig(string& placeholder) {
	Config config;
	ifstream config_file;
	config_file.open("config.ini");
	while(!config_file.eof()) {
		getline(config_file, placeholder);
		string property = placeholder.substr(0, placeholder.find("="));
		string value = placeholder.substr((placeholder.find("=") + 1), placeholder.size());
		if (property=="presidents") {
			config.presidents = atoi(value.c_str());
		} else if (property=="quizzes") {
			config.quizzes = atoi(value.c_str());
		} else if (property=="guesses") {
			if (value=="infinity") config.guesses=-1;
			else config.guesses = atoi(value.c_str());
		} else {
			assert(0);
		}
	}
	return config;
}

vector<President> getPresidents(Config config, string& placeholder) {
	cout<<"Getting president data...";
	ifstream presidents_list;
	presidents_list.open("presidents.txt");
	vector<President> presidents;
	President current_president;
	while(!presidents_list.eof()) {
		getline(presidents_list, placeholder);
		if (atoi(placeholder.c_str()) > config.presidents) break;
		getline(presidents_list, current_president.name);
		getline(presidents_list, current_president.years);
		getline(presidents_list, current_president.party);
		getline(presidents_list, placeholder);
		presidents.push_back(current_president);
	}
	presidents_list.close();
	cout<<"Done!"<<endl;
	return presidents;
}

void addToStats(int president, bool correct, string& placeholder) {
	vector<string> stats_lines;
	ifstream stats_read;
	stats_read.open("stats.txt");
	while (!stats_read.eof()) {
		getline(stats_read, placeholder);
		stats_lines.push_back(placeholder);
	}
	stats_read.close();
	stringstream new_line;
	for (unsigned int i = 0; i < stats_lines.size(); i++) {
		new_line<<president;
		if (stats_lines[i].substr(0, 2) != "//" && stats_lines[i].substr(0, stats_lines[i].find(" ")) == new_line.str()) {
			new_line.str("");
			int new_stats = (((stats_lines[i].find("X") != string::npos) || (stats_lines[i].find("O") != string::npos)) ? 0 : 1);
			stats_lines[i] = stats_lines[i].substr(0, (stats_lines[i].size() - new_stats));
			new_line<<stats_lines[i]<<(correct ? "O" : "X");
			stats_lines[i] = new_line.str();
		}
		new_line.str("");
	}
	ofstream stats;
	stats.open("stats.txt");
	for (unsigned int i = 0; i < stats_lines.size(); i++) {
		stats<<stats_lines[i];
		if (i<(stats_lines.size() - 1)) stats<<endl;
	}
	stats.close();
}

void resetStats(string& placeholder) {
	ifstream stats_template;
	stats_template.open("stats_template.txt");
	ofstream stats;
	stats.open("stats.txt", ofstream::trunc);
	while (!stats_template.eof()) {
		getline(stats_template, placeholder);
		stats<<placeholder<<endl;
	}
	stats_template.close();
	stats.close();
	cout<<"Statistics reset!"<<endl;
}

int main(int argc, char* argv[]) {
	string placeholder;
	if (argc > 1) {
		string argument = argv[1];
		if (argument == "-reset") resetStats(placeholder);
	}
	Config config = getConfig(placeholder);
	vector<President> presidents = getPresidents(config, placeholder);
	srand(time(NULL));
	int random_president;
	bool correct_answer;
	string correct;
	vector<int> presidents_done;
	int quizzes = min((size_t)config.quizzes, presidents.size());
	for (int i = 0; i < quizzes; i++) {
		do {
			random_president = (rand() % (presidents.size()));
		} while (find(presidents_done.begin(), presidents_done.end(), random_president) != presidents_done.end());
		presidents_done.push_back(random_president);
		for (int j = 0; j < 3; j++) {
			int guesses = config.guesses;
			correct_answer = false;
			while(!correct_answer && guesses > 0) {
				switch (j) {
					case 0:
						cout<<"Who was the "<<(random_president + 1)<<getSuffix(random_president + 1)<<" president?"<<endl;
						getline(cin, placeholder);
						if (placeholder != presidents[random_president].name.substr(0, (presidents[random_president].name.size() - 1))) {
							cout<<"Incorrect answer.  Try again."<<endl;
							guesses--;
							break;
						} else {
							correct_answer = true;
							break;
						}
					case 1:
						cout<<"During which years was he president?"<<endl;
						getline(cin, placeholder);
						if (placeholder != presidents[random_president].years.substr(0, (presidents[random_president].years.size() - 1))) {
							cout<<"Incorrect answer.  Try again."<<endl;
							guesses--;
							break;
						} else {
							correct_answer = true;
							break;
						}
					case 2:
						cout<<"What party was he affiliated with?"<<endl;
						getline(cin, placeholder);
						if (placeholder != presidents[random_president].party.substr(0, (presidents[random_president].party.size() - 1))) {
							cout<<"Incorrect answer.  Try again."<<endl;
							guesses--;
							break;
						} else {
							correct_answer = true;
							break;
						}
				}
			}
			if (guesses == 0) {
				cout<<endl<<"Congratulations.  You're a failure."<<endl;
				addToStats((random_president + 1), false, placeholder);
				exit(0);
			} else {
				cout<<"Good!"<<endl;
			}
		}
		addToStats((random_president + 1), true, placeholder);
	}
}