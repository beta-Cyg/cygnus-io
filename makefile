CXX=g++
OPT=-std=c++20 -Wno-terminate -lfmt

all: compile

compile:
	$(CXX) $(OPT) test/test.cpp -o bin/test.out

clean:
	rm -f bin/* lib/*
