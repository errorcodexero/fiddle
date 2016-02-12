all: test log_reader
	./logger

test: test.cpp logger.cpp
	g++ test.cpp logger.cpp -o "logger"

log_reader: Log_reader.cpp
	g++ Log_reader.cpp -o "reader"

.PHONY: clean
clean:
	rm -rf logger;
	rm -rf reader;
	rm deadTree.csv;
