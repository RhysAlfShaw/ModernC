# Detect the operating system
ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif

# Set the compiler
CC = gcc

# Set the compiler flags
CFLAGS = -Wall -fPIC -std=c2x

# Set directories
SRC_DIR = lib
BIN_DIR = bin

# Ensure the bin directory exists
$(shell mkdir -p $(BIN_DIR))

# Set the output name based on the OS
ifeq ($(detected_OS),Windows)
    TARGET = $(BIN_DIR)/math_operations.dll
else ifeq ($(detected_OS),Darwin)
    TARGET = $(BIN_DIR)/libmath_operations.dylib
else
    TARGET = $(BIN_DIR)/libmath_operations.so
endif

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Default target
all: $(TARGET)

# Rule to build object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the shared library
$(TARGET): $(OBJS)
ifeq ($(detected_OS),Windows)
	$(CC) $(CFLAGS) -shared -o $(TARGET) $(OBJS)
else ifeq ($(detected_OS),Darwin)
	$(CC) $(CFLAGS) -dynamiclib -o $(TARGET) $(OBJS)
else
	$(CC) $(CFLAGS) -shared -o $(TARGET) $(OBJS)
endif

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean