CXX=clang++

.if !empty (OSTYPE:Mlinux*) || defined (FORCE_CC)
  CXX=g++
.endif

OFLAG=-O3
CPUFLAGS=-march=corei7 -mssse3 -msse4.1 
OPTFLAGS=$(OFLAG) -funroll-loops -fno-strict-aliasing -ffast-math -fstack-protector
WARNFLAGS=-Wall -pedantic-errors
LIBFLAGS=

CXXFLAGS=$(CPUFLAGS) $(WARNFLAGS) $(LIBFLAGS) $(OPTFLAGS)

engine: player board
	$(CXX) $(CXXFLAGS) -c engine.cpp

player:
	$(CXX) $(CXXFLAGS) -c player.cpp

board:
	$(CXX) $(CXXFLAGS) -c board.cpp

clean:
	rm -rf ./*.o
