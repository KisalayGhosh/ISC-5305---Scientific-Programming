# Numerical Integration Methods: Analysis and Benchmarking

## Author
Kisalay Ghosh

## Date
November 14, 2024

## Introduction
This project explores various numerical integration techniques, focusing on comparing adaptive and non-adaptive methods. We evaluate the performance, accuracy, and efficiency of these methods using both simple and complex test functions. The methods implemented include Non-Adaptive Simpson and Adaptive Trapezoidal methods.

## Methods
The following numerical integration methods are analyzed:
- **Non-Adaptive Simpson Method**: A fixed-step method well-suited for smooth functions.
- **Adaptive Trapezoidal Method**: An adaptive approach that adjusts step sizes based on function behavior.

## Test Functions
We used three test functions to assess the integration methods:
1. **Function 1**: \( f_1(x) = \sin(x) \)  
   - *Interval*: \([0, \pi]\)
   - *Exact Integral*: 2
2. **Function 2**: \( f_2(x) = e^{-x^2} \sin(1000x) \)  
   - *Interval*: \([0, \pi]\)
   - *Characteristics*: Highly oscillatory
3. **Function 3**: \( f_3(x) = x^{0.75} \log(1 + x^2) \)  
   - *Interval*: \([0, \pi]\)
   - *Characteristics*: Combines polynomial and logarithmic components

## Compilation and Execution
### Compilation
Use the `make` command to compile all source files:
```bash
make


./simpson_adaptive_nonrecursive.x
# Output: integral: 330.667, exact: 330.667

./simpson_adaptive_recursive.x
# Output: Adaptive Simpson's Rule Result: 14.0259, Exact Integral: 14.0259, Error: 1.1649e-09

./simpson_nonadaptive_nonrecursive.x
# Output: integral: 330.667, exact: 330.667

./simpson_nonadaptive_recursive.x
# Output: integral: 330.667, exact: 330.667

./trapezoidal_adaptive_nonrecursive.x
# Output: integral: 330.75, exact: 330.667

./trapezoidal_adaptive_recursive.x
# Output: integral: 330.672, exact: 330.667

./trapezoidal_nonadaptive_nonrecursive.x
# Output: integral: 330.667, exact: 330.667

./trapezoidal_nonadaptive_recursive.x
# Output: integral: 330.672, exact: 330.667
