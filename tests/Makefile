
# Include/ dir and obj/ dir
IDIR=../include
ODIR=.

# Compiler options and flags
CXX=g++

all: UnitTests

backend.o: ../src/backend.cpp
	$(CXX) -c ../src/backend.cpp -I../include

UnitTests.o: UnitTests.cpp
	$(CXX) -c UnitTests.cpp -I. -I../include

# Link .o files and make an executable in bin/ folder
UnitTests: backend.o UnitTests.o utest.h
	$(CXX) -o ./$@.$(OUT_EXT) $^