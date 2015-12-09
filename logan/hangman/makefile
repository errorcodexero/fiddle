all: 
	make hangman_solver; make hangman;

hangman_solver: hangman_solver.cpp
	g++ hangman_solver.cpp -std=c++11 -Wall -Wextra -Werror -o "hangman_solver.out"

hangman: hangman.cpp
	g++ hangman.cpp -std=c++11 -Wall -Wextra -Werror -o "hangman.out"

.PHONY: clean
clean: 
	rm -f hangman_solver; rm -f hangman;
