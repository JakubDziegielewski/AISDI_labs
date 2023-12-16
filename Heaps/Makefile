CC = 		g++ -std=c++17
CCFLAGS = 	-g -c -Wall -Werror
LINK = 		g++ -std=c++17
LINKFLAGS = -g -Wall -Werror

all: heap.o main.o output_file.o

heap.o : heap.cpp
		$(CC) $(CCFLAGS) -o heap.o heap.cpp
main.o : main.cpp
		$(CC) $(CCFLAGS) -o main.o main.cpp 
output_file.o : heap.o main.o
		$(LINK) $(LINKFLAGS) -o output_file.o heap.o main.o -lm
