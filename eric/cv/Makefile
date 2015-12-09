CXX=g++
CXX_FLAGS=-std=c++11 -Wall -Wextra -ggdb `pkg-config --cflags opencv`
CXX_LIBS=`pkg-config --libs opencv`
SOURCES=hello.cpp
EXECUTABLE=$(SOURCES:.cpp=)

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)

.cpp:
	$(CXX) $(CXX_FLAGS) $< -o $@ $(CXX_LIBS) 

.PHONY: clean

clean:
	rm -f ex *.o
