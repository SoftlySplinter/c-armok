CC=gcc
CFLAGS=-std=c99 -g -Wall

OUT=bin/
SRC=src/

all: compile

compile: armok
	mv bin/armok armok

armok: interpreter parser syntax encode
	${CC} ${CFLAGS} -o ${OUT}/armok ${SRC}/main.c ${OUT}/run.o ${OUT}/parse.o ${OUT}/syntax.o ${OUT}/encode.o

interpreter: parser syntax
	${CC} ${CFLAGS} -c -o ${OUT}/run.o ${SRC}/run.c

parser: syntax
	${CC} ${CFLAGS} -c -o ${OUT}/parse.o ${SRC}/parse.c

syntax:
	${CC} ${CFLAGS} -c -o ${OUT}/syntax.o ${SRC}/syntax.c

encode:
	${CC} ${CFLAGS} -c -o ${OUT}/encode.o ${SRC}/encode.c

clean:
	rm bin/*.o armok
