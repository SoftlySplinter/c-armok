CC=clang
CFLAGS=-std=c99 -g -Wall

OUT=bin/
SRC=src/

all: compile

compile: armok
	mv bin/armok armok

armok: interpreter parser
	${CC} ${CFLAGS} -o ${OUT}/armok ${SRC}/main.c ${OUT}/run.o ${OUT}/parse.o

interpreter: parser
	${CC} ${CFLAGS} -c -o ${OUT}/run.o ${SRC}/run.c

parser:
	${CC} ${CFLAGS} -c -o ${OUT}/parse.o ${SRC}/parse.c

clean:
	rm bin/*.o armok
