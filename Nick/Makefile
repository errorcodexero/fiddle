all:
	g++  logReader.cpp -I include/ -o logReader.out -std=c++11
debug:
	clear
	g++  logReader.cpp -I include/ -o logReader.out -std=c++11 -DDEBUG
test:
	clear
	g++  logReader.cpp -I include/ -o logReader.out -std=c++11 -DTEST
	yes no | ./logReader.out
