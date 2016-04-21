#include "hangman.h"

#ifdef HANGMAN_TEST

int main(){
	std::cout<<"Playing hangman:\n";
	Game game;
	Solver solver(game.length());
	while(!game.done()){
		char guess=solver.get_guess();
		std::cout<<draw_gallows(ATTEMPTS-game.remaining())<<"\nKnown: "<<game.print_word()<<". Guessing letter '"<<guess<<"'.\n";
		bool right=game.check(guess);
		if(right){
			solver.right(guess);
			std::vector<unsigned int> locs;
			for(unsigned int i=0;i<game.print.length(); i++){
				char c=game.print[i];
				if(c==' ')continue;
				if(c==guess) locs.push_back(i);
			}
			solver.fill(locs,guess);
			std::cout<<"\nCorrect, the letter "<<guess<<" is present in the word.\n";
		}
		else{
			solver.wrong(guess);
			std::cout<<"\nWrong: there are no letter "<<guess<<"'s in the word.\n";
		}
		if(game.done()){
			std::cout<<draw_gallows(ATTEMPTS-game.remaining())<<"\n";
			if(right) std::cout<<"\nYou win! The word was \""<<game.print_word()<<"\"!\n";
			else std::cout<<"\nYou lost. The word was "<<game.print_word()<<"\n";
		}
	}
	if(game.remaining()==0) log(false,game.print_word(),__FILE__);
	else log(true,game.print_word(),__FILE__);
	return 0;
}

#endif
