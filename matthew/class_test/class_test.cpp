#include <iostream>
#include <memory>

using namespace std;

struct Animal {
	virtual void make_noise()=0;
};

struct Cat : Animal {
	void make_noise() {
		cout<<"Meow\n";
	}
};

struct Dog : Animal {
	Dog():big(false){};
	Dog(bool b):big(b){};

	bool big;
	void make_noise() {
		if (big) cout<<"Woof\n";
		else cout<<"Arf\n";
	}
};

struct CatDog : Cat,Dog {
	
};

int main() {
	unique_ptr<Animal> a = make_unique<Cat>();
	a->make_noise();
	
	unique_ptr<Dog> d = make_unique<Dog>(true);
	d->make_noise();
	
	CatDog* cd = new CatDog();
	//cd->make_noise();
	delete cd;

	return 0;
}
