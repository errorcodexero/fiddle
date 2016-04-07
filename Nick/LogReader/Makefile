all:
	g++  src/logReader.cpp src/utils/math.cpp src/utils/csvParser.cpp -I include/ -o logReader.out -std=c++11 -Wall -pg
debug:
	g++  src/logReader.cpp src/utils/math.cpp src/utils/csvParser.cpp -I include/ -o logReader.out -std=c++11 -DDEBUG -pg 
test:
	g++  src/logReader.cpp src/utils/math.cpp src/utils/csvParser.cpp -I include/ -o logReader.out -std=c++11 -DTEST -pg
	yes no | ./logReader.out
