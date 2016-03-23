#include "hangman.h"

#include <ctime>
#include <cstdlib>
#include <sstream>
#include <ctype.h>

using namespace std;

unsigned int remaining_attempts=ATTEMPTS;//Variable for how many guesses the user is allowed (see line 113, this must be equal to the number at left-- however, if you change this you will
//need to change the draw_gallows function.

Game::Game():incorrect({}),correct({}){
	word=get_word();
}

Game::Game(Word w):word(w),incorrect({}),correct({}){}

std::string draw_gallows(unsigned int incorrect){//Draws the gallows with the appropriate amount of body parts. 
	std::string gallows="      _______\n     |/       \n     |         \n     |          \n     |        \n     |          \n     |\n  ___|___\n";//Empty Gallows
	switch(incorrect){
		case 1:
			gallows="      _______\n     |/      |\n     |      (_)\n     |          \n     |        \n     |          \n     |\n  ___|___\n";//Head
			break;
		case 2:
			gallows="      _______\n     |/      |\n     |      (_)\n     |       |  \n     |       |\n     |          \n     |\n  ___|___\n";//Torso
			break;
		case 3:
			gallows="      _______\n     |/      |\n     |      (_)\n     |      \\| \n     |       |\n     |          \n     |\n  ___|___\n";//Left arm
			break;
		case 4:
			gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |          \n     |\n  ___|___\n";//Right arm 
			break;
		case 5:
			gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      / \n     |\n  ___|___\n";//Left leg
			break;
		default:
			gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      / \\\n     |\n  ___|___\n";//Right leg
			break;
	}
	return gallows;
}

string get_word(){//Chooses the word
	ifstream chooseword;
	string word;
	srand(time(NULL));
	int random=(rand() % 99171)+1;
	if(random==1)random=2;
	int f=0;
	chooseword.open(FILENAME);
	while(!chooseword.eof()){
		if(f==random){
			break;
		}	
		else{
			while(f!=random){
				chooseword >> word;
				f++;
			}
		}
	}
	chooseword.close();
	return word;
}

struct Comparison_return{//A type that returns the necessary values from a function
	unsigned int remaining_attempts;
	string blanks;
};

Comparison_return guess_v_word_comparison(string guess, string word, string blanks){
	Comparison_return comparison_return;
	vector<string> use_an_an{"a", "e", "f", "h", "i", "l", "m", "n", "o", "r", "s", "x"};//Used to determine if the program should say "a" or "an" before the letter
	bool correct=0;
	bool use_an_an_confirmed=0;
	for(unsigned int i=0; i<word.length(); i++){//Determines if the guess was right or wrong--checks the lower case form
		if(tolower(guess[0])==word[i]){
			blanks[i*2]=tolower(guess[0]);
			correct=1;
		}
	}
	for(unsigned int i=0; i<word.length(); i++){//Determines if the guess was right or wrong--checks the capital form
		if(toupper(guess[0])==word[i]){
			blanks[i*2]=toupper(guess[0]);
			correct=1;
		}
	}
	if(correct==0){
		cout<<"Incorrect guess. There are no "<<guess[0]<<"\'s in the word.\n";
		remaining_attempts--;
	}
	else{
		for(unsigned int t=0; t<use_an_an.size(); t++){
			if(guess==use_an_an[t]){
				cout<<"Correct guess! There is an "<<guess[0]<<" in the word!\n";
				use_an_an_confirmed=1;
				break;
			}
		}
		if(use_an_an_confirmed==0){
			cout<<"Correct guess! There is a "<<guess[0]<<" in the word!\n";
		}
	}
	comparison_return.remaining_attempts=remaining_attempts;
	comparison_return.blanks=blanks;
	return comparison_return;
}

string get_blanks(string word){
	string blanks;
	for(unsigned int i=0; i<word.length(); i++){//Creates a string with the correct number of blanks for the user to try to guess the word
		blanks+="_ ";
	}
	for(unsigned int i=0; i<word.length(); i++){//Inserts an apostrophe where it belongs
		if(word[i]=='\'')blanks[i*2]='\'';
	}
	return blanks;	
}

void play_game(string word, string blanks){//Accepts user guesses and compares them with the word
	Comparison_return comparison_return;
	string guess, previous_guesses;
	remaining_attempts=6;
	while(true){
		bool repeated_guess=0;
		bool victory=0;
		cout<<"\n"<<blanks<<"\n\n";
		if(previous_guesses.size()==0){
			cout<<draw_gallows(remaining_attempts);
			cout<<"You have "<<remaining_attempts<<" attempts remaining. Please guess a character: ";//Prompts user for a guess when there are no previous guesses
			cin>>guess;
		}
		else{
			cout<<draw_gallows(remaining_attempts);
			cout<<"You have "<<remaining_attempts<<" attempts remaining. You have already guessed:"<<previous_guesses<<". Please guess a character: ";//Prompts user for a guess
			cin>>guess;
		}
		cout<<"\n";
		for(unsigned int i=0; i<previous_guesses.size(); i++){//Determines if the guess has already been guessed
			if(previous_guesses.size()%2==0){
				if(previous_guesses.size()>(i*2)-1){
					if(guess[0]==previous_guesses[(i*2)-1]){
						cout<<"You have already guessed "<<guess[0]<<".\n";
						repeated_guess=1;
						break;
					}
				}
				else{
					if(guess[0]==previous_guesses[1]){
						cout<<"You have already guessed "<<guess[0]<<".\n";
						repeated_guess=1;
						break;
					}
				}
			}
		}
		if(repeated_guess==0){//Adds guess to the previous-guessed list
			previous_guesses.append(" "+guess);
			comparison_return=guess_v_word_comparison(guess, word, blanks);
			remaining_attempts=comparison_return.remaining_attempts;
			blanks=comparison_return.blanks;
		}
		if(remaining_attempts==0){//Determines is the user has lost
			cout<<draw_gallows(remaining_attempts);
			cout<<"=========================================================================="<<"\n\nGame over. You lose. The correct word ";
			cout<<"was: \""<<word<<"\n\n==========================================================================\n";
			break;
		}
		for(unsigned int k=0; k<blanks.size(); k++){//Determines is the user has won
			if(blanks[k]=='_'){
				break;
			}
			else{
				if(k==blanks.size()-1)victory=1;
			}
		}
		if(victory==1){
			cout<<draw_gallows(remaining_attempts);
			cout<<"=========================================================================="<<"\n\nCongratulations! You win! the word";
			cout<<" was \""<<word<<"\n\n==========================================================================\n";
			break;
		}
	}
}

string print_instructions(){
	string s="On the screen there will appear a word written with blanks in the place of each letter. You will then guess a letter. If that letter is in ";
	s+="the word then I will write\nthe letter in every place it appears in the word. If the letter isn't in the word then I will add a head," ;
	s+=" torso, left arm, right arm, left leg, or right leg to the\n";
	s+="gallows. The word may contain accented letters (in which case you're basically screwed) as well as apostrophes (these will be shown, however).";
	s+=" If you want to guess a\nword, just type the letters with space in-between them.";
	s+="\n\nThe game will continue until either the full body is hanging from the gallows (I win) or if you guess the correct word before ";
	s+="the person is hung (you win).";	
	return s;
}

#ifdef HANGMAN_GAME

int main(){
	char play='n';
	cout<<"Would you like to play a game of hangman?(y/n): ";
	cin>>play;
	if(play=='y'){
		char instructions;
		cout<<"\nWould you like to read the instructions?(y/n): ";
		cin>>instructions;
		cout<<"\n";
		if(instructions=='y'){//Instructions
			cout<<print_instructions();
			cout<<"Would you still like to play a game of hangman?(y/n): ";
			cin>>play;
			cout<<"\n";
		}
	}
	while(play=='y'){
		cout<<"Let's play!\n";
		string word=get_word();
		string blanks=get_blanks(word);
		play_game(word, blanks);
		cout<<"\nWould you like to play another game of hangman?(y/n): ";
		cin>>play;
	}
	cout<<"\nThanks for playing!\n";
	return 0;
}

#endif