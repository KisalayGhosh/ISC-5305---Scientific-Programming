# Compiler and compiler flags
CC = g++
CCFLAGS = -std=c++11

# Source files and executables for the heat simulation
SRC1 = generate_grid.cpp
SRC2 = generate_heat_distribution.cpp
EXEC1 = generate_grid.x
EXEC2 = generate_heat_distribution.x

# Default target: build both executables
all: $(EXEC1) $(EXEC2)

# Rule to build the first executable (generate_grid)
$(EXEC1): $(SRC1)
	$(CC) $(CCFLAGS) -o $(EXEC1) $(SRC1)

# Rule to build the second executable (generate_heat_distribution)
$(EXEC2): $(SRC2)
	$(CC) $(CCFLAGS) -o $(EXEC2) $(SRC2)

# Rule to run the simulation with user inputs
run:
	# Default values if not provided by the user
	@echo "Running the simulation with command-line inputs..."
	@read -p "Enter number of grid points (N): " N; \
	read -p "Enter initial temperature: " T_initial; \
	read -p "Enter range a (lower bound): " a; \
	read -p "Enter range b (upper bound): " b; \
	./$(EXEC1) $$N $$T_initial initial_grid.csv; \
	./$(EXEC2) initial_grid.csv $$a $$b heat_distribution.csv; \
	python3 visual.py

# Clean up generated files (executables, CSV files, plot files)
clean:
	rm -rf *.o $(EXEC1) $(EXEC2) initial_grid.csv heat_distribution.csv heat_distribution_plot.png
