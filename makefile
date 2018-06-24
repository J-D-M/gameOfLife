CC     = clang++
LFLAGS = -lSDL2
CFLAGS = -Wall -std=c++17 -O3
SRCDIR = ./src
BINDIR = ./bin
DEPS   = $(SRCDIR)/wrappers.cpp $(SRCDIR)/world.cpp
OBJ    = $(SRCDIR)/main.cpp
ONAME  = gameOfLife

default: $(OBJ) $(DEPS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $(BINDIR)/$(ONAME)
