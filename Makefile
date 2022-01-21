# Include/ dir and obj/ dir
IDIR=include
ODIR=obj

# Compiler options and flags
CXX=g++

# Check if make is being ran on Windows or Unix
ifeq ($(OS),Windows_NT)
	CXXFLAGS=-I$(IDIR) -Llib/
	OUT_EXT=exe
else
	CXXFLAGS=-I$(IDIR)
	OUT_EXT=out
endif

ERRFLAGS=-O3 -Wall -Wextra -Werror -g

# Put header files here
_DEPS=
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

# Put cpp files but change extension to .o
_OBJ=main.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

# Libraries
ifeq ($(OS),Windows_NT)
	LIBS=-lncurses
else
	LIBS=-lncurses
endif

# Compile .cpp files to .o files
$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(ERRFLAGS)

# Link .o files and make an executable in bin/ folder
main: $(OBJ)
	$(CXX) -o bin/$@.$(OUT_EXT) $^ $(CXXFLAGS) $(ERRFLAGS) $(LIBS)