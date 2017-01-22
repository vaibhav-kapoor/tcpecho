CC=gcc
CFLAGS= -Wall -g
RM= rm -f
.PHONY: all clean

all: server client

server: server.o
	$(CC) $(CFLAGS) $< -o $@
server.o: server.c
	$(CC) $(CFLAGS) -c $< -o $@

client: client.o
	$(CC) $(CFLAGS) $< -o $@
client.o: client.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o *.so server client
