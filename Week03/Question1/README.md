
# Week 3 Assignment - 3D Array Grid Implementation

## Overview

This assignment involves creating a 3D grid (named `Grid`) using three different methods in C++:
1. 1D Array
2. `std::vector`
3. `new` operator

Each method is implemented in separate `.cpp` files, and the grid can be manipulated using a set of functions. This README provides an overview of the implementation, the steps to compile and run the project, and the tests conducted to verify the functionality of the grids.

## Files
The following files are included:
- `grid3d_1d_array.cpp`: Implements the grid using a 1D array.
- `grid3d_vector.cpp`: Implements the grid using `std::vector`.
- `grid3d_new.cpp`: Implements the grid using the `new` operator.
- `grid3d_1d_array.h`: Header file for the 1D array implementation.
- `grid3d_vector.h`: Header file for the `std::vector` implementation.
- `grid3d_new.h`: Header file for the `new` operator implementation.
- `main.cpp`: Main file that tests the grids by creating and manipulating them.
- `test_grid.cpp`: Test file that includes several unit tests.
- `Makefile`: A makefile to compile the project.
- `grid_summation_plot.py`: Python script to generate a plot showing the time taken to sum grids for different sizes.

## Functions Implemented

Each grid implementation has the following functions:

### Constructor
- **Description**: Initializes a 3D grid.
- **Parameters**: `nx_`, `ny_`, `nz_` (Grid dimensions).
- **Return**: None

### Destructor
- **Description**: Frees the allocated memory for the grid.
- **Return**: None

### `getSize()`
- **Description**: Returns the total number of elements in the grid.
- **Return**: Total number of elements (int).

### `getMemory()`
- **Description**: Returns the memory used by the grid in bytes.
- **Return**: Memory in bytes (int).

### `operator()`
- **Description**: Accesses the value at a specific index `(i, j, k)`.
- **Parameters**: `i`, `j`, `k` (Indices).
- **Return**: Value at the specified index.

### `set()`
- **Description**: Sets a value at a specific index `(i, j, k)`.
- **Parameters**: `i`, `j`, `k` (Indices), `value` (Value to be set).

### `operator+`
- **Description**: Adds two grids element-wise.
- **Parameters**: Another grid object.
- **Return**: New grid with summed values.

### `operator<<`
- **Description**: Overloads `<<` for outputting the grid values.
- **Return**: Output stream with grid data.

## Exception Handling

Basic exception handling has been added for scenarios such as:
- Invalid grid size or dimension inputs.
- Out-of-bound index access for `operator()` and `set()`.

## Compilation and Execution

### Compilation
To compile the project, run the following commands in the terminal:
```bash
1. make homework.x
2. ./homework.x
3. make test_grid.x
4. ./test_grid.x
5. make clean


```

This will compile the main program (`homework.x`) and the test program (`test_grid.x`).

### Running the Program
To run the main program:
```bash
./homework.x
```
This will execute the grid operations as described in the `main.cpp` file.

To run the test suite:
```bash
./test_grid.x
```

### Python Plot
To generate the timing plot using Python, run:
```bash
python grid_summation_plot.py
```
This will generate a plot showing the time taken to add two grids for different grid sizes.

## Unit Tests

The following tests were created in `test_grid.cpp`:

1. **1D Array Grid Test**: Verifies that the grid is created correctly, values can be set, and element-wise addition works as expected.
2. **Vector-Based Grid Test**: Similar to the 1D array test, but uses the `std::vector` implementation.
3. **New Operator-Based Grid Test**: Ensures the `new` operator implementation behaves correctly.
4. **Memory Usage Test**: Checks that the `getMemory()` function reports the correct memory usage.
5. **Grid Summation Timing Test**: Measures the time taken to sum grids of various sizes.

## Timing Results

The following table shows the time taken to sum two grids for different grid sizes:

| Grid Size | 1D Array Time (s) | Vector Time (s) | New Operator Time (s) |
|-----------|------------------|-----------------|-----------------------|
| 10x10x10  | 1.42e-05         | 4.66e-05        | 1.64e-05              |
| 50x50x50  | 3.56e-04         | 7.63e-04        | 4.51e-04              |
| 100x100x100 | 1.32e-03        | 2.76e-03        | 1.63e-03              |
| 200x200x200 | 5.48e-03        | 1.03e-02        | 6.78e-03              |

## Conclusion

This assignment demonstrated the implementation of 3D grids using different memory management techniques in C++. Each implementation was tested for correctness, memory usage, and performance. The results show varying performance across the three methods, with the `new` operator method generally being faster in most cases.

## Additional Information
- AI was used to debug code, and provide exception handling logic.
- The Python script utilizes `matplotlib` to generate the plot.

Plot:

<img width="746" alt="plot_grid" src="https://github.com/user-attachments/assets/184038fc-93c9-441f-88db-658c82e3a35f">
