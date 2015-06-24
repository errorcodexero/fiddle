/*
TODO:
	Must do:
	-If letter frequency is equal, then chose from the master list. (in function order_same_frequency)
	-Check letter case logic
	Later:
	-Stop it from replacing letters (say user says there's "e" in place one then later says there's an "h" in place one)
*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

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

ostream& operator<<(ostream& o, vector<unsigned int> v){
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

ostream& operator<<(ostream& o, vector<pair<char,int>> v){
	o<<"<";
	for(unsigned int i=0; i<v.size(); i++){
		o<<"<";
		o<<v[i].first;
		o<<" ";
		o<<v[i].second;
		o<<"> ";
	}
	o<<">";
	return o;
}

bool check_redundancy(vector<unsigned int> remove_at, unsigned int i){
	for(unsigned int k=0; k<remove_at.size(); k++){
		if(remove_at[k]==i)return 0;
	}
	return 1;
}

vector<string> remove_nonmatching(const string word, vector<string> possible_words, vector<char> incorrect_letters){
	for(unsigned int i=0; i<incorrect_letters.size(); i++){//Removes words containing incorrect letters
		vector<unsigned int> remove_at;
		for(unsigned int j=0; j<possible_words.size(); j++){
			for(unsigned int k=0; k<possible_words[j].size(); k++){
				if(tolower(possible_words[j][k])==incorrect_letters[i] || toupper(possible_words[j][k])==incorrect_letters[i]){
					if(check_redundancy(remove_at, j))remove_at.push_back(j);
					break;
				}
			}
		}
		for(unsigned int i=remove_at.size(); i>0; i--){
			//if(possible_words.size()==0 || possible_words.size()<remove_at[i-1])break;
			possible_words.erase(possible_words.begin()+remove_at[i-1]);
		}
	}
	for(unsigned int k=0; k<word.size(); k++){//Shortens to words with correct letters in the known places
		if(word[k]!='_'){
			possible_words=[&](){
				vector<unsigned int> remove_at;
				for(unsigned int i=0; i<possible_words.size(); i++){
					if(tolower(possible_words[i][k])==word[k] || toupper(possible_words[i][k])==word[k]);
					else if(check_redundancy(remove_at, i))remove_at.push_back(i);
				}
				for(unsigned int i=remove_at.size(); i>0; i--){
					//if(possible_words.size()==0 || possible_words.size()<remove_at[i-1])break;
					possible_words.erase(possible_words.begin()+remove_at[i-1]);
				}
				return possible_words;
			}();
		}
	}
	return possible_words;
}

vector<string> get_possible_words(string word, unsigned int word_length, vector<char> all_letters, vector<char> incorrect_letters, bool print_diagnostics){//Checks a word list and returns a list of words of length "n"
	fstream input_words;
	input_words.open("words.txt");
	vector<string> possible_words;
	if(print_diagnostics)cout<<"\nget_possible_words{";
	for(unsigned int l=1; !input_words.eof(); l++){
		string possible_word;
		input_words>>possible_word;
		if(possible_word.size()==word_length){
			possible_words.push_back(possible_word);
			for(unsigned int i=0; i<possible_word.size(); i++){
				for(unsigned int j=0; j<all_letters.size(); j++){
					if(tolower(possible_word[i])==all_letters[j])break;
					if(toupper(possible_word[i])==all_letters[j])break;
					if(j==all_letters.size())possible_words.pop_back();
				}
			}
		}
		/*if(print_diagnostics){
			cout<<"\nline:"<<l<<"   word:"<<possible_word<<"   size:"<<possible_word.size()<<"   target"<<word_length<<"   vsize:"<<possible_words.size()<<"   vmax:"<<possible_words.max_size();
			if(possible_words.size()!=0)cout<<"   latest:"<<possible_words.back();
		}*/
	}
	input_words.close();
	possible_words=remove_nonmatching(word,possible_words,incorrect_letters);
	if(print_diagnostics)cout<<"\n}\n\npossible_words:"<<possible_words<<"\n";
	return possible_words;
}

void order_same_frequency(vector<char>& /*letter_frequency*/, vector<pair<char, int>> /*quantified_letter_frequency*/){
	vector<char> default_letter_frequency={'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};
}

vector<char> set_smart_letter_frequency(string word, vector<char> incorrect_letters, bool print_diagnostics){//Sets the frequency of letter occurrence in list of words of length "n"
	vector<char> all_letters={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	vector<pair<char,int>> quantified_letter_frequency;
	for(unsigned int i=0; i<all_letters.size(); i++){
		pair<char,int> initialize;
		initialize.first=all_letters[i];
		initialize.second=0;
		quantified_letter_frequency.push_back(initialize);		
	}
	vector<string> possible_words=get_possible_words(word, word.size(), all_letters, incorrect_letters, print_diagnostics);
	if(print_diagnostics)cout<<"\npossible_words:"<<possible_words<<"\n";
	vector<char> letter_frequency;
	if(possible_words.size()==0)letter_frequency={'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};
	else{
		for(unsigned int i=0; i<possible_words.size(); i++){
			for(unsigned int j=0; j<possible_words[i].size(); j++){
				for(unsigned int k=0; k<all_letters.size(); k++){
					if(toupper(possible_words[i][j])==all_letters[k]) quantified_letter_frequency[k].second++;
					else if(tolower(possible_words[i][j])==all_letters[k]) quantified_letter_frequency[k].second++;
				}
			}
		}
		if(print_diagnostics)cout<<"\nquantified_letter_frequency:"<<quantified_letter_frequency<<"\n";
		vector<pair<char, int>> transfer_frequency;
		transfer_frequency=quantified_letter_frequency;
		vector<int> sort_letters;
		for(unsigned int i=0; i<transfer_frequency.size(); i++){
			sort_letters.push_back(transfer_frequency[i].second);
		}
		sort(sort_letters.begin(),sort_letters.end());
		for(unsigned int i=0; i<sort_letters.size(); i++){
			for(unsigned int j=0; j<transfer_frequency.size(); j++){
				if(sort_letters[i]==transfer_frequency[j].second){
					letter_frequency.push_back(transfer_frequency[j].first);
					transfer_frequency.erase(transfer_frequency.begin()+j);
					break;
				}
			}
		}
		reverse(letter_frequency.begin(),letter_frequency.end());
	}
	//order_same_frequency(letter_frequency, quantified_letter_frequency);
	if(print_diagnostics)cout<<"\nletter_frequency:"<<letter_frequency<<"\n";
	return letter_frequency;
}

vector<char> remove_already_guessed(vector<char> remaining_letters, const vector<char> incorrect_letters, const vector<char> correct_letters, bool print_diagnostics){
	vector<int> remove_from_remaining;
	vector<char> already_guessed=incorrect_letters;
	for(unsigned int i=0; i<correct_letters.size(); i++){
		already_guessed.push_back(correct_letters[i]);
	}
	if(print_diagnostics)cout<<"\ncorrect_letters:"<<correct_letters<<"\n\nincorrect_letters:"<<incorrect_letters<<"\n";
	for(unsigned int i=0; i<remaining_letters.size(); i++){//Fills remaining_letters with the remaining possible letters
		for(unsigned int j=0; j<already_guessed.size(); j++){
			//if(print_diagnostics)cout<<"\nfreq:"<<remaining_letters[i]<<"   already:"<<already_guessed[j]<<"    erase:"<<(remaining_letters[i]==already_guessed[j])<<","<<j<<"\n";
			if(remaining_letters[i]==already_guessed[j]) remove_from_remaining.push_back(i);
		}
	}
	sort(remove_from_remaining.begin(), remove_from_remaining.end());
	for(unsigned int i=remove_from_remaining.size(); i>0; i--){
		remaining_letters.erase(remaining_letters.begin()+remove_from_remaining[i-1]);		
	}
	return remaining_letters;	
}

char guess(const vector<char> correct_letters, const vector<char> incorrect_letters, const vector<char> letter_frequency, bool print_diagnostics){//Picks a letter to guess from generic letter frequency
	vector<char> remaining_letters;
	remaining_letters=letter_frequency;
	char guess_letter;
	remaining_letters=remove_already_guessed(remaining_letters, incorrect_letters, correct_letters, print_diagnostics);
	if(print_diagnostics)cout<<"\nremaining_letters:"<<remaining_letters<<"\n\n";
	guess_letter=remaining_letters[0];
	return guess_letter;
}

string fill_word(const unsigned int word_length){
	string word;
	for(unsigned int i=0; i<word_length; i++){
		word+="_";
	}
	return word;
}

string print_word(const string word){
	string printout;
	for(unsigned int i=0; i<word.length();i++){
		printout+=word[i];
		if(i<word.length()-1) printout+=" ";
	}
	return printout;
}

void if_correct_guess(string& word, vector<char>& correct_letters, char& letter_guess, bool& finish){
	char temp[10];
	int letter_place=0;
	cout<<"What place is it in the word? ";
	cin>>temp;
	letter_place=atoi(temp);
	word[letter_place-1]=letter_guess;
	for(unsigned int j=0; j<word.size(); j++){
		if(word[j]=='_') break;
		else if(j==word.size()-1){
			cout<<"\nI WIN! The word is \""<<word<<"\"!\n";
			finish=1;
		}
	}
	correct_letters.push_back(letter_guess);
}

void process_guess_result(string& word, char letter_guess, bool correct, bool& finish, vector<char>& correct_letters, vector<char>& incorrect_letters){
	if(correct){
		char yn='y';
		while(yn=='y' && !finish){
			if_correct_guess(word,correct_letters,letter_guess,finish);
			if(finish) break;
			cout<<"Is there another instance of the letter?(y/n) ";
			cin>>yn;
		}
	}
	else{
		incorrect_letters.push_back(letter_guess);
		if(incorrect_letters.size()==6){
			cout<<"\nI LOSE!";
			string temp;
			cout<<"\nWhat was the word? ";
			cin>>temp;
			finish=1;
		}
	}
}

int main(){
	cout<<"Welcome to this hangman solver! Think of a word and I'll try to guess it, letter by letter.\n\n";
	const bool print_diagnostics=0;
	unsigned int word_length=0;
	cout<<"Enter the number of letters in the word: ";
	cin>>word_length;
	string word="";
	word=fill_word(word_length);
	char yn='n';
	cout<<"Use smart guess?(y/n) ";
	cin>>yn;
	bool smart_guess=0;
	smart_guess=yn=='y';
	vector<char> letter_frequency={'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};
	vector<char> correct_letters;
	vector<char> incorrect_letters;	
	for(unsigned int i=0; i<26; i++){
		if(smart_guess)letter_frequency=set_smart_letter_frequency(word, incorrect_letters, print_diagnostics);
		char letter_guess;
		letter_guess=guess(correct_letters, incorrect_letters, letter_frequency, print_diagnostics);
		yn='n';
		cout<<"Known: "<<print_word(word)<<". Does it have the letter \'"<<letter_guess<<"\'?(y/n) ";
		cin>>yn;
		bool finish=0;
		process_guess_result(word, letter_guess, yn=='y', finish, correct_letters, incorrect_letters);
		if(finish)break;
	}
	return 0;
}