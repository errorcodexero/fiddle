/*
 • Project: A hangman game program.
 • Author(s): Logan Traffas.
 • Description: A program that will randomly select a word that you will try to guess before a man is hanged.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <windows.h>
#include <sstream>
#include <ctype.h>
using namespace std;

unsigned int remaining_attempts=6;//Variable for how many guesses the user is allowed (see line 113, this must be equal to the number at left-- however, if you change this you will
//need to change the draw_gallows function.

void draw_gallows(unsigned int remaining_attempts){//Draws the gallows with the appropriate amount of body parts. 
	cout<<endl;
	string gallows;
	if(remaining_attempts==6){
		gallows="      _______\n     |/       \n     |         \n     |          \n     |        \n     |          \n     |\n  ___|___\n";//Empty Gallows
	}
	else if(remaining_attempts==5){
		gallows="      _______\n     |/      |\n     |      (_)\n     |          \n     |        \n     |          \n     |\n  ___|___\n";//Head
	}
	else if(remaining_attempts==4){
		gallows="      _______\n     |/      |\n     |      (_)\n     |       |  \n     |       |\n     |          \n     |\n  ___|___\n";//Torso
	}
	else if(remaining_attempts==3){
		gallows="      _______\n     |/      |\n     |      (_)\n     |      \\| \n     |       |\n     |          \n     |\n  ___|___\n";//Left arm
	}
	else if(remaining_attempts==2){
		gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |          \n     |\n  ___|___\n";//Right arm 
	}
	else if(remaining_attempts==1){
		gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      / \n     |\n  ___|___\n";//Left leg
	}
	else if(remaining_attempts==0){
		gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      / \\\n     |\n  ___|___\n";//Right leg
	}
	cout<<gallows<<endl;
}

string get_word(){//Chooses the word
	ifstream chooseword;
	string word;
	srand(time(NULL));
	int random=(rand() % 99171)+1;
	if(random==1)random=2;
	int f=0;
	chooseword.open("words.txt");
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

struct Wins_and_losses_return{
	int winnings, loses;
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
		cout<<"Incorrect guess. There are no "<<guess[0]<<"\'s in the word."<<endl;
		remaining_attempts--;
	}
	else{
		for(unsigned int t=0; t<use_an_an.size(); t++){
			if(guess==use_an_an[t]){
				cout<<"Correct guess! There is an "<<guess[0]<<" in the word!"<<endl;
				use_an_an_confirmed=1;
				break;
			}
		}
		if(use_an_an_confirmed==0){
			cout<<"Correct guess! There is a "<<guess[0]<<" in the word!"<<endl;
		}
	}
	comparison_return.remaining_attempts=remaining_attempts;
	comparison_return.blanks=blanks;
	return comparison_return;
}

void reset_saved_statistics(){//Resets win and loss statistics
	Sleep(750);
	cout<<endl<<endl<<"Resetting saved win and loss statistics to 0's."<<flush;
	Sleep(750);
	cout<<" ."<<flush;
	Sleep(750);
	cout<<" ."<<flush;
	Sleep(750);
	cout<<" ."<<flush;
	ofstream logger;
	logger.open("hangman_log.txt");
	logger<<"W:"<<0<<",L-"<<0<<",";
	logger.close();
	Sleep(750);
	cout<<" done!"<<endl<<endl;
	Sleep(100);
}

Wins_and_losses_return win_and_loss_saver(int won, int lost){
	string wins, losses, line;
	int winnings, loses;
	ifstream log;
	log.open("hangman_log.txt");
	getline(log, line);
	stringstream input;
	input.str("");
	for(unsigned int i=0; i<line.size(); i++){
		if(line[i]==':'){	
			unsigned int t=i+1;
			while(line[t]!=','){
				wins+=(line[t]);
				t++;
			}
			stringstream input (wins);
			if(!(input>>winnings)){
				winnings=won;
			}
		}
		else if(line[i]=='-'){
			unsigned int t=i+1;
			while(line[t]!=','){
				losses+=(line[t]);
				t++;
			}
			stringstream input (losses);
			if(!(input>>loses)){
				loses=lost;
			}
		}
	}
	winnings+=won;
	loses+=lost;
	log.close();
	ofstream logger;
	logger.open("hangman_log.txt");
	logger<<"W:"<<winnings<<",L-"<<loses<<",";
	logger.close();
	Wins_and_losses_return wins_and_losses_return;
	wins_and_losses_return.winnings=winnings;
	wins_and_losses_return.loses=loses;
	return wins_and_losses_return;
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
	int won=0, lost=0;
	Comparison_return comparison_return;
	Wins_and_losses_return wins_and_losses_return;
	string guess, previous_guesses;
	remaining_attempts=6;
	while(true){
		bool repeated_guess=0;
		bool victory=0;
		cout<<endl<<blanks<<endl<<endl;
		if(previous_guesses.size()==0){
			draw_gallows(remaining_attempts);
			cout<<"You have "<<remaining_attempts<<" attempts remaining. Please guess a character: ";//Prompts user for a guess when there are no previous guesses
			cin>>guess;
		}
		else{
			draw_gallows(remaining_attempts);
			cout<<"You have "<<remaining_attempts<<" attempts remaining. You have already guessed:"<<previous_guesses<<". Please guess a character: ";//Prompts user for a guess
			cin>>guess;
		}
		cout<<endl;
		for(unsigned int i=0; i<previous_guesses.size(); i++){//Determines if the guess has already been guessed
			if(previous_guesses.size()%2==0){
				if(previous_guesses.size()>(i*2)-1){
					if(guess[0]==previous_guesses[(i*2)-1]){
						cout<<"You have already guessed "<<guess[0]<<"."<<endl;
						repeated_guess=1;
						break;
					}
				}
				else{
					if(guess[0]==previous_guesses[1]){
						cout<<"You have already guessed "<<guess[0]<<"."<<endl;
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
			lost=1;
			wins_and_losses_return=win_and_loss_saver(won, lost);
			draw_gallows(remaining_attempts);
			cout<<"=========================================================================="<<endl<<endl<<"Game over. You lose. The correct word ";
			cout<<"was: \""<<word<<"\"! You have lost "<<wins_and_losses_return.loses<<" times."<<endl<<endl<<"=========================================================================="<<endl;
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
			won=1;
			wins_and_losses_return=win_and_loss_saver(won, lost);
			draw_gallows(remaining_attempts);
			cout<<"=========================================================================="<<endl<<endl<<"Congratulations! You win! the word";
			cout<<" was \""<<word<<"!\" You have won "<<wins_and_losses_return.winnings<<" times!"<<endl<<endl<<"=========================================================================="<<endl;
			break;
		}
	}
}

int main(){
	char play='n';
	cout<<"Would you like to play a game of hangman?(y/n): ";
	cin>>play;
	if(play=='y'){
		char instructions;
		cout<<endl<<"Would you like to read the instructions?(y/n): ";
		cin>>instructions;
		cout<<endl;
		if(instructions=='y'){//Instructions
			cout<<"On the screen there will appear a word written with blanks in the place of each letter. You will then guess a letter. If that letter is in "; 
			cout<<"the word then I will write"<<endl<<"the letter in every place it appears in the word. If the letter isn't in the word then I will add a head," ;
			cout<<" torso, left arm, right arm, left leg, or right leg to the"<<endl;
			cout<<"gallows. The word may contain accented letters (in which case you're basically screwed) as well as apostrophes (these will be shown, however).";
			cout<<" If you want to guess a"<<endl<<"word, just type the letters with space in-between them.";
			cout<<endl<<endl<<"The game will continue until either the full body is hanging from the gallows (I win) or if you guess the correct word before ";
			cout<<"the person is hung (you win). (When asked"<<endl<<"to play again, press \"r\" to reset win and loss statistics."<<endl<<endl;
			cout<<"Would you still like to play a game of hangman?(y/n): ";
			cin>>play;
			cout<<endl;
		}
	}
	while(play=='y'){
		cout<<"Let's play!"<<endl;
		string word=get_word();
		string blanks=get_blanks(word);
		play_game(word, blanks);
		cout<<endl<<"Would you like to play another game of hangman?(y/n): ";
		cin>>play;
		if(play=='r'){
			reset_saved_statistics();		
		}
	}
	cout<<endl<<"Thanks for playing!"<<endl;
	return 0;
}