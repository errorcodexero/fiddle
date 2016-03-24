all: hangman_solver hangman hangman_test

hangman_solver: hangman_solver.cpp hangman.cpp
	g++ -std=c++11 -DHANGMAN_SOLVER -Wall -Wextra -Werror hangman_solver.cpp hangman.cpp -o "hangman_solver"

hangman: hangman.cpp hangman_solver.cpp
	g++ -std=c++11 -DHANGMAN_GAME -Wall -Wextra -Werror hangman.cpp hangman_solver.cpp -o "hangman"

hangman_test: hangman_test.cpp hangman.cpp hangman_solver.cpp
	g++ -std=c++11 -DHANGMAN_TEST -Wall -Wextra -Werror hangman_test.cpp hangman.cpp hangman_solver.cpp -o "hangman_test"

.PHONY: clean
clean: 
	rm -rf hangman_solver; rm -rf hangman; rm -rf hangman_test;
