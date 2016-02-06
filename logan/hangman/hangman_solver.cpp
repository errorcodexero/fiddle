/*Author: Logan Traffas
TODO:
	- Remove remove1()
	- Bug fixes
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

template<typename T>
void remove1(std::vector<T>& v,std::vector<unsigned int> r){
	if(v.size()>0){
		for(unsigned int i=r.size(); i>0; i--){
			v.erase(v.begin()+r[i]);
		}
	}
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

std::vector<std::string> init_list(std::string w){
	std::ifstream words("words.txt");
	std::vector<std::string> possibles;
	while(!words.eof()){
		std::string s;
		std::getline(words,s);
		bool r=1;
		for(char c:s){
			if(find(GEN_FREQ.begin(),GEN_FREQ.end(),tolower(c))==GEN_FREQ.end()){
				r=0;
				break;
			}
		}
		if(find(s.begin(),s.end(),'\'')==s.end() && s.size()==w.size() && r){
			possibles.push_back(s);
		}
	}
	words.close();
	return possibles;	
}

void update_possibles(const std::string w,const std::vector<char> wrong,std::vector<std::string>& possibles){
	for(std::vector<std::string>::iterator i=possibles.begin(); i<possibles.end();){
		bool b=wrong.size()>0?0:1;
		for(char x:wrong){
			for(char c:*i){
				if(tolower(c)==tolower(x)){
					b=0;
					possibles.erase(i);
					break;
				} else b=1;
			}
		}
		if(b)i++;
	}
	for(std::vector<std::string>::iterator i=possibles.begin(); i<possibles.end();){
		bool b=0;
		for(std::string::const_iterator it=w.begin(); it<w.end();){
			if(*it==' '){
				b=1;
				it++;
				continue;
			}
			for(std::string::iterator ite=(*i).begin(); ite<(*i).end();){
				if(distance(w.begin(),it)==distance((*i).begin(),ite) && tolower(*it)!=tolower(*ite)){
					b=0;
					possibles.erase(i);
					break;
				} else b=1;
				ite++;
			}
			if(!b)break;
			it++;
		}
		if(b)i++;
	}
	//std::cout<<possibles<<"\n";
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
				unsigned int loc1=0,loc2=0;
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

std::vector<char> set_freq(std::string w,std::vector<char> wrong,std::vector<std::string>& possibles){
	std::vector<char> real_freq;
	update_possibles(w,wrong,possibles);
	if(possibles.size()==0)return GEN_FREQ;
	std::string all;
	for(unsigned int i=0; i<possibles.size(); i++){
		for(char c: possibles[i]){
			all+=c;
		}
	}
	std::vector<std::pair<char,unsigned int>> ordered=count(all);
	std::vector<unsigned int> r;
	for(unsigned int i=0; i<ordered.size(); i++){
		if(ordered[i].second==0)r.push_back(i);
	}
	remove1(ordered,r);//remove1 letters that aren't present in word base
	order(ordered,ordered.size());
	for(std::pair<char,unsigned int> p: ordered){
		real_freq.push_back(p.first);
	}
	real_freq=order_equal(ordered, real_freq);
	return real_freq;
}

char get_guess(const std::string w,std::vector<char> wrong,std::vector<std::string>& possibles){
	std::vector<char> freq=set_freq(w,wrong,possibles);
	for(unsigned int i=0; i<w.size(); i++){
		if(w[i]!=' ' && find(freq.begin(),freq.end(),w[i])!=freq.end())freq.erase(find(freq.begin(),freq.end(),w[i]));
	}
	for(unsigned int i=0; i<wrong.size(); i++){
		if(w[i]!=' ' && find(freq.begin(),freq.end(),wrong[i])!=freq.end())freq.erase(find(freq.begin(),freq.end(),wrong[i]));
	}
	std::cout<<"\n"<<freq<<"\n";
	return freq.front();
}

bool finished(std::string w){
	for(char c:w){
		if(c==' ')return 0;
	}
	return 1;
}

int main(){
	unsigned int length=0;
	std::cout<<"Enter number of letters in the word: ";
	std::cin>>length;
	std::string w;
	for(unsigned int i=0; i<length; i++)w+=' ';
	std::vector<std::string> possibles=init_list(w);
	std::vector<char> wrong;
	while(true){
		char guess=get_guess(w,wrong,possibles), yn='n';
		std::cout<<draw_gallows(wrong.size())<<"\nKnown: "<<print(w)<<". Does it have the letter \'"<<guess<<"\'?(y/n) ";
		std::cin>>yn;
		if(yn=='y'){
			std::cout<<"\nWhere is it in the word?(Please write the locaions separated by commas) ";
			std::string locs;
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
			for(unsigned int i:num)w[i]=guess;
		}
		else wrong.push_back(guess);
		if(wrong.size()>=6){
			std::cout<<"\n"<<draw_gallows(wrong.size())<<"\nI lose :'(\nWhat was the word? ";
			std::string c;
			std::cin>>c;
			break;
		}
		if(finished(w)){
			std::cout<<"\n"<<draw_gallows(wrong.size())<<"\nI WIN! The word is \""<<w<<"\"\n";
			break;
		}
	}
	std::cout<<"\nThanks for playing!\n";
	return 0;
}
