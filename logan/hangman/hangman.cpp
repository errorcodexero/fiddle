#include "hangman.h"

Game::Game():remaining(ATTEMPTS),incorrect({}),correct({'\''}){
	word=get_word();
	print=[&]{
		std::string s;
		for(char c:word){
			if(c=='\'') s+="' ";
			else s+="_ ";
		}
		return s;
	}();
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

std::string get_word(){//Chooses the word
	unsigned int len=0;
	{
		std::ifstream get_len(FILENAME);
		while(!get_len.eof()){
			std::string temp;
			len++;
			get_len>>temp;
		}
		get_len.close();
	}
	std::string word;
	{
		std::ifstream chooseword(FILENAME);
		srand(time(NULL));
		int random=(rand() % len)+1;
		if(random==1)random=2;
		int f=0;
		while(!chooseword.eof()){
			if(f==random) break;
			chooseword >> word;
			f++;
		}
		chooseword.close();
	}
	return word;
}

bool Game::check(char guess){
	bool right=false;
	for(char c:word){
		if(guess==c){
			correct.push_back(guess);
			right=true;
			print=[&]{
				std::string n;
				for(unsigned int i=0;i<word.length();i++){
					bool known=false;
					for(char c:correct){
						if(c==word[i]){
							known=true;
							break;
						}
					}
					if(!known) n+="_ ";
					else{
						n+=word[i];
						n+=' ';
					}
				}
				return n;
			}();
			break;
		}
	}
	if(!right){
		incorrect.push_back(guess);
		remaining--;
	}
	return right;
}

void Game::operator()(){
	char guess;
	{
		std::vector<char> guessed=incorrect;
		for(char c: correct){
			if(c!='\'') guessed.push_back(c);
		}
		std::cout<<draw_gallows(incorrect.size())<<"\nKnown: "<<print<<" You have already guessed: "<<"PRINT OUT GUESSED HERE"<<" What is your guess? ";
		std::cin>>guess;
		bool again=true;
		while(again){
			again=false;
			for(char c:guessed){ 
				if(guess==c){
					std::cout<<"\nYou have already guessed the letter \""<<guess<<"\". Guess again: ";
					std::cin>>guess;
					again=true;
					break;
				}
			}
		}
	}
	bool right=check(guess);
	std::cout<<remaining<<"\n";
	if(done()){
		std::cout<<draw_gallows(incorrect.size())<<"\n";
		if(right) std::cout<<"\nI win! The word was \""<<print<<"\"!\n";
		else{
			std::string t;
			std::cout<<"\nI lost. What was the word? ";
			std::cin>>t;
		}
	}
}

bool Game::done(){
	if(remaining==0) return true;
	for(char c:print){
		if(c=='_')return false;
	}
	return true;
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
	{
		std::cout<<"Let's play a game of hangman!\n";
		char instructions;
		std::cout<<"\nWould you like to read the instructions?(y/n): ";
		std::cin>>instructions;
		if(instructions=='y') std::cout<<print_instructions(); 
	}
	Game game;
	while(!game.done()){
		game();
	}
	std::cout<<"\nThanks for playing!\n";
	return 0;
}

#endif
