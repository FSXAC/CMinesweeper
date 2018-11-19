# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

OBJS = grid.o minesweeper.o

# Built target
TARGET = minesweeper

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	$(RM) $(OBJS) $(TARGET) *~


