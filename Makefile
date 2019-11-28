SOURCES = main.cpp radixsort.cpp mergesort.cpp quicksort.cpp memory.cpp
HEADERS = radixsort.hpp mergesort.hpp quicksort.hpp memory.hpp
CFLAGS = -std=c++11 -Wall -g
OUT = sort

$(OUT): $(SOURCES) $(HEADERS)
	g++ -o $@ $(CFLAGS) $(SOURCES) 
