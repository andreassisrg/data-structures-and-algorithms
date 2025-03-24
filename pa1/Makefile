CC = gcc                             # Compiler
CFLAGS = -Wall -Wextra -g            # Compiler flags
TARGET = bin/pa1.out

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, obj/%.o, $(wildcard src/*.c))

all: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

obj/%.o: src/%.c
	$(CC) -c $< -o $@

.PHONY: clean
clean:
	rm $(OBJS)

.PHONY: prepare
prepare:
	rm $(OBJS) $(wildcard bin/*)