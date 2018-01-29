CC = gcc
CFLAGS = -Wall -Wextra -g -O3 -std=c99
LDFLAGS = -pthread -lm

all: graphColor_FF 

## FF 
graphColor_FF: test_graphColor.o graphColorFF.o graph.o
	$(CC) $(LDFLAGS) -o graphColor_FF test_graphColor.o graphColorFF.o graph.o

test_graphColor.o: test_graphColor.c
	$(CC) $(CFLAGS) -c -o test_graphColor.o test_graphColor.c

graphColorFF.o: graphColor.c
	$(CC) $(CFLAGS) -c -o graphColorFF.o graphColor.c 


## EXTRA
graphColor.o: graphColor.c 
	$(CC) $(CFLAGS) -c -o graphColor.o graphColor.c

graph.o: graph.c graph.h 
	$(CC) $(CFLAGS) -c -o graph.o graph.c

clean:
	rm -f *.o graphColor_FF
