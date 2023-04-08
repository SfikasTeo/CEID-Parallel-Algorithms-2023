SHELL:= /bin/bash

CXX := g++
CXXFLAGS?= -O3 -Wall -std=c++11 -lstdc++ -fopenmp

ifeq ($(debug), 1)
	CXXFLAGS+=-DDEBUG
endif

all: packetRouting

packetRouting: packetRouting.cpp
	$(CXX) $(CXXFLAGS) -o  $@ $<

clean:
	rm -f packetRouting *.txt