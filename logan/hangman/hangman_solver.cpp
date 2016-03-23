#include "hangman.h"
#include <stdlib.h>

Freq::Freq():letter_('a'),count_(0){}
Freq::Freq(char a):letter_(a),count_(0){}
Freq::Freq(char a,int b):letter_(a),count_(b){}

void Freq::add(){ count_++; }

char Freq::letter(){ return letter_; }

int Freq::count(){ return count_; }

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

std::vector<Word> get_list(const unsigned int len){
	std::ifstream in(FILENAME);
	std::vector<Word> words;
	while(!in.eof()){
		Word new_word;
		std::getline(in,new_word);
		if(new_word.length()!=len)continue;
		words.push_back(new_word);
	}
	in.close();
	return words;
}

Solver::Solver(unsigned int a):incorrect({}),correct({}){
	known=[&]{
		Word n;
		for(unsigned int i=0;i<a; i++)n.append(" ");
		return n;
	}();
	possibles=get_list(known.length());
}

unsigned int Solver::remaining(){
	return incorrect.size();
}

void Solver::update_possibles(){
	std::vector<unsigned int> to_remove;
	for(unsigned int i=0;i<possibles.size();i++){
		bool remove=false;
		for(char c:possibles[i]){
			for(char cc:incorrect){
				if(c==cc){
					remove=true;
					break;
				}
			}
			if(remove) break;
		}
		if(remove){
			to_remove.push_back(i); 
			continue;
		}
		for(unsigned int j=0; j<known.length(); j++){
			if(known[j]!=' ' && possibles[i][j]!=known[j]){
				remove=true;
				break;
			}
		}
		if(remove) to_remove.push_back(i);
	}
	for(unsigned int i=to_remove.size(); i>0; i--) possibles.erase(possibles.begin()+to_remove[i-1]);
}

std::set<Freq> get_freq(std::vector<Word> words){
	std::set<Freq> s;
	{
		std::array<Freq,Letter::LETTER> freq=[&]{
			std::array<Freq,Letter::LETTER> frequency;
			for(unsigned int i=0;i<Letter::LETTER; i++) frequency[i]={LETTERS[i],0};
			for(Word w: words){
				for(char c: w){
					for(int i=0; i<Letter::LETTER; i++){
						if(tolower(c)==frequency[i].letter()){
							frequency[i].add();
							break;
						}
					}
				}
			}
			return frequency;
		}();
		for(Freq a: freq) s.insert(a);
	}
	return s;
}

char Solver::get_guess(){
	update_possibles();
	std::set<Freq> freq=get_freq(possibles);
	unsigned int num=1;
	char guess='1';
	while(true){
		std::set<Freq>::iterator it=std::next(freq.begin(),Letter::LETTER-num);
		Freq f=*it;
		char n=f.letter();
		bool skip=0;
		for(unsigned int i=0;i<correct.size(); i++){
			if(n==correct[i]){
				num++;
				skip=1;
				break;
			}
		}
		for(unsigned int i=0;i<incorrect.size(); i++){
			if(n==incorrect[i]){
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

std::string Solver::print_word(){
	std::string s;
	for(char c:known){
		if(c==' ')s+="_ ";
		else{
			s+=c;
			s+=' ';
		}
	}
	return s;
}

void Solver::right(char c){
	correct.push_back(c);
}

void Solver::wrong(char c){
	incorrect.push_back(c);
}

void Solver::fill(std::vector<unsigned int> v,char c){
	for(unsigned int i:v) known[i]=c;
}

void Solver::operator()(){
	char guess=get_guess(), yn='n';
	std::cout<<draw_gallows(incorrect.size())<<"\nKnown: "<<print_word()<<". Does it have the letter \'"<<guess<<"\'?(y/n) ";
	std::cin>>yn;
	if(yn=='y'){
		right(guess);
		std::string locs;
		std::cout<<"\nWhere is it in the word?(Please write the locaions separated by commas) ";
		std::cin>>locs;
		std::vector<unsigned int> r,num;
		for(unsigned int i=0; i<locs.size(); i++){
			if(locs[i]==' ')r.push_back(i);
		}
		for(unsigned int i=r.size(); i>0; i--) locs.erase(locs.begin()+r[i]);
		unsigned int temp=0;
		for(unsigned int i=0; i<locs.size()+1; i++){
			if(locs[i]==','){
				num.push_back(atoi((locs.substr(temp,(i-temp))).c_str())-1);
				temp=i+1;
			}
		}
		num.push_back(atoi((locs.substr(temp,(locs.size()-temp))).c_str())-1);
		fill(num,guess);
	}
	else wrong(guess);
}

bool Solver::failed(){ return incorrect.size()>=ATTEMPTS; }

bool Solver::found(){
	for(char c:known){
		if(c==' ') return false;
	}
	return true;
}

#ifdef HANGMAN_SOLVER

int main(){
	unsigned int len=0;
	std::cout<<"How long is the word? ";
	std::cin>>len;
	Solver solver(len);
	while(!solver.found() && !solver.failed()){
		solver();
		if(solver.found()) std::cout<<"\n"<<draw_gallows(solver.remaining())<<"\nI WIN! The word is \""<<solver.known<<"\"\n";
		else if(solver.failed()){
			std::cout<<"\n"<<draw_gallows(solver.remaining())<<"\nI lose :'(\nWhat was the word? ";
			std::cin>>solver.known;
		}
	}
	return 0;
}

#endif