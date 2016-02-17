all: log_reader

log_reader: tagreader.cpp
	g++ tagreader.cpp -o "CSV_reader" 2>&1 | head

.PHONY: clean
clean:
	rm -rf reader;
