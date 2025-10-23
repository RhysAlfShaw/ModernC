# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude -std=c2x 

SRCDIR = src
OBJDIR = obj
BINDIR = bin

TARGET = $(BINDIR)/main
SOURCES = $(wildcard $(SRCDIR)/*.c)

OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR) # Ensure the bin directory exists
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Linking complete. Executable is at $(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) # Ensure the object directory exists
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< into $@"

.PHONY: run
run: all
	@echo "Running the program..."
	./$(TARGET)

# The 'clean' target removes all compiled files.
.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -rf $(OBJDIR) $(BINDIR)