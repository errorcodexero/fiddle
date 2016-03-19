#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include <vector>
#include <set>
#include <stdlib.h>
#include <algorithm>

#define NYI { \
	std::cout<<"\nnyi "<<__LINE__<<"\n"; \
	exit(44); \
}

typedef std::string Word;

class Freq{
	private:
	char letter_;
	int count_;
	
	public:
	void add();
	char letter();
	int count();
	explicit Freq(char);
	Freq(char,int);
};

Freq::Freq(char a):letter_(a),count_(0){}
Freq::Freq(char a,int b):letter_(a),count_(b){}

void Freq::add(){
	count_++;
}

char Freq::letter(){
	return letter_;
}

int Freq::count(){
	return count_;
}

bool operator<(Freq a, Freq b){
	return a.count()<b.count();
}

std::ostream& operator<<(std::ostream& o, Freq a){
	return o<<"Freq("<<a.letter()<<","<<a.count()<<")";
}

const std::set<Freq> GEN_FREQ=[&]{
	std::set<Freq> freq;
	const std::vector<char> ORDER={'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};
	int num=ORDER.size();
	for(char c:ORDER){
		freq.insert({c,num});
		num--;
	}
	return freq;
}();

std::string draw_gallows(const unsigned int remaining_attempts){//Draws the gallows with the appropriate amount of body parts. 
	std::string gallows;
	if(remaining_attempts==0){
		gallows="      _______\n     |/       \n     |         \n     |          \n     |        \n     |          \n     |\n  ___|___\n";//Empty Gallows
	}
	else if(remaining_attempts==1){
		gallows="      _______\n     |/      |\n     |      (_)\n     |          \n     |        \n     |          \n     |\n  ___|___\n";//Head
	}
	else if(remaining_attempts==2){
		gallows="      _______\n     |/      |\n     |      (_)\n     |       |  \n     |       |\n     |          \n     |\n  ___|___\n";//Torso
	}
	else if(remaining_attempts==3){
		gallows="      _______\n     |/      |\n     |      (_)\n     |      \\| \n     |       |\n     |          \n     |\n  ___|___\n";//Left arm
	}
	else if(remaining_attempts==4){
		gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |          \n     |\n  ___|___\n";//Right arm 
	}
	else if(remaining_attempts==5){
		gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      / \n     |\n  ___|___\n";//Left leg
	}
	else if(remaining_attempts==6){
		gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      / \\\n     |\n  ___|___\n";//Right leg
	}
	return gallows;
}

int main(){
	for(auto i:GEN_FREQ){
		std::cout<<i<<"\n";
	}
	NYI
	return 0;
}