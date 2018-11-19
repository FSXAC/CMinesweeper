# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Wall -I

# Built target
TARGET = minesweeper

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).o $(TARGET).c

clean:
	$(RM) $(TARGET)


