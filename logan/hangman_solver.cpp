/*
TODO:
	Must do:
	-Check capitals in smart guess
	-Use already known letters in smart guess
	Later:
	-Stop it from replacing letters (say user says there's "e" in place one then later says there's an "h" in place one)
*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <sstream>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

ostream& operator<<(ostream& o, vector<int> v){
	o<<"<";
	for(unsigned int i=0; i<v.size(); i++){
		o<<v[i];
		o<<" ";
	}
	o<<">";
	return o;
}

ostream& operator<<(ostream& o, vector<char> v){
	o<<"<";
	for(unsigned int i=0; i<v.size(); i++){
		o<<v[i];
		o<<" ";
	}
	o<<">";
	return o;
}

ostream& operator<<(ostream& o, vector<string> v){
	o<<"<";
	for(unsigned int i=0; i<v.size(); i++){
		o<<v[i];
		o<<" ";
	}
	o<<">";
	return o;
}

vector<char> set_smart_letter_frequency(string word){
	vector<char> letter_frequency;
	letter_frequency.resize(26);
	vector<char> all_letters={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	vector<char> disallowed={'\''};
	vector<pair<char,int>> quantified_letter_frequency;
	for(unsigned int i=0; i<all_letters.size(); i++){
		pair<char,int> initialize;
		initialize.first=all_letters[i];
		initialize.second=0;
		quantified_letter_frequency.push_back(initialize);		
	}
	vector<string> possible_words;
	fstream input_words;
	input_words.open("words.txt");
	for(unsigned int i=1; !input_words.eof(); i++){
		string possible_word;
		input_words>>possible_word;
		if(possible_word.size()==word.size()){
			possible_words.push_back(possible_word);
			for(unsigned int i=0; i<possible_word.size(); i++){
				for(unsigned int j=0; j<all_letters.size(); j++){
					if(possible_word[i]==all_letters[j])break;
					if(j==all_letters.size())possible_words.pop_back();
				}
			}
		}
		//cout<<"\nline:"<<i<<"   word:"<<possible_word<<"   size:"<<possible_word.size()<<"   target"<<word.size()<<"   vsize:"<<possible_words.size()<<"   vmax:"<<possible_words.max_size();
		//if(possible_words.size()!=0)cout<<"   latest:"<<possible_words.back();
	}
	input_words.close();
	for(unsigned int i=0; i<possible_words.size(); i++){
		for(unsigned int j=0; j<possible_words[i].size(); j++){
			for(unsigned int k=0; k<all_letters.size(); k++){
				for(unsigned int l=0; l<disallowed.size(); l++){
					if(possible_words[i][j]!=disallowed[l] && possible_words[i][j]==all_letters[k]) quantified_letter_frequency[k].second++;
				}
			}
		}
	}
	vector<int> sort_letters;
	for(unsigned int i=0; i<quantified_letter_frequency.size(); i++){
		sort_letters.push_back(quantified_letter_frequency[i].second);
	}
	sort(sort_letters.begin(),sort_letters.end());
	for(unsigned int i=0; i<sort_letters.size(); i++){
		for(unsigned int j=0; j<quantified_letter_frequency.size(); j++){
			if(sort_letters[i]==quantified_letter_frequency[j].second){
				letter_frequency.push_back(quantified_letter_frequency[j].first);
				quantified_letter_frequency.erase(quantified_letter_frequency.begin()+j);
				break;
			}
		}
	}
	reverse(letter_frequency.begin(),letter_frequency.end());
	letter_frequency.erase(letter_frequency.begin()+26,letter_frequency.end());
	//cout<<"\n"<<letter_frequency<<"\n";
	return letter_frequency;
}

char guess(vector<char> correct_letters, vector<char> incorrect_letters, const vector<char> letter_frequency){//Picks a letter to guess from letter frequency
	vector<char> remaining_letters;
	vector<int> remove_from_remaining;
	remaining_letters=letter_frequency;
	char guess_letter;
	for(unsigned int i=0; i<letter_frequency.size(); i++){//Fills remaining_letters with the remaining possible letters
		for(unsigned int j=0; j<correct_letters.size(); j++){
			if(letter_frequency[i]==correct_letters[j]) remove_from_remaining.push_back(j);
		}
		for(unsigned int j=0; j<incorrect_letters.size(); j++){
			if(letter_frequency[i]==incorrect_letters[j])remove_from_remaining.push_back(j);
		}
	}
	for(unsigned int i=remove_from_remaining.size(); i>0; i--){
		remaining_letters.erase(remaining_letters.begin()+remove_from_remaining[i-1]);		
	}
	guess_letter=remaining_letters[0];
	return guess_letter;
}

string fill_word(unsigned int word_length){
	string word;
	for(unsigned int i=0; i<word_length; i++){
		word+="_";
	}
	return word;
}

string print_word(string word){
	string printout;
	for(unsigned int i=0; i<word.length();i++){
		printout+=word[i];
		if(i<word.length()-1) printout+=" ";
	}
	return printout;
}

void function(string& word, vector<char>& correct_letters, char& letter_guess, bool& finish){
	char temp[10];
	int letter_place=0;
	cout<<"What place is it in the word? ";
	cin>>temp;
	letter_place=atoi(temp);
	word[letter_place-1]=letter_guess;
	for(unsigned int j=0; j<word.size(); j++){
		if(word[j]=='_') break;
		else if(j==word.size()-1){
			cout<<"\nI WIN!";
			finish=1;
		}
	}
	correct_letters.push_back(letter_guess);
}

int main(){
	bool smart_guess=1;
	unsigned int word_length=0;
	string word="";
	bool finish=0;
	vector<char> correct_letters;
	vector<char> incorrect_letters;
	char letter_guess;
	char yn='n';
	cout<<"Enter the number of letters in the word: ";
	cin>>word_length;
	cout<<"Use smart guess?(y/n) ";
	cin>>yn;
	smart_guess=yn=='y';
	vector<char> letter_frequency={'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};
	word=fill_word(word_length);
	if(smart_guess)letter_frequency=set_smart_letter_frequency(word);
	for(unsigned int i; i<26; i++){
		yn='n';
		letter_guess=guess(correct_letters, incorrect_letters, letter_frequency);
		cout<<"Known: "<<print_word(word)<<". Does it have the letter \'"<<letter_guess<<"\'?(y/n) ";
		cin>>yn;
		while(yn=='y' && !finish){
			function(word,correct_letters,letter_guess,finish);
			if(finish) break;
			cout<<"Is there another instance of the letter?(y/n) ";
			cin>>yn;
		}
		if(yn!='y' && !finish){
			incorrect_letters.push_back(letter_guess);
			if(incorrect_letters.size()==6){
				cout<<"\nI LOSE!";
				string temp;
				cout<<"\nWhat was the word? ";
				cin>>temp;
				finish=1;
			}
		}
		if(finish)break;
	}
	return 0;
}