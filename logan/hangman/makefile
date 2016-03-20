all: 
	make hangman_solver; make hangman; make hangman_solver_new;

hangman_solver: hangman_solver.cpp
	g++ hangman_solver.cpp -std=c++11 -Wall -Wextra -Werror -o "hangman_solver"

hangman: hangman.cpp
	g++ hangman.cpp -std=c++11 -Wall -Wextra -Werror -o "hangman"

hangman_solver_new: hangman_solver_new.cpp
	g++ hangman_solver_new.cpp -std=c++11 -Wall -Wextra -Werror -o "hangman_solver_new"

.PHONY: clean
clean: 
	rm -rf hangman_solver; rm -rf hangman; rm -rf hangman_solver_new;
