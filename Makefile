CXX = g++ -std=c++20
CXXFLAGS = -Wall -g -MMD -I/opt/homebrew/include # extra include path for Homebrew packages
LDFLAGS = -L/opt/homebrew/lib
SOURCES = $(wildcard *.cc) $(wildcard pieces/*.cc) $(wildcard ai/*.cc) # list of all .cc files
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=chess

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o $(EXEC) -lX11 -lpng $(LIBFLAGS)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBFLAGS)

-include ${DEPENDS}

.PHONY: clean tests
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
