CC=gcc
CFLAGS=-std=c99 -g -Wall

all: compile

compile: bin/armok

bin/armok: bin/run.o bin/parse.o
	${CC} ${CFLAGS} -o bin/armok src/main.c bin/run.o bin/parse.o

bin/run.o: bin/parse.o
	${CC} ${CFLAGS} -c -o bin/run.o src/run.c

bin/parse.o:
	${CC} ${CFLAGS} -c -o bin/parse.o src/parse.c

test: compile
	rm -f bin/armok bin/run.o bin/parse.o
