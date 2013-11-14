CC=clang
CFLAGS=-std=c99 -g -Wall

OUT=bin/
SRC=src/

all: compile

compile: armok
	mv bin/armok armok

armok: interpreter parser syntax
	${CC} ${CFLAGS} -o ${OUT}/armok ${SRC}/main.c ${OUT}/run.o ${OUT}/parse.o ${OUT}/syntax.o

interpreter: parser syntax
	${CC} ${CFLAGS} -c -o ${OUT}/run.o ${SRC}/run.c

parser: syntax
	${CC} ${CFLAGS} -c -o ${OUT}/parse.o ${SRC}/parse.c

syntax:
	${CC} ${CFLAGS} -c -o ${OUT}/syntax.o ${SRC}/syntax.c

clean:
	rm bin/*.o armok
