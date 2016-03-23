#include "hangman.h"

#include <ctime>
#include <cstdlib>
#include <sstream>
#include <ctype.h>

Game::Game():remaining(ATTEMPTS),incorrect({}),correct({}){
	word=get_word();
}

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

std::string Game::print_known(bool spaces=true){
	std::string s;
	for(unsigned int i=0; i<word.length(); i++) s+='_';
	for(char c:correct){
		for(unsigned int i=0; i<word.length(); i++){
			if(c==word[i]) s[i]=c;
		}	
	}
	if(spaces){
		std::string n;
		for(char c:s){
			n+=c;
			n+=' ';	
		}
		s=n;
	}
	return s;
}

std::string get_word(){//Chooses the word
	std::ifstream chooseword(FILENAME);
	std::string word;
	srand(time(NULL));
	int random=(rand() % 99171)+1;
	if(random==1)random=2;
	int f=0;
	while(!chooseword.eof()){
		if(f==random) break;
		chooseword >> word;
		f++;
	}
	chooseword.close();
	return word;
}

void Game::operator()(){
	char guess;
	std::cout<<draw_gallows(incorrect.size())<<"\nKnown: "<<print_known()<<" What is your guess? ";
	std::cin>>guess;
	std::vector<char> guessed=correct;
	for(char c: incorrect) guessed.push_back(c);
	for(char c:guessed){ 
		if(guess==c){
			std::cout<<"\nYou have already guessed the letter "<<guess<<"\n";
			break;
		}
	}
	bool right=false;
	for(char c:word){
		if(guess==c){
			correct.push_back(guess);
			right=true;
		}
	}
	if(!right) incorrect.push_back(guess);
}

bool Game::done(){
	if(print_known(true)==word) return true;
	return remaining==0;
}

std::string print_instructions(){
	std::string s="\nOn the screen there will appear a word written with blanks in the place of each letter. You will then guess a letter. If that letter is in ";
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
	std::cout<<"Let's play a game of hangman!\n";
	char instructions;
	std::cout<<"\nWould you like to read the instructions?(y/n): ";
	std::cin>>instructions;
	if(instructions=='y') std::cout<<print_instructions(); 
	Game game;
	while(!game.done()){
		game();
	}
	std::cout<<"\nThanks for playing!\n";
	return 0;
}

#endif
