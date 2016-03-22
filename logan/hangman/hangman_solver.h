#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include <array>
#include <set>
#include <stdlib.h>
#include <algorithm>

#define NYI { \
	std::cout<<"\nnyi "<<__LINE__<<"\n"; \
	exit(44); \
}

#define FILENAME "words.txt"
#define ATTEMPTS 6

typedef std::string Word;

enum Letter{A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,LETTER};//enum of all letters in their place

class Freq{
	private:
	char letter_;
	int count_;
	
	public:
	void add();
	char letter();
	int count();
	
	Freq();
	Freq(char);
	Freq(char,int);
};

struct Game{
	private:
	std::vector<char> incorrect;
	std::vector<char> correct;
	std::vector<Word> possibles;
	char get_guess();
	void update_possibles();
	
	public:
	Word word;
	std::string draw_gallows();
	bool found();
	bool failed();
	void operator()();
	
	Game();
	Game(unsigned int);
};

bool operator<(Freq, Freq);
bool operator==(Freq,Freq);
bool operator!=(Freq,Freq);

std::ostream& operator<<(std::ostream&, Freq);

template<class Type, long unsigned int Len>
std::ostream& operator<<(std::ostream&,std::array<Type,Len>);

template<typename T>
std::ostream& operator<<(std::ostream&, std::set<T>);

const std::array<char,Letter::LETTER> GEN_ORDER{'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};//general frequency of letter occurences
const std::array<char,Letter::LETTER> LETTERS{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};//all letters in alphabetical order

const std::vector<Freq> GEN_FREQ=[&]{//general order of letters as type Freq
	std::vector<Freq> freq;
	int num=GEN_ORDER.size();
	for(char c:GEN_ORDER){
		freq.push_back(Freq{c,num});
		num--;
	}
	return freq;
}();