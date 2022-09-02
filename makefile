CXX=g++
OPT="-Wno-terminate -lfmt"
target=all

all: compile

compile:
	cd include&&make CXX=$(CXX) OPT=$(OPT) $(target)

clear:
	rm -f bin/* lib/*
