
# Root-Finding Methods: Newton and Secant Methods Using Polymorphism and Templates

## Project Overview

This project implements root-finding algorithms using **Newton's Method** and **Secant Method** for solving non-linear equations. The project is built using **C++ templates** and **polymorphism**, allowing the algorithms to be applied for both float (32-bit) and double (64-bit) precision. The methods are applied to three different mathematical functions.

### Approach

The Newton and Secant methods are implemented as templated classes inheriting from a base abstract class `Function`. These methods iteratively compute the root of a given function starting from an initial guess. The project also verifies the computed roots and generates plots to track the convergence of the root-finding process.

The root-finding methods are tested for:
1. **Newton's Method**: Uses the derivative of the function to iteratively compute the root.
2. **Secant Method**: Does not require the derivative and approximates the root using two initial guesses.

### Functions Implemented

The root-finding methods are tested on the following functions:
1. **f(x) = sin(3x - 2)**: A sine function over the interval [0, 2π].
2. **f(x) = x³ - 6x² + 11x - 8**: A cubic polynomial.
3. **f(x) = log(x) + x² - 3**: A logarithmic quadratic function.

These functions are implemented in separate derived classes inheriting from the `Function` base class. Each function also includes a `verify` method that checks the accuracy of the computed root by evaluating the function at the root and returning the absolute error.

### Files in the Project

- **main.cpp**: Main program that runs the Newton and Secant methods for double precision. It writes the results to CSV files and uses manual memory management.
- **main1.cpp**: Same as `main.cpp`, but uses smart pointers (no need for manual memory management).
- **main_float.cpp**: Similar to `main.cpp`, but specialized for float precision instead of double precision.
- **sine_function.h**: Defines the sine function \( f(x) = \sin(3x - 2) \) for root-finding.
- **cubic_function.h**: Defines the cubic function \( f(x) = x³ - 6x² + 11x - 8 \).
- **log_quadratic_function.h**: Defines the logarithmic quadratic function \( f(x) = \log(x) + x² - 3 \).
- **newton.h**: Implements the Newton's Method as a templated class.
- **secant.h**: Implements the Secant Method as a templated class.
- **solver.h**: Base abstract class for root-finding methods. Contains common attributes like tolerance and maximum iterations.
- **function.h**: Abstract class defining the interface for mathematical functions.
- **Makefile**: A makefile to compile and build the project. It includes targets for double precision (`root_finding`), float precision (`root_finding_float`), and a clean target.
- **plot_roots.py**: Python script to plot the root vs iterations for both Newton and Secant methods from the generated CSV files.
- **CSV Files**: The generated files store iteration data for Newton and Secant methods, used for plotting.

### How the Project Works

1. **Newton's Method**: The method starts with an initial guess and iteratively computes the root using the derivative of the function. The iteration continues until the function value at the computed root is less than the specified tolerance.
2. **Secant Method**: This method starts with two initial guesses and approximates the derivative numerically. It iteratively computes the root without requiring the actual derivative of the function.

### Steps to Run the Project

1. **Clone the Repository**:
   Clone the project files to your local machine.

2. **Compile the Code**:
   Use the following command to compile the code using the Makefile:
   
   ```bash
   make
   ```

   This will generate two executables:
   - `root_finding`: For double precision using Newton and Secant methods.
   - `root_finding_float`: For float precision.

3. **Run the Executables**:
   Execute the compiled programs to generate the CSV files for root-finding iterations.
   
   ```bash
   ./root_finding
   ./root_finding_float
   ```

4. **Visualize the Results**:
   Run the Python script to plot the root vs iterations for both methods:
   
   ```bash
   python plot_roots.py
   ```

   This will generate plots showing how the root converges over iterations for both methods.

5. **Clean the Project**:
   Run the following command to clean the compiled files:
   
   ```bash
   make clean
   ```

### Deliverables

1. **Functional Makefile**: A Makefile that compiles the code with appropriate targets.
2. **Main Program**: A `main.cpp` and `main1.cpp` that implement root-finding using both manual and smart pointer memory management.
3. **Float Precision Version**: A `main_float.cpp` specialized for float precision.
4. **Function Implementations**: Templated implementations of Newton and Secant methods in `newton.h` and `secant.h`.
5. **Verification**: The `verify` function is implemented in each derived class to confirm the accuracy of the computed root.
6. **Plots**: Generated plots of root vs iterations for both Newton and Secant methods.
7. **README.md**: This document explaining the project and steps to run it.

### Project Structure

```
├── main.cpp
├── main1.cpp
├── main_float.cpp
├── sine_function.h
├── cubic_function.h
├── log_quadratic_function.h
├── newton.h
├── secant.h
├── solver.h
├── function.h
├── Makefile
├── plot_roots.py
├── *.csv (Generated CSV files)
└── README.md
```


