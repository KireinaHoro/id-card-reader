CC = gcc
CXX = g++

LIBS = -lnnxx -lnanomsg
OBJS = controller.o
TARGETS = controller
HEADERS =

INCLUDES = -I../include

_CFLAGS = -g -O2 $(INCLUDES) -Wall
_CXXFLAGS = $(_CFLAGS) -std=c++17

CFLAGS = $(_CFLAGS) -c
CXXFLAGS = $(_CXXFLAGS) -c

LDFLAGS = $(_CXXFLAGS)

all: $(TARGETS)

controller.o: controller.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) controller.cc -o controller.o

controller: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o controller

clean:
	rm -f $(OBJS) $(TARGETS)
