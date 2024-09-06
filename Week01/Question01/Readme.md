
# 1D Heat Distribution Simulation

---

## Question Statement

**Task**: Create a command-line tool that accepts input parameters (e.g., grid size `N`, initial temperature `T_initial`) for a simple 1D heat distribution simulation on a uniform grid and outputs the initial grid configuration \((x, T)\) to an output file. The input and output files must be read from the command line.

Create a separate program to generate the 1D heat distribution using \( T(x) = 1 - x^2 \), where the grid is defined by \( x \in [a, b] \), with `a` and `b` read from the command line along with the number of points `N`. The output should be written to a CSV file. 

Finally, write a Python script that reads the 1D heat distribution from the CSV file and generates a plot. 

---

## Work Performed

The project consists of three parts:

1. **Grid Generation (`generate_grid.cpp`)**:
   - This program accepts the number of grid points (`N`) and an initial temperature (`T_initial`) from the command line and generates a uniform grid with the specified initial temperature at each point. It writes the grid data to a CSV file (`initial_grid.csv`).

2. **Heat Distribution Calculation (`generate_heat_distribution.cpp`)**:
   - This program takes the grid generated in the previous step (from `initial_grid.csv`) and computes the temperature distribution using \( T(x) = 1 - x^2 \) over the range \( x \in [a, b] \), where `a` and `b` are specified from the command line. The results are written to another CSV file (`heat_distribution.csv`).

3. **Visualization (`visual.py`)**:
   - A Python script reads the `heat_distribution.csv` file and plots the temperature distribution using Matplotlib. The plot is saved as `heat_distribution_plot.png` and also displayed on the screen.

---

## File Descriptions

- **`generate_grid.cpp`**: Generates a 1D grid based on user-specified grid size and initial temperature. Outputs the grid to `initial_grid.csv`.
- **`generate_heat_distribution.cpp`**: Reads the grid from `initial_grid.csv`, computes the heat distribution, and writes the results to `heat_distribution.csv`.
- **`visual.py`**: Reads the heat distribution data from `heat_distribution.csv` and generates a plot of \( T(x) = 1 - x^2 \).
- **`Makefile`**: Automates the compilation of the C++ programs and the cleanup of generated files.
- **`README.md`**: This file contains a detailed description of the project.

---

## How to Compile and Run

### Compilation:

1. Navigate to the project directory.
2. Use the following command to compile the C++ programs:
   ```bash
   make
   ```

This will compile both `generate_grid.cpp` and `generate_heat_distribution.cpp`, generating two executables: `generate_grid.x` and `generate_heat_distribution.x`.

---

### Execution Steps:

1. **Run the Grid Generation Program**:
   ```bash
   ./generate_grid.x <N> <T_initial> initial_grid.csv
   ```
   Replace `<N>` with the number of grid points, and `<T_initial>` with the initial temperature for each grid point.
   
   Example:
   ```bash
   ./generate_grid.x 100 50.0 initial_grid.csv
   ```
   This command generates a grid of 100 points, each with an initial temperature of 50.0, and saves the grid to `initial_grid.csv`.

2. **Run the Heat Distribution Program**:
   After generating the initial grid, compute the heat distribution by running:
   ```bash
   ./generate_heat_distribution.x initial_grid.csv <a> <b> heat_distribution.csv
   ```
   Replace `<a>` and `<b>` with the lower and upper bounds of `x`.
   
   Example:
   ```bash
   ./generate_heat_distribution.x initial_grid.csv -1.0 1.0 heat_distribution.csv
   ```
   This command reads the grid from `initial_grid.csv`, computes the heat distribution over the range \( x \in [-1.0, 1.0] \), and writes the results to `heat_distribution.csv`.

3. **Run the Python Plotting Script**:
   To visualize the temperature profile, run the Python script:
   ```bash
   python3 visual.py
   ```
   This script will read `heat_distribution.csv`, generate a plot, and save it as `heat_distribution_plot.png`. The plot will also be displayed on the screen.

---

### Cleanup:

To clean up the generated files (executables, CSV files, and the plot), use the following command:
```bash
make clean
```
This will remove the executables `generate_grid.x`, `generate_heat_distribution.x`, and the generated CSV and plot files.

---

## Function Documentation

### `generate_grid.cpp`:
- **`generate_initial_grid(int N, double T_initial)`**:
   - Generates a 1D grid of size `N` with an initial temperature `T_initial`.
   - **Input**: `N` (grid size), `T_initial` (initial temperature).
   - **Output**: A vector of grid points with their temperatures.
   
- **`write_to_csv(const std::string& filename, const std::vector<std::pair<int, double>>& data)`**:
   - Writes the grid data to a CSV file.
   - **Input**: `filename` (output file), `data` (grid data).
   - **Output**: Writes the grid data to the file.

### `generate_heat_distribution.cpp`:
- **`read_from_csv(const std::string& filename)`**:
   - Reads grid data from a CSV file.
   - **Input**: `filename` (input file).
   
- **`compute_heat_distribution(const std::vector<int>& indices, double a, double b)`**:
   - Computes the heat distribution for each `x` point using \( T(x) = 1 - x^2 \).
   - **Input**: `indices` (grid indices), `a` (lower bound for `x`), `b` (upper bound for `x`).
   - **Output**: A vector of `(x, T)` pairs representing the heat distribution.
   
- **`write_heat_distribution_to_csv(const std::string& filename, const std::vector<std::pair<double, double>>& data)`**:
   - Writes the computed heat distribution to a CSV file.
   - **Input**: `filename` (output file), `data` (heat distribution data).

---

## Error Handling

### `generate_grid.cpp`:

- **Input Validation**:
   - Ensures that the number of grid points `N` is a positive integer.
   - Throws an `invalid_argument` exception if the input is invalid and displays an error message.
   
- **File Handling**:
   - Checks if the output file can be opened for writing. If it cannot be opened, the program throws an exception and displays an error message.

### `generate_heat_distribution.cpp`:

- **File Handling**:
   - Ensures that the input file exists and can be opened. If the file cannot be opened, the program throws an `ios_base::failure` exception and displays an error message.
   
- **Input Validation**:
   - Validates that the user provides valid values for the range bounds `a` and `b`.

### Suggestions for Additional Error Handling:

- You can add file format validation to ensure that the CSV files are formatted correctly before processing the data.
- Further input validation for ensuring `a < b` can be implemented.

---

## Visualization of the Temperature Profile

The Python script `visual.py` reads the heat distribution data from the CSV file (`heat_distribution.csv`) and generates a plot. The plot shows the temperature profile \( T(x) = 1 - x^2 \) for the specified range of `x`.

### Plot Details:
- **X-axis**: Represents the values of `x`.
- **Y-axis**: Represents the computed temperature values \( T(x) \).
- The plot is saved as `heat_distribution_plot.png` and also displayed on the screen.

- ### Plot:
![Heat Distribution Plot](<img width="473" alt="plot" src="https://github.com/user-attachments/assets/efd4b965-aa09-48b6-8b3c-c760828ee13e">
plot.png)


