#include <iostream>

using namespace std;



class Student {
	string name;
	double grade[6];
	double avg(double *g, int l) {
		double s=0;
		for(int i=0;i<l;i++) {
			s+=g[i];
		};
		return (double)(s/l);
	}
	char letterGrade(double g) {
		if((g>=90)) return 'A';
		else if (g>=80) return 'B';
		else if (g>=70) return 'C';
		else if (g>=60) return 'D';
		else return 'F';
	}
public:	
	Student(string name) {
		this->name=name;	
	}

	string getName() {
		return name;
	}
	void setGrade(int index, double grade) {
		this->grade[index]=grade;
	}
	double getGrade(int index) {
		return grade[index];
	}
	void setGrades(double *grades) {
		for(int i=0;i<6;i++) {
			grade[i]=grades[i];		
		};
	}
	void getGrades() {
		for(int i=1;i<6;i++){
			cout << grade[i] << endl;
		};
		
	}
	double getAvg() {
		return avg(grade,6);
	}
	char avgletter() {
		double g=getAvg();
		return letterGrade(g);
	}
	char subjLetter(int index) {
		return letterGrade(grade[index]);	
	}
};

int main(){
	//cout<<"Hello World!"<<endl;
	Student john("John");
	double g[6] = {60,80,75,34,66,95};
	john.setGrades(g);
	john.getGrades();
	cout << john.getAvg() << endl;
	cout << john.avgletter() << endl;
	cout << john.subjLetter(3);
	return 0;
}
