CC = g++
prog: main.o EuroEnglishConverter.o ListUtil.o
	$(CC) main.o EuroEnglishConverter.o ListUtil.o -o program
main.o: main.cpp EuroEnglishConverter.h ListUtil.h
	$(CC) -c main.cpp
EuroEnglishConverter.o: EuroEnglishConverter.h EuroEnglishConverter.cpp
	$(CC) -c EuroEnglishConverter.cpp
ListUtil.o: ListUtil.h ListUtil.cpp
	$(CC) -c ListUtil.cpp
