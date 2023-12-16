CC = 		g++ -std=c++17
CCFLAGS = 	-g -c -Wall -Werror
LINK = 		g++ -std=c++17
LINKFLAGS = -g -Wall -Werror

all: main.o

main.o : main.cpp src/node.hpp src/tree.hpp src/binary_search_tree.hpp
		$(CC) $(LINKFLAGS) -o main.o main.cpp 
