TARGET=a.out
CXX=g++
DEBUG=-g
OPT=-O0
WARN=-Wall -Wno-unknown-pragmas
NCURSES=-lncurses -ltinfo
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(NCURSES) -pipe
LD=g++
LDFLAGS=$(NCURSES)
OBJS= main.o nvimfy.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
	@rm -rf *.o
 
main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o
 
nvimfy.o: nvimfy.cpp
	$(CXX) -c $(CXXFLAGS) nvimfy.cpp -o nvimfy.o