# Compiler and compiler flags
CC = g++
CCFLAGS = -std=c++11 -Wall

# Source files
SRC = homework2.cpp
TEST_SRC = tests2.cpp

# Executables
EXEC = homework2.x
TEST_EXEC = tests2.x

# Default target: build both executables
all: $(EXEC)

# Rule to build the main executable
$(EXEC): $(SRC)
	$(CC) $(CCFLAGS) -o $(EXEC) $(SRC)

# Rule to build the test executable with TEST_MODE defined
test: $(TEST_SRC)
	$(CC) $(CCFLAGS) -DTEST_MODE -o $(TEST_EXEC) $(TEST_SRC)

# Rule to run the main program
run:
	./$(EXEC)

# Rule to run the tests
run_tests:
	./$(TEST_EXEC)

# Clean up generated files
clean:
	rm -f $(EXEC) $(TEST_EXEC) traject_2d.txt traject_3d.txt
	rm -rf images
