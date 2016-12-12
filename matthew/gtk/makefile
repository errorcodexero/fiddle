all: gtktest

gtktest: gtktest.cpp
	 g++ `pkg-config --cflags gtk+-3.0` -o gtktest gtktest.cpp `pkg-config --libs gtk+-3.0`

.PHONY: clean
clean:
	rm gtktest
