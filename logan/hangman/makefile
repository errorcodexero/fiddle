all: hangman_solver hangman hangman_test

hangman_solver: hangman_solver.cpp
	g++ hangman_solver.cpp -std=c++11 -DHANGMAN_SOLVER -Wall -Wextra -Werror -o "hangman_solver"

hangman: hangman.cpp
	g++ hangman.cpp hangman_solver.cpp -std=c++11 -DHANGMAN_GAME -Wall -Wextra -Werror -o "hangman"

hangman_test: hangman_test.cpp
	g++ hangman_test.cpp hangman.cpp hangman_solver.cpp -std=c++11 -DHANGMAN_TEST -Wall -Wextra -Werror -o "hangman_test"

.PHONY: clean
clean: 
	rm -rf hangman_solver; rm -rf hangman; rm -rf hangman_test;
