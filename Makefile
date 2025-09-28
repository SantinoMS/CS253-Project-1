CC = g++
CFLAGS = -Wall -g

main: src/main.cpp
	$(CC) $(CFLAGS) -o main src/main.cpp

clean:
	rm -f main