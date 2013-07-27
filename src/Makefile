CC=clang++

.if !empty (OSTYPE:Mlinux*) || defined (FORCE_CC)
  CC=g++
.endif

OFLAG=-O3
CPUFLAGS=-march=corei7 -mssse3 -msse4.1 
OPTFLAGS=$(OFLAG) -funroll-loops -fno-strict-aliasing -ffast-math -fstack-protector
WARNFLAGS=-Wall -pedantic-errors
LIBFLAGS=

CFLAGS=$(CPUFLAGS) $(WARNFLAGS) $(LIBFLAGS) $(OPTFLAGS)

engine: player board
	$(CC) $(CFLAGS) -c engine.cpp

player:
	$(CC) $(CFLAGS) -c player.cpp

board:
	$(CC) $(CFLAGS) -c board.cpp

clean:
	rm -rf ./*.o
