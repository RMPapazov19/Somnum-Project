# Include/ dir and obj/ dir
IDIR=include
ODIR=obj

# Compiler options and flags
CXX=g++

# Check if make is being ran on Windows or Unix
ifeq ($(OS),Windows_NT)
	CXXFLAGS=-I$(IDIR) -I$(IDIR)/PDcurses -Llib/
	OUT_EXT=exe
else
	CXXFLAGS=-I$(IDIR) 
	OUT_EXT=out
endif

ERRFLAGS=-O3 -Wall -Wextra -g

# Put header files here
_DEPS=backend.h tui.h
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

# Put cpp files but change extension to .o
_OBJ=main.obj backend.obj tui.obj
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

# Libraries
ifeq ($(OS),Windows_NT)
	LIBS=-l:pdcurses.a
else
	LIBS=-lncurses -lpanel
endif

LIBS+=-lpthread

# Compile .cpp files to .o files
$(ODIR)/%.obj: src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(ERRFLAGS)

# Link .o files and make an executable in bin/ folder
main: $(OBJ)
	$(CXX) -o bin/$@.$(OUT_EXT) $^ $(CXXFLAGS) $(ERRFLAGS) $(LIBS)