all:
	g++  logReader.cpp -I include/ -o logReader.out -std=c++11 -Wall
debug:
	g++  logReader.cpp -I include/ -o logReader.out -std=c++11 -DDEBUG
test:
	g++  logReader.cpp -I include/ -o logReader.out -std=c++11 -DTEST
	yes no | ./logReader.out
