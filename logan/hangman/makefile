all: hangman_solver hangman

hangman_solver: hangman_solver.cpp
	g++ hangman_solver.cpp -std=c++11 -Wall -Wextra -Werror -o "hangman_solver"

hangman: hangman.cpp
	g++ hangman.cpp -std=c++11 -Wall -Wextra -Werror -o "hangman"

.PHONY: clean
clean: 
	rm -rf hangman_solver; rm -rf hangman; rm -rf hangman_solver_new;
