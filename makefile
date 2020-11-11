# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
CC = g++
CFLAGS  = -g -Wall -std=c++11
LFLAGS  = -L/usr/lib

# All Targets
all: spl_assignment

# Tool invocations
spl_assignment: bin/Agent.o bin/Graph.o bin/Tree.o bin/main.o bin/Session.o
	@echo 'Building target: spl_assignment'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/spl_assignment bin/Agent.o  bin/Graph.o bin/Tree.o bin/main.o bin/Session.o $(LFLAGS)
	@echo 'Finished building target: spl_assignment'
	@echo ' '

bin/Agent.o: src/Agent.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Agent.o src/Agent.cpp

bin/Graph.o: src/Graph.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Graph.o src/Graph.cpp

bin/Tree.o: src/Tree.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Tree.o src/Tree.cpp
	
bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/main.o src/main.cpp

bin/Session.o: src/Session.cpp
	$(CC) $(CFLAGS) -c -Iinclude -o bin/Session.o src/Session.cpp
	
#Clean the build directory
clean: 
	rm -f bin/*
