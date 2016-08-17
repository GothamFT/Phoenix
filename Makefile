CC = g++
CFLAGS = -c -g -Wall -O2 

EXEC = btc_arb
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

all: EXEC

EXEC: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) -lcrypto -ljansson -lcurl -g

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf core $(OBJECTS)
