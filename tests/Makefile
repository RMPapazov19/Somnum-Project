IDIR=../include
CXX=g++

ifeq ($(OS),Windows_NT)
	CXXFLAGS=-I. -I$(IDIR) -I$(IDIR)/PDcurses
	OUT_EXT=exe
else
	CXXFLAGS=-I$(IDIR)
	OUT_EXT=out
endif

UnitTests: UnitTests.cpp
	$(CXX) -o $@.$(OUT_EXT) $^ $(CXXFLAGS)