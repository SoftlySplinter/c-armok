CC=gcc
CFLAGS=-Wall

all: compile

compile:
	echo "${CC} ${CFLAGS} -o ${BIN} "

test: compile
	echo "Test"
