# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Iinclude -MMD -MP

# Directories
SRCDIR = src
OBJDIR = obj
OUTPUTDIR = output

# Source files and object files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Target executable
TARGET = $(OUTPUTDIR)/main

# Ensure obj and output directories exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OUTPUTDIR):
	mkdir -p $(OUTPUTDIR)

# Rule to build the final executable
$(TARGET): $(OUTPUTDIR) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) -lpcap

# Rule to compile each .c file into an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(OUTPUTDIR)

# Phony target to build everything
.PHONY: all
all: $(TARGET)
