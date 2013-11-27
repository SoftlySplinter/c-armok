SHELL=/bin/sh

CFLAGS=-std=c99 -g

OUT=bin
SRC=src

exec_prefix=/usr/local
bindir=${exec_prefix}/bin

all: compile

compile: armok ${OUT}

debug: CFLAGS = -std=c99 -DDEBUG=0 -g
debug: compile

armok: ${OUT} interpreter parser syntax encode
	${CC} ${CFLAGS} -o ${OUT}/armok ${SRC}/main.c ${OUT}/run.o ${OUT}/parse.o ${OUT}/syntax.o ${OUT}/encode.o

${OUT}:
	mkdir ${OUT}

interpreter: parser syntax
	${CC} ${CFLAGS} -c -o ${OUT}/run.o ${SRC}/run.c

parser: syntax
	${CC} ${CFLAGS} -c -o ${OUT}/parse.o ${SRC}/parse.c

syntax:
	${CC} ${CFLAGS} -c -o ${OUT}/syntax.o ${SRC}/syntax.c

encode:
	${CC} ${CFLAGS} -c -o ${OUT}/encode.o ${SRC}/encode.c

install:
	cp ${OUT}/armok ${bindir}/armok

installdirs: ${bindir} ${OUT}

uninstall:
	rm ${bindir}/armok

clean:
	rm ${OUT}/*.o
	rm ${OUT}/armok
	rmdir ${OUT}
