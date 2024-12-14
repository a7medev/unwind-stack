CC = gcc
CFLAGS = -Wall -Wextra -g
OBJECTS = unwind-stack.o main.o

# Default target
all: program

# Compile the program
program: $(OBJECTS)
	$(CC) $(OBJECTS) -o program

# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Explicit dependencies
unwind-stack.o: unwind-stack.c unwind-stack.h
main.o: main.c unwind-stack.h

# Run the program
run: program
	./program

# Clean build files
clean:
	rm -f program $(OBJECTS)

# Phony targets
.PHONY: all clean run
