#ifndef HANGMAN_H
#define HANGMAN_H

#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>
#include <array>
#include <set>
#include <vector>

#define NYI { \
	std::cout<<"\nnyi "<<__LINE__<<"\n"; \
	assert(0); \
}

#define FILENAME "words.txt"
#define LOG_FILE "hangman_log.txt"
#define ATTEMPTS 6

template<class Type, long unsigned int Len>
std::ostream& operator<<(std::ostream& o,std::array<Type,Len> a){
	o<<"(";
	for(unsigned int i=0; i<a.size(); i++){
		o<<a[i];
		if(i<a.size()-1)o<<",";
		o<<"\n";
	}
	return o<<")";
}

template<typename T>
std::ostream& operator<<(std::ostream& o, std::set<T> s){
	o<<"(";
	unsigned int j=0;
	for(auto i=s.begin(); i!=s.end(); i++){
		o<<*i;
		if(j<s.size()-1)o<<",";
		j++;
	}
	return o<<")";
}

template<typename T>
std::ostream& operator<<(std::ostream& o,std::vector<T> v){
	o<<"(";
	for(unsigned int i=0; i<v.size(); i++){
		o<<v[i];
		if(i<v.size()-1) o<<",";
	}
	return o<<")";
}

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

struct Solver{
	private:
	std::vector<char> incorrect;
	std::vector<char> correct;
	
	std::vector<Word> possibles;
	void update_possibles();
	
	public:
	bool found();
	bool failed();
			
	void right(char);
	void wrong(char);
	
	Word known;
	char get_guess();
	void fill(std::vector<unsigned int>,char);
	std::string print_word();
	unsigned int remaining();
	void operator()();
	
	explicit Solver(unsigned int);
};

struct Game{
	private:
	Word word;
	std::vector<char> incorrect;
	std::vector<char> correct;
	
	public:
	void wrong(char);
	void right(char);
	
	Word print;
	unsigned int length();
	bool done();
	unsigned int remaining();
	std::string print_word();
	bool check(char);
	void operator()();
	
	Game();
	Game(Word);
};

bool operator<(Freq, Freq);
bool operator==(Freq,Freq);
bool operator!=(Freq,Freq);

std::ostream& operator<<(std::ostream&, Freq);

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

std::string draw_gallows(unsigned int);
std::string get_word();

inline void log(bool result_status, std::string word, std::string source){
	std::string result="Loss ";
	if(result_status) result="Win  ";
	std::ofstream logger(LOG_FILE,std::ios::app);
	logger<<source<<"  "<<result<<" - "<<word<<"\n";
	logger.close();
}

#endif
