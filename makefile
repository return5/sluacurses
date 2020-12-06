OPTIONS = -Wall -Wextra -shared -fPIC -llua5.4 -o 
LIBFLAGS = -I/usr/include/lua5.4 
OUTPUT   = sluacurses.so
SRC      = sluacurses.c
CC       = gcc

all:
	$(CC) $(OPTIONS)$(OUTPUT) $(LIBFLAGS) $(SRC)
