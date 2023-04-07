SHELL:= /bin/bash

CXX := g++
CXXFLAGS?= -O3 -Wall -std=c++11 -lstdc++ -fopenmp

ifeq ($(debug), 1)
	CXXFLAGS+=-DDEBUG
endif

all: packageRouting

packageRouting: packageRouting.cpp
	$(CXX) $(CXXFLAGS) -o  $@ $<

clean:
	rm -f packageRouting *.txt