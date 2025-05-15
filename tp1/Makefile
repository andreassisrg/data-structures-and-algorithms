CC = g++                             # Compiler
CFLAGS = -Wall -Wextra -g            # Compiler flags
TARGET = bin/tp1.out

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, obj/%.o, $(wildcard src/*.cpp))
DIRS := bin obj include

all: $(DIRS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

obj/%.o: src/%.cpp
	$(CC) -c $< -o $@

$(DIRS):
	mkdir -p $@

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: prepare
prepare:
	rm -f $(OBJS) $(wildcard bin/*)