CC = gcc -g -O2
CXX = g++ -g -O2
CFLAGS =
LIBS = -lnfc
OBJS = scanner.o

all: test

scanner.o: scanner.c scanner.h
	$(CC) -c scanner.c -o scanner.o

test: test.cc scanner.o
	$(CXX) test.cc -o test $(OBJS) $(LIBS)

clean:
	rm -f *.o
	rm -f test
