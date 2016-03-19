#include "hangman_solver_new.h"
#include <fstream>
#include <assert.h>
#include <stdlib.h>
#include <algorithm>

#define NYI { \
	std::cout<<"\nnyi "<<__LINE__<<"\n"; \
	exit(44); \
}

Freq::Freq():letter_('a'),count_(0){}
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

Game::Game():word(""),incorrect({}),correct(){}
Game::Game(unsigned int a):incorrect({}),correct({}){
	word=[&]{
		Word n;
		for(unsigned int i=0;i<a; i++)n.append(" ");
		return n;
	}();
}

bool operator<(Freq a, Freq b){
	if(a.count()<b.count()) return true;
	if(a.count()>b.count()) return false;
	if(a.letter()==b.letter()) return false;
	unsigned int a_num=0,b_num=0;
	for(unsigned int i=0;i<GEN_ORDER.size(); i++){
		if(a.letter()==GEN_ORDER[i])a_num=i;
		if(b.letter()==GEN_ORDER[i])b_num=i;
	}
	return a_num>b_num;//greater than because GEN_ORDER is ordered from most common to least
}

bool operator==(Freq a,Freq b){
	return a.letter()==b.letter() && a.count()==b.count();
}

bool operator!=(Freq a,Freq b){
	return !(a==b);
}

std::ostream& operator<<(std::ostream& o, Freq a){
	return o<<"Freq("<<a.letter()<<","<<a.count()<<")";
}

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

std::vector<Word> get_list(unsigned int len,Game game){
	std::ifstream in(FILENAME);
	std::vector<Word> words;
	while(!in.eof()){
		Word word;
		std::getline(in,word);
		if(word.length()!=len)continue;
		bool skip=0;
		for(char c:word){
			for(char cc:game.incorrect){
				if(c==cc){
					skip=1;
					break;
				}
			}
		}
		if(skip)continue;
		skip=0;
		for(unsigned int i=0; i<len; i++){
			if(game.word[i]!=' ' && word[i]!=game.word[i]){
				skip=1;
				break;
			}
		}
		if(skip)continue;
		words.push_back(word);
	}
	in.close();
	return words;
}

void init(std::array<Freq,Letter::LETTER>& freq){
	for(unsigned int i=0;i<Letter::LETTER; i++){
		freq[i]={LETTERS[i],0};
	}
}

void add(const char c,std::array<Freq,Letter::LETTER>& freq){
	for(int i=0; i<Letter::LETTER; i++){
		if(c==freq[i].letter()){
			freq[i].add();
			break;
		}
	}
}

std::array<Freq,Letter::LETTER> get_freq(unsigned int len,Game game){
	std::vector<Word> words=get_list(len,game);
	std::array<Freq,Letter::LETTER> freq;
	init(freq);
	for(Word w: words){
		for(char c: w){
			add(c,freq);
		}
	}
	return freq;
}

std::set<Freq> get_order(unsigned int len, Game game){
	std::array<Freq,Letter::LETTER> freq=get_freq(len,game);
	std::set<Freq> s;
	for(Freq a: freq){
		s.insert(a);
	}
	std::cout<<"\n"<<s<<"\n";
	return s;
}

char get_guess(unsigned int len,Game game){
	std::set<Freq> freq=get_order(len,game);
	unsigned int num=1;
	char guess='1';
	while(true){
		std::set<Freq>::iterator it=std::next(freq.begin(),Letter::LETTER-num);
		Freq f=*it;
		char n=f.letter();
		bool skip=0;
		for(unsigned int i=0;i<game.correct.size(); i++){
			if(n==game.correct[i]){
				num++;
				skip=1;
				break;
			}
		}
		for(unsigned int i=0;i<game.incorrect.size(); i++){
			if(n==game.incorrect[i]){
				num++;
				skip=1;
				break;
			}
		}
		if(skip)continue;
		guess=n;
		break;
	}
	return guess;
}

std::string print_word(Word w){
	std::string s;
	for(char c:w){
		if(c==' ')s.append(" _ ");
		else{
			s+=' ';
			s+=c;
			s+=' ';
		}
	}
	return s;
}

bool finished(Word w){
	for(char c:w){
		if(c==' ')return 0;
	}
	return 1;
}

int main(){
	unsigned int len=0;
	std::cout<<"How long is the word? ";
	std::cin>>len;
	Game game(len);
	while(true){
		char guess=get_guess(game.word.length(),game), yn='n';
		std::cout<<draw_gallows(game.incorrect.size())<<"\nKnown: "<<print_word(game.word)<<". Does it have the letter \'"<<guess<<"\'?(y/n) ";
		std::cin>>yn;
		if(yn=='y'){
			game.correct.push_back(guess);
			std::string locs;
			std::cout<<"\nWhere is it in the word?(Please write the locaions separated by commas) ";
			std::cin>>locs;
			std::vector<unsigned int> r,num;
			for(unsigned int i=0; i<locs.size(); i++){
				if(locs[i]==' ')r.push_back(i);
			}
			for(unsigned int i=r.size(); i>0; i--){
				locs.erase(locs.begin()+r[i]);
			}
			unsigned int temp=0;
			for(unsigned int i=0; i<locs.size()+1; i++){
				if(locs[i]==','){
					num.push_back(atoi((locs.substr(temp,(i-temp))).c_str())-1);
					temp=i+1;
				}
			}
			num.push_back(atoi((locs.substr(temp,(locs.size()-temp))).c_str())-1);
			for(unsigned int i:num)game.word[i]=guess;			
		} else{
			game.incorrect.push_back(guess);
		}
		if(finished(game.word)){
			std::cout<<"\n"<<draw_gallows(game.incorrect.size())<<"\nI WIN! The word is \""<<game.word<<"\"\n";
			break;
		}
		else if(game.incorrect.size()>=ATTEMPTS){
			std::cout<<"\n"<<draw_gallows(game.incorrect.size())<<"\nI lose :'(\nWhat was the word? ";
			std::string c;
			std::cin>>c;
			break;
		}
	}
	return 0;
}