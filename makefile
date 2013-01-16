CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lncurses -lpanel
SOURCES=main.cpp GUI/AddrBlock.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -r *.o main