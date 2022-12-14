# Compiler options
CC       = gcc
INC     += -I. -I./include -I/usr/include
CFLAGS  += -g -W -Wall -Werror -std=c99 -pedantic -Wno-unused-result ${INC}
CPPFLAGS =\
	-D_POSIX_C_SOURCE=200809L
LDFLAGS = -lm
