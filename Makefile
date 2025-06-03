CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = memGer
OBJS = main.o fifo.o lru.o utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c page_replacement.h
	$(CC) $(CFLAGS) -c main.c

fifo.o: fifo.c page_replacement.h
	$(CC) $(CFLAGS) -c fifo.c

lru.o: lru.c page_replacement.h
	$(CC) $(CFLAGS) -c lru.c

utils.o: utils.c page_replacement.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
