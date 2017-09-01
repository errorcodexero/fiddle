#include <iostream>
#include <vector>

using namespace std;




class Student {
	string name;
	double grade[6],avg_grade;
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

class Gradebook {
	string id;
	int current_size=0;
	vector<Student> list;
public:
	Gradebook (string id) {
		this->id=id;
	}
	double getClassAvg() {
		double s=0;
		for(int i=0;i<list.size();i++) {
			s+=list[i].getAvg();			
		}
		return (double)(s/20);
	}

	double getStudentAvg(int index) {
		return list[index].getAvg();	
	}
	Student topStudent() {
		double e=0,f=0;
		int i;
		for(i=0;i<list.size();i++) {
			double k=list[i].getAvg();
			if (k>e) { e=k; f=i;};
		}
		return list[f];	
	}
	Student botStudent() {
		double e=600,f=0;
		int i;
		for(i=0;i<list.size();i++) {
			double k=list[i].getAvg();
			if (k<e) { e=k; f=i;};
		}
		return list[f];	
	}
	void addStudent(Student a) {
		list.push_back(a);	
	}
};
string topGrade(Gradebook a) {
	Student r = a.topStudent();
	return r.getName();
}
int main(){
	//cout<<"Hello World!"<<endl;
	Gradebook gb("ABC");
	Student john("john");
	Student tim("tim");
	Student jeff("jeff");
	double j[6] = {10,20,30,40,50,60}, t[6] = {20,30,40,50,60}, jf[6] = {30,40,50,60,70,80};
	john.setGrades(j); tim.setGrades(t); jeff.setGrades(jf);
	gb.addStudent(john);
	gb.addStudent(tim);
	gb.addStudent(jeff);
	cout << topGrade(gb) << endl;
	return 0;
}
