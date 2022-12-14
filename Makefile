include ./config.mk


SRC = ${wildcard *.c}
OBJ = ${SRC:.c=.o}
BIN = pgm

all: ${BIN}
	@echo all built

clean:
	@rm -rf ${BIN} ${OBJ}

filelib.o: filelib.c
imglib.o: imglib.c
cliente.o: cliente.c

pgm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}
