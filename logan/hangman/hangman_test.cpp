#include "hangman_solver.h"

#ifdef HANGMAN_TEST

int main(){
	std::cout<<"Playing hangman:";
	std::string word=get_word();
	Game game(word.length());
	while(!game.found() && !game.failed()){
		std::string blanks=get_blanks(word);
		play_game(word, blanks);
	}
	return 0;
}

#endif
