CC = gcc                             # Compiler
CFLAGS = -Wall -Wextra -g            # Compiler flags
TARGET = bin/pa1.out

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, obj/%.o, $(wildcard src/*.c))
DIRS := bin obj include

all: $(DIRS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

obj/%.o: src/%.c
	$(CC) -c $< -o $@

$(DIRS):
	mkdir -p $@

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: prepare
prepare:
	rm -f $(OBJS) $(wildcard bin/*)