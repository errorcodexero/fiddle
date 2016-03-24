#include "hangman.h"

Game::Game():incorrect({}),correct({'\''}){
	word=get_word();
	print=[&]{
		std::string s;
		for(char c:word){
			if(c=='\'') s+="'";
			else s+=" ";
		}
		return s;
	}();
}

Game::Game(Word w):incorrect({}),correct({'\''}){
	word=w;
	print=[&]{
		std::string s;
		for(char c:word){
			if(c=='\'') s+="' ";
			else s+=" ";
		}
		return s;
	}();
}

std::string draw_gallows(unsigned int incorrect){//Draws the gallows with the appropriate amount of body parts. 
	std::string gallows;
	switch(incorrect){
		case 0:
			gallows="      _______\n     |/       \n     |         \n     |          \n     |        \n     |          \n     |\n  ___|___\n";//Empty Gallows
			break;
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
		case 6:
			gallows="      _______\n     |/      |\n     |      (_)\n     |      \\|/\n     |       |\n     |      / \\\n     |\n  ___|___\n";//Right leg
			break;
		default:
			assert(incorrect<=ATTEMPTS);
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

void Game::wrong(char c){
	incorrect.push_back(c);
}

void Game::right(char c){
	correct.push_back(c);
	print=[&]{
		std::string n;
		for(unsigned int i=0;i<word.length();i++){
			bool known=false;
			for(char d:correct){
				if(d==word[i]){
					known=true;
					break;
				}
			}
			if(known) n+=word[i];
			else n+=' ';
		}
		return n;
	}();
}

bool Game::check(char guess){
	bool in_word=false;
	for(char c:word){
		if(std::tolower(guess)==std::tolower(c)){
			right(guess);
			in_word=true;
			break;
		}
	}
	if(!in_word) wrong(guess);
	return in_word;
}

std::string Game::print_word(){
	if(done()) return word;
	std::string to_print;
	for(char c:print){
		if(c==' ')c='_';
		to_print+=c;
		to_print+=' ';
	}
	return to_print;
}

unsigned int Game::length(){
	return word.length();
}

unsigned int Game::remaining(){
	return (ATTEMPTS-incorrect.size());
}

void Game::operator()(){
	char guess;
	{
		std::vector<char> guessed=incorrect;
		for(char c: correct){
			if(c!='\'') guessed.push_back(c);
		}
		std::cout<<draw_gallows(ATTEMPTS-remaining())<<"\nKnown: "<<print_word()<<" You have already guessed: "<<guessed<<" What is your guess? ";
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
	if(done()){
		std::cout<<draw_gallows(ATTEMPTS-remaining())<<"\n";
		if(right) std::cout<<"\nYou win! The word was \""<<print_word()<<"\"!\n";
		else std::cout<<"\nYou lost. The word was "<<print_word()<<"\n";
	}
}

bool Game::done(){
	if(remaining()==0) return true;
	for(char c:print){
		if(c==' ')return false;
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
	if(game.remaining()==0) log(false,game.print_word(),__FILE__);
	else log(true,game.print_word(),__FILE__);
	std::cout<<"\nThanks for playing!\n";
	return 0;
}

#endif
