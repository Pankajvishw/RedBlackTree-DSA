# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Source and object directories
SRC := $(wildcard *.c)
OBJDIR := obj
OBJ := $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Output binary
TARGET := rbtree

# Default build rule
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile .c files into object files inside obj/
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if not exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)
