SHELL=/bin/sh

CFLAGS=-std=c99 -g -O2
ALLFLAGS=${CFLAGS} ${LDFLAGS}

OUT=bin
SRC=src
TEST=test

exec_prefix=/usr/local
bindir=${exec_prefix}/bin

all: compile

compile: armok ${OUT}

debug: ALLFLAGS = -DDEBUG=0 ${CFLAGS} ${LDFLAGS}
debug: compile

armok: ${OUT} interpreter parser syntax encode
	${CC} -o ${OUT}/armok ${ALLFLAGS} ${SRC}/main.c ${OUT}/run.o ${OUT}/parse.o ${OUT}/syntax.o ${OUT}/encode.o

${OUT}:
	mkdir ${OUT}

interpreter: parser syntax
	${CC} -c -o ${OUT}/run.o ${ALLFLAGS} ${SRC}/run.c

parser: syntax
	${CC} -c -o ${OUT}/parse.o ${ALLFLAGS} ${SRC}/parse.c

syntax:
	${CC} -c -o ${OUT}/syntax.o ${ALLFLAGS} ${SRC}/syntax.c

encode:
	${CC} -c -o ${OUT}/encode.o ${ALLFLAGS} ${SRC}/encode.c

install:
	cp ${OUT}/armok ${bindir}/armok

installdirs: ${bindir} ${OUT}

uninstall:
	rm ${bindir}/armok

test: compile_tests
	${OUT}/runner.o 2>/dev/null

compile_tests: runner

runner: syntax_tests unit
	${CC} -o ${OUT}/runner.o ${ALLFLAGS} ${TEST}/runner.c ${OUT}/syntax_tests.o ${OUT}/unit.o ${OUT}/syntax.o

syntax_tests:
	${CC} -c -o ${OUT}/syntax_tests.o ${ALLFLAGS} ${TEST}/syntax.c

unit:
	${CC} -c -o ${OUT}/unit.o ${ALLFLAGS} ${TEST}/unit.c

clean:
	rm ${OUT}/*.o
	rm ${OUT}/armok
	rmdir ${OUT}
