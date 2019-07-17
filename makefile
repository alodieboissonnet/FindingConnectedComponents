CC=g++
CFLAGS=-c -Wall -Wextra
LDFLAGS=
SOURCES=graph.cpp node.cpp edge.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=pgm

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)
