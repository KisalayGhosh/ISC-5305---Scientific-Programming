# Compiler and compiler flags
CC = g++
CCFLAGS = -std=c++11 -Wall

# Source file and executable
SRC = homework2.cpp
EXEC = homework2.x

# Default target: build the executable
all: $(EXEC)

# Rule to build the executable (homework2.x)
$(EXEC): $(SRC)
	$(CC) $(CCFLAGS) -o $(EXEC) $(SRC)

# Rule to run the program
run:
	# Execute the compiled program
	./$(EXEC)

# Clean up generated files (executable, output files)
clean:
	rm -rf $(EXEC) traject_2d.txt traject_3d.txt
