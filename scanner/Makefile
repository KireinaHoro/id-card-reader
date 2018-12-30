CC = gcc
CXX = g++

LIBS = -lnfc -lnnxx -lnanomsg
OBJS = scan.o scanner.o
TARGETS = scanner
HEADERS = scan.h

INCLUDES = -I../include

_CFLAGS = -g -O2 $(INCLUDES) -Wall
_CXXFLAGS = $(_CFLAGS) -std=c++17

CFLAGS = $(_CFLAGS) -c
CXXFLAGS = $(_CXXFLAGS) -c

LDFLAGS = $(_CXXFLAGS)

all: $(TARGETS)

scan.o: scan.c $(HEADERS)
	$(CC) $(CFLAGS) scan.c -o scan.o

scanner.o: scanner.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) scanner.cc -o scanner.o

scanner: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o scanner

clean:
	rm -f $(OBJS) $(TARGETS)
