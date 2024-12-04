# Compiler and flags
CC = gcc
CFLAGS = -Wall -pthread

#make memo = ./memo
#make test = ./test
TARGET = memo
TEST_TARGET = test

# Source files
SOURCES = memo.c main.c
TEST_SOURCES = test.c memo.c

# Object files (generated from sources)
OBJECTS = $(SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

# Default rule: Build the target executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to build the test executable
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule (removes object and executable files)
clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_OBJECTS) $(TEST_TARGET)
