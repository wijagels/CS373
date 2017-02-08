CXX=clang++
CXXFLAGS=-c -Wall -Wextra -pedantic -std=c++11
LDFLAGS=
SOURCES=nfa.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=jagels_p1

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@
