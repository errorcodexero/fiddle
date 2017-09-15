#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

const string inp = "roster.txt";


class Student {
	string name;
	double grade[6], avg_grade;
	double avg(double *g, int l) {
		double s = 0;
		for (int i = 0; i < l; i++) {
			s += g[i];
		};
		return (double)(s / l);
	}
	char letterGrade(double g) {
		if ((g >= 90)) return 'A';
		else if (g >= 80) return 'B';
		else if (g >= 70) return 'C';
		else if (g >= 60) return 'D';
		else return 'F';
	}
public:
	Student(string name) {
		this->name = name;
	}

	string getName() {
		return name;
	}
	void setGrade(int index, double grade) {
		this->grade[index] = grade;
	}
	double getGrade(int index) {
		return grade[index];
	}
	void setGrades(double *grades) {
		for (int i = 0; i < 6; i++) {
			grade[i] = grades[i];
		};
	}
	void getGrades(double r[]) {
		/*for (int i = 1; i < 6; i++) {
			cout << grade[i] << endl;
		};*/
		for (int i = 0; i < 6; i++) {
			r[i] = grade[i];
		}
	}
	double getAvg() {
		return avg(grade, 6);
	}
	char avgletter() {
		double g = getAvg();
		return letterGrade(g);
	}
	char subjLetter(int index) {
		return letterGrade(grade[index]);
	}
};

class Gradebook {
	string id;
	vector<Student> list;
public:
	Gradebook(string id) {
		this->id = id;
	}
	unsigned int classSize() {
		return list.size();
	}
	double getClassAvg() {
		double s = 0;
		for (int i = 0; i < list.size(); i++) {
			s += list[i].getAvg();
		}
		return (double)(s / 20);
	}

	double getStudentAvg(int index) {
		return list[index].getAvg();
	}
	char getStudentLetter(int index) {
		return list[index].avgletter();
	}
	Student topStudent() {
		double e = 0;
		int i, f = 0;
		for (i = 0; i < list.size(); i++) {
			double k = list[i].getAvg();
			if (k > e) { e = k; f = i; };
		}
		return list[f];
	}
	Student botStudent() {
		double e = 600;
		int i, f = 0;
		for (i = 0; i < list.size(); i++) {
			double k = list[i].getAvg();
			if (k < e) { e = k; f = i; };
		}
		return list[f];
	}
	void addStudent(Student a) {
		list.push_back(a);
	}
	int gradeStats(char g) {
		int l = list.size();
		int c = 0;
		for (int i = 0; i < l; i++) {
			if (list[i].avgletter() == g) {
				c++;
			}
		}
		return c;
	}
	void getAllGrades(double r[], int index) {
		list[index].getGrades(r);
	}
	/*void addStudent(Student a, int index) {
		int i;
		Student t();
		list.push_back(list[list.size()]);
		for (i = 0; i < list.size(); i++) {
			t = list[i + 1];
			list[i+1] = list[i]
		}
	}*/
};
string topGrade(Gradebook a) {
	Student r = a.topStudent();
	return r.getName();
}
string name(string s) {
	string r;
	int i = 0, l = s.length();
	while ((i < l) && (s[i]!=':')) {
		r += s[i]; i++;
	}
	return r;
}
void grades(string s,  Student &a) {
	double g=0;
	int i = 0, l = s.length();
	while ((i < l) && (s[i] != ':')) {
		i++;
	}
	i++;
	//i = 0;
	int c = 0;
	string temp = "";
	while (i < l) {
		string buffer="" ;
		buffer = s[i];
		i++;
		if ((buffer == ",")) {
			g = stod(temp);
			a.setGrade(c, g);
			temp = "";
			c++;
		}
		else {
			temp += buffer;
			if (i == l) {
				g = stod(temp);
				a.setGrade(c, g);
				temp = "";
				c++;
			}
		}
	}
}
void read(Gradebook &a, string fn) {
	ifstream f;
	f.open(fn);
	string buffer;
	if (f.good()) {
		while (!f.eof()) {
			getline(f, buffer);
			Student t(name(buffer));
			grades(buffer, t);
			a.addStudent(t);
		}
	}
	f.close();
}
void write(Gradebook a, string fn, int mode = 0, int index = 0) {
	ofstream f;
	f.open(fn);
	if (f.good()) {
		int sz = a.classSize();
		if (mode == 0) {
			for (int i = 0; i < sz; i++) {
					f << a.getStudentAvg(i) << endl;
				}
		}
		else if (mode == 1) {
			double g[6];
			for (int i = 0; i < sz; i++) {
				a.getAllGrades(g, i);
				for (int j = 0; j < 6; j++) {
					f << g[j] << ' ';
				}
				f << endl;
			}
		}
		else if (mode == 2) {
			for (int i = 0; i < sz; i++) {
				f << a.getStudentLetter(i) << endl;
			}
		}
		
	}
	f.close();
}
int main() {
	//cout<<"Hello World!"<<endl;
	Gradebook gb("Class 1");
	read(gb, "roster.txt");
	//cout << gb.getStudentAvg(0) << endl;
	write(gb, "grades.txt",2); //0(default) for all averages, 1 for all grades, 2 for all letters
	return 0;
}


