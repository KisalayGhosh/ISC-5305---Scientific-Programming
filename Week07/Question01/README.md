
# Polynomial Manipulation and Differentiation Project

This project involves building a C++ program to manipulate and differentiate polynomials using a binary tree structure. The project aims to demonstrate the use of modern C++ practices, including object-oriented design, smart pointers, and expression trees.

## Objective

The goal of this project is to construct a polynomial from its roots, represent it in a binary tree, differentiate it, evaluate it at specific points, and save the results to a file. Additionally, a Python script is provided to visualize the polynomial and its derivatives.

---

## Project Structure

The project consists of the following main files:

- **`Node.hpp`**: Defines the `Node` class to represent individual terms (constants, variables, operators) in the polynomial.
- **`PolynomialBinaryTree.hpp`**: Implements the `PolynomialBinaryTree` class to construct and manipulate polynomials using nodes.
- **`main.cpp`**: The main driver code to construct the polynomial, differentiate it, evaluate it, and save results.
- **`test.cpp`**: Contains unit tests for verifying each function of the project.
- **`plot.py`**: A Python script to visualize the polynomial and its derivatives.

---

## Detailed Explanation of Each Class and Function

### Node Class (`Node.hpp`)

The `Node` class represents a single element in the polynomial expression tree. Each node can be:
- **Constant**: Holds a constant numerical value.
- **Variable**: Represents a variable, typically "x".
- **Operator**: Holds an operator (`+`, `-`, `*`, etc.) and has left and right child nodes.

#### Key Functions
- **Constructors**: There are constructors for constants, variables, and operators, allowing the node to be flexible in representing any part of the polynomial.
- **Getters**: Each property (e.g., `getConstantValue`, `getVariable`, `getOperator`) has a getter function to access it.

### PolynomialBinaryTree Class (`PolynomialBinaryTree.hpp`)

The `PolynomialBinaryTree` class manages a tree structure to represent and manipulate polynomials. It uses `std::shared_ptr<Node>` for each node to enable shared ownership, as multiple tree nodes may need to reference the same sub-expressions, especially during differentiation.

#### Key Functions

- **`constructFromZeros(const std::vector<double>& zeros)`**:
  - Constructs a polynomial from its zeros (roots). Each root is added as a factor in the polynomial (e.g., for roots `-0.5` and `0.5`, the polynomial is \((x + 0.5)(x - 0.5)\)).
  - **Justification for Smart Pointers**: `std::shared_ptr` is used here to allow shared ownership of nodes, making it easier to manage nodes' lifetimes without worrying about memory leaks.
  
- **`differentiate()`**:
  - Differentiates the polynomial by applying differentiation rules recursively. It handles:
    - Constant nodes: Derivative is 0.
    - Variable nodes: Derivative is 1.
    - Operators (`+`, `-`, `*`): Applies the appropriate differentiation rules (e.g., product rule for `*`).
  - Returns a new `PolynomialBinaryTree` representing the differentiated polynomial.
  - **Justification**: We use recursion to traverse and differentiate each node. `std::shared_ptr` allows seamless copying of nodes to build the differentiated tree.

- **`evaluate(double x)`**:
  - Evaluates the polynomial at a specific value of `x` by traversing the expression tree and performing the necessary calculations.
  
- **`add` and `multiply`**:
  - These functions create new `PolynomialBinaryTree` objects that represent the sum or product of two polynomials.
  - **Justification for Design**: Using `add` and `multiply` functions with shared pointers allows easy manipulation of polynomial expressions as trees without worrying about memory ownership.

### Main Program (`main.cpp`)

The main program constructs a polynomial from specific roots, differentiates it up to five times, and evaluates it at intervals between 0 and 1. Results are saved to `polynomial_evaluation.txt`.

#### Key Functions

- **`savePolynomialEvaluation(const PolynomialBinaryTree& poly, const std::string& filename)`**:
  - Saves the evaluated polynomial and its derivatives at 100 points in the range [0, 1].
  - Uses `differentiate()` repeatedly to obtain higher-order derivatives.
  - Writes results to a file, which can then be visualized using the provided Python script.

### Test File (`test.cpp`)

`test.cpp` includes unit tests for the following:

1. **`testConstructFromZeros()`**: Verifies that a polynomial constructed from zeros evaluates to zero at each root.
2. **`testEvaluate()`**: Confirms that the polynomial evaluates correctly at a known point.
3. **`testDifferentiation()`**: Checks that the derivative of the polynomial is correct using a numerical approximation.
4. **`testRepeatedRoots()`**: Tests that repeated roots are handled properly.

---

## Justification for Using `std::shared_ptr`

In this project, `std::shared_ptr` was chosen over `std::unique_ptr` because:
1. **Shared Ownership**: Each node in the polynomial tree can be referenced by multiple other nodes, especially when differentiating. Using `std::shared_ptr` allows multiple references without needing to manage ownership explicitly.
2. **Ease of Use**: With `std::shared_ptr`, we avoid manually deleting nodes, which reduces the risk of memory leaks.
3. **Flexibility for Complex Structures**: For an expression tree that requires nodes to be shared or copied, `std::shared_ptr` provides the flexibility we need for safe and efficient memory management.

---

## Instructions to Compile and Run

### Requirements

- C++17 or higher
- Python 3 with `matplotlib` and `numpy` for visualization

### Step 1: Compile the Program

Use the provided `Makefile` to compile the program and tests:

```bash
make
```

This will produce two executables:
- **`polynomial_main`**: The main program that evaluates and saves the polynomial data.
- **`tests`**: The test program to verify correctness.

### Step 2: Run the Main Program

```bash
./polynomial_main
```

This will output `polynomial_evaluation.txt` with values of the polynomial and its first five derivatives.

### Step 3: Run the Tests

To verify the functionality:

```bash
./tests
```

You should see output indicating that each test has passed.

### Step 4: Visualize Results with Python

To plot the polynomial and its derivatives, use the provided Python script:

```bash
python plot.py
```

This will display a plot of the polynomial and its derivatives from `polynomial_evaluation.txt`.

---

## Output Example

`polynomial_evaluation.txt` will contain values of \( P(x) \) and its derivatives at 100 points:

```plaintext
x     P(x)     P'(x)    P''(x)   P'''(x)  P''''(x)  P'''''(x)
0.00  1.0000   -0.5000  ...
0.01  0.9950   -0.4750  ...
...
```

---

## Troubleshooting

- **Memory Issues**: Ensure that all nodes in `PolynomialBinaryTree` are managed by `std::shared_ptr`.
- **Accuracy of Differentiation**: If there are issues with `testDifferentiation`, check the finite difference calculation in `test.cpp`.

---

## Future Improvements

- **Support for Additional Operators**: Extend `Node` and `PolynomialBinaryTree` to support division (`/`) and power (`^`) operators.
- **Further Optimization**: Consider using `std::unique_ptr` if exclusive ownership of nodes becomes feasible in future designs.

- Plot
- <img width="703" alt="Screenshot 2024-10-31 230401" src="https://github.com/user-attachments/assets/04eade51-c614-4245-a37a-2b93332cfc28">


---

This project demonstrates the use of modern C++ for symbolic computation, highlighting memory management, object-oriented design, and numerical methods.
