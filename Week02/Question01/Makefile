# Compiler and compiler flags
CC = g++
CCFLAGS = -std=c++11 -Wall

# Source files and executables
SRC1 = homework2.cpp
SRC2 = tests2.cpp
EXEC1 = homework2.x
EXEC2 = tests2.x

# Default target: build both executables
all: $(EXEC1) $(EXEC2)

# Rule to build the homework2 executable (homework2.x)
$(EXEC1): $(SRC1)
	$(CC) $(CCFLAGS) -o $(EXEC1) $(SRC1)

# Rule to build the tests executable (tests2.x)
$(EXEC2): $(SRC2)
	$(CC) $(CCFLAGS) -o $(EXEC2) $(SRC2)

# Rule to run the main program
run: $(EXEC1)
	# Execute the main program
	./$(EXEC1)

# Rule to run the tests
test: $(EXEC2)
	# Execute the test suite
	./$(EXEC2)

# Clean up generated files (executables, output files)
clean:
	rm -rf $(EXEC1) $(EXEC2) traject_2d.txt traject_3d.txt
