all: test log_reader
	./logger

test: test.cpp logger.cpp
	g++ test.cpp logger.cpp -o "logger"

log_reader: reader.cpp
	g++ reader.cpp -o "reader"

.PHONY: clean
clean:
	rm -rf logger;
	rm -rf reader;
