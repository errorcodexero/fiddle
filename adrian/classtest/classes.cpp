#include <iostream>
#include <memory>

//compile w/ -std=c++14

using namespace std;

struct Animal{
	virtual void make_noise()=0;
	Animal(){}
};
	
struct Cow:public Animal{
	void make_noise(){
		cout<<"oink"<<endl;
	}
	Cow():Animal(){}
};

struct Dog:public Animal{
	bool angry;
	void make_noise(){
		if(angry)cout<<"hiss"<<endl;
		else cout<<"meow"<<endl;
	}
	Dog():Animal(){	
		angry=true;
	}
};

int main(){
	unique_ptr<Animal>a;
	a=make_unique<Dog>();
	a->make_noise();
	return 0;
}

