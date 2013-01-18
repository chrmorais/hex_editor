CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lpanel -lncurses
SOURCES=main.cpp GUI/AddrBlock.cpp GUI/ByteGrid.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -r *.o main