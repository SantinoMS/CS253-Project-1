CC = g++
CFLAGS = -std=c++11 -Wall -g

main: clean build
	./main

build: src/main.cpp
	$(CC) $(CFLAGS) -o main src/main.cpp

clean:
	rm -f main

reset:
	rm *.txt