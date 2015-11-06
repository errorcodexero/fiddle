/*Author: Logan Traffas
TODO:
	- Added user's answer for guess
*/
#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <assert.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#define nyi { \
	std::cout<<"\nnyi "<<__LINE__<<"\n"; \
	exit(44); \
}

const std::vector<char> GEN_FREQ={'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};
const std::vector<char> CAPS_GEN_FREQ={'E','T','A','O','I','N','S','H','R','D','L','C','U','M','W','F','G','Y','P','B','V','K','J','X','Q','Z'};


template<typename T, typename S>
std::ostream& operator<<(std::ostream& o, std::pair<T,S> p){
	return o<<"<"<<p.first<<" "<<p.second<<">";
}

template<typename T>
std::ostream& operator<<(std::ostream& o, std::vector<T> v){
	o<<"<";
	for(unsigned int i=0; i<v.size(); i++){
		o<<v[i]<<" ";
	}
	o<<">";
	return o;
}

std::string print(std::string w){
	std::string s;
	for(unsigned int i=0; i<w.size(); i++){
		if(w[i]==' ')s+=" _ ";
		else s+=' '+w[i]+' ';
	}
	return s;
}

template<typename T>
void remove(std::vector<T>& v,std::vector<unsigned int> r){
	if(r.size()==v.size())v={};
	if(v.size()>0 && r.size()>0){
		for(unsigned int i=r.size()-1; i>0; i--){
			v.erase(v.begin()+r[i]);
		}
	}
}

std::vector<std::string> init_list(std::string w){
	std::ifstream words("test.txt");
	std::vector<std::string> possibles;
	while(!words.eof()){
		std::string s;
		std::getline(words,s);
		possibles.push_back(s);
	}
	std::vector<unsigned int> r;
	for(unsigned int i=0; i<possibles.size(); i++){
		if(find(possibles[i].begin(),possibles[i].end(),'\'')!=possibles[i].end())r.push_back(i);
	}
	remove(possibles,r);//Remove words that have apostrophes
	r.clear();	
	for(unsigned int i=0; i<possibles.size(); i++){
		for(unsigned int j=0; j<possibles[i].size(); j++){
			if(find(GEN_FREQ.begin(),GEN_FREQ.end(),tolower(possibles[i][j]))!=GEN_FREQ.end())break;
			r.push_back(i);
		}
	}
	remove(possibles,r);//Remove words that have unaccepted characters
	r.clear();
	for(unsigned int i=0; i<possibles.size(); i++){
		if(possibles[i].size()!=w.size())r.push_back(i);
	}
	remove(possibles,r);//Remove words that are too long
	words.close();
	return possibles;	
}

void update_possibles(std::string w,std::vector<char> wrong,std::vector<std::string>& possibles){
	if(wrong.size()>0){
		std::vector<unsigned int> r;
		for(unsigned int i=0; i<possibles.size(); i++){
			if(find(possibles[i].begin(),possibles[i].end(),wrong.back())!=possibles[i].end())r.push_back(i);
		}
		remove(possibles,r);//Remove words that have apostrophes
	}
}

std::vector<std::pair<char, unsigned int>> count(std::string all){
	std::vector<std::pair<char, unsigned int>> counted;
	std::vector<char> letters=GEN_FREQ;
	for(unsigned int i=0; i<letters.size(); i++){
		counted.push_back({letters[i],0});
	}
	for(char c: all){
		unsigned int i=0;
		for(char a: letters){
			if(c==a)counted[i].second++;
			i++;
		}
	}
	return counted;
}

std::vector<std::pair<char,unsigned int>> order(std::vector<std::pair<char,unsigned int>>& v,unsigned int size){
	std::pair<char,unsigned int> max={{},0};
	unsigned int loc=0;
	for(unsigned int i=0; i<size; i++){
		if(v[i].second>=max.second){
			max=v[i];
			loc=i;
		}
	}
	v.erase(v.begin()+loc);
	v.push_back(max);
	if(size>1){
		size--;
		order(v,size);
	}
	return v;
	
}

std::vector<char> order_equal(std::vector<std::pair<char,unsigned int>> ordered,std::vector<char> real_freq){
	std::vector<std::pair<char,unsigned int>> compare=ordered;
	for(unsigned int i=0; i<ordered.size(); i++){
		for(unsigned int j=0; j<compare.size(); j++){
			if(ordered[i].second==compare[j].second && i!=j){
				unsigned int loc1=0,loc2=0,loc3=0;
				for(unsigned int k=0; k<GEN_FREQ.size(); k++){
					if(ordered[i].first==GEN_FREQ[k]){
						loc1=k;
						break;
					}
				}
				for(unsigned int k=0; k<GEN_FREQ.size(); k++){
					if(compare[j].first==GEN_FREQ[k]){
						loc2=k;
						break;
					}
				}
				char first=(loc1<loc2)?ordered[i].first:compare[j].first,second=(loc1>loc2)?ordered[i].first:compare[j].first;
				unsigned int x=0,y=0;
				for(unsigned int k=0; k<real_freq.size(); k++){
					if(first==real_freq[k])x=k;
					else if(second==real_freq[k])y=k;
				}
				if(x<y)return real_freq;
				iter_swap(real_freq.begin()+x,real_freq.begin()+y);
				return real_freq;
			}
		}	
	}
	return real_freq;
}

std::vector<char> set_freq(std::string w,std::vector<char> wrong,std::vector<std::string> possibles){
	std::vector<char> real_freq;
	update_possibles(w,wrong,possibles);
	std::string all;
	for(unsigned int i=0; i<possibles.size(); i++){
		for(char c: possibles[i]){
			all+=c;
		}
	}
	std::vector<std::pair<char,unsigned int>> ordered=count(all);
	order(ordered,ordered.size());
	for(std::pair<char,unsigned int> p: ordered){
		real_freq.push_back(p.first);
	}
	real_freq=order_equal(ordered, real_freq);
	return real_freq;
}

char get_guess(std::string w,std::vector<char> wrong,std::vector<std::string> possibles){
	std::vector<char> freq=set_freq(w,wrong,possibles);
	return freq.front();
}

int main(){
	std::string w;
	unsigned int length;
	std::cout<<"Enter number of letters in the word: ";
	std::cin>>length;
	for(unsigned int i=0; i<length; i++)w+=' ';
	std::vector<std::string> possibles=init_list(w);
	std::vector<char> wrong;
	while(true){
		char guess=get_guess(w,wrong,possibles), yn='n';
		std::cout<<"Known: "<<print(w)<<". Does it have the letter \'"<<guess<<"\'?(y/n) ";
		std::cin>>yn;
		if(yn=='y'){
			
		}
		else{
			wrong.push_back(guess);
		}
		break;
	}
	return 0;
}
