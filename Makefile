# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Wall -I

OBJS = grid.o minesweeper.o

# Built target
TARGET = minesweeper

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) -f $(TARGET) *~


