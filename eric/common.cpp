#include "common.h"
#include<sstream>
#include<iostream>

using namespace std;

vector<unsigned> range(unsigned lim){
	vector<unsigned> r;
	for(unsigned i=0;i<lim;i++){
		r|=i;
	}
	return r;
}

string first_word(string s){
	stringstream ss;
	for(unsigned i=0;i<s.size() && s[i]!=' ';i++){
		ss<<s[i];
	}
	return ss.str();
}

Tag::Tag(string s):name(first_word(s)){
	cout<<"<"<<s<<">\n";
}

Tag::~Tag(){ cout<<"</"<<name<<">\n"; }

unsigned max_pts(unsigned totes,unsigned cans,unsigned max_stack_height){
	unsigned r=0;
	while(totes && max_stack_height){
		auto stack_height=min(totes,max_stack_height);
		totes-=stack_height;
		r+=2*stack_height;
		if(cans){
			r+=4*stack_height;
			cans--;
		}
	}
	return r;
}

