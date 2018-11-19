# Compiler
CC = gcc

# Compiler flags
CFLAGS = -g -Wall

# Built target
TARGET = minesweeper

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)


