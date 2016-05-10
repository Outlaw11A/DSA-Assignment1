CC = g++
prog: main.o Euro.o ListUtil.o
	$(CC) main.o Euro.o ListUtil.o -o program
main.o: main.cpp Euro.h ListUtil.h
	$(CC) -c main.cpp
Euro.o: Euro.h Euro.cpp
	$(CC) -c Euro.cpp
ListUtil.o: ListUtil.h ListUtil.cpp
	$(CC) -c ListUtil.cpp
