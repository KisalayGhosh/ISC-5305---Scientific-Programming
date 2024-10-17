# ScientificContainer Project

## Overview

This project involves creating a `ScientificContainer` class in C++ that manages various scientific calculation objects and their associated metadata. The container supports adding elements, managing metadata, performing computations, filtering elements, and serializing the data to a JSON-like format. The project demonstrates the use of advanced C++ features such as templates, smart pointers, custom exceptions, and standard library containers.

## Features

1. **Custom Exception Handling**
   - A custom exception (`DuplicateElementException`) is used to handle attempts to add duplicate elements to the container, providing a more descriptive error message.

2. **Polymorphism for Scientific Computations**
   - The `ScientificObject` base class provides a uniform interface for different types of scientific calculations.
   - Derived classes (`VectorCalculation`, `MatrixCalculation`, and `TensorCalculation`) override the `compute` function to provide specific computation logic.

3. **Template Functions for Data Processing**
   - Template functions are used to enforce type safety during data processing.
   - `static_assert` is used to ensure that only arithmetic types are allowed in the generic `process_data()` function, reducing runtime errors.

4. **Metadata Management**
   - Metadata can be associated with each element in the container, including an integer, a double, a string, and a callback function.
   - Metadata is printed and the associated callbacks are executed upon request.

5. **Serialization**
   - The container can serialize itself to a JSON-like format, providing a structured overview of its contents. This is useful for debugging or exporting the container's state.

6. **Exception Safety**
   - The code implements both basic and strong exception safety. Errors in one computation or callback do not affect others.

7. **Unit Testing**
   - A `run_tests()` function is provided to verify the correctness of core functionalities, including adding elements, adding metadata, performing computations, filtering elements, and serialization.

## Detailed Design Choices

### Static Assertions

- The `static_assert` in `process_data()` ensures that only arithmetic types are passed to the function, preventing incorrect usage at compile time.
- This choice was made to ensure that the function is used only with valid types, thus reducing runtime errors and enforcing stricter type safety.

### Exception Safety Analysis

- **`add_element()` Function**: Provides **basic exception safety** by ensuring the container is not modified if a duplicate element is added. The `DuplicateElementException` is thrown if a duplicate key is detected.
- **`add_metadata()` Function**: This function also provides **basic exception safety** by checking for existing metadata before adding new entries, preventing overwriting.
- **`compute_all()` Function**: Implements **strong exception safety** by using try-catch blocks to ensure that each computation runs independently without affecting others in case of an error.
- Exception safety is essential for ensuring that the program remains in a valid state, even when unexpected errors occur.

### Design Considerations

- The use of **polymorphism** through the `ScientificObject` class allows for extensibility, meaning new types of calculations can be added without changing the container's implementation.
- **Smart Pointers (`std::shared_ptr`)** are used for memory management, providing automatic deallocation and preventing memory leaks. `shared_ptr` was chosen over `unique_ptr` to allow shared ownership of the scientific objects.
- The decision to use **`std::vector`** for storing elements was based on its efficient iteration and cache-friendly nature, which are advantageous given the relatively small container size.

### Alternatives Considered

- **Using `std::unique_ptr` instead of `std::shared_ptr`**: `unique_ptr` could be used for more efficient memory management, but `shared_ptr` was chosen to allow multiple references to the same scientific object.
- **Using `std::list` instead of `std::vector`**: `list` would be more efficient for frequent insertions and deletions, but the primary use case involves iteration, which favors `vector` due to better cache locality.

## Usage Instructions

### Compilation

To compile the program, use the following command:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o scientific_program
```

Make sure to use C++17 or a later version to support the features used in the code.

### Running the Program

To run the compiled program, use:

```bash
./scientific_program
```

### Running Unit Tests

The program includes a `run_tests()` function to verify the functionality of the container. These tests include adding elements, adding metadata, performing computations, filtering, and serialization.

## Example Output

The program demonstrates the following steps:

1. Adding elements to the container (`VectorCalculation`, `MatrixCalculation`, `TensorCalculation`).
2. Associating metadata with each element, including a callback function.
3. Processing different types of data using `process_data()`, including integers, doubles, complex numbers, and strings.
4. Computing each element in the container.
5. Printing metadata and executing callbacks.
6. Filtering elements based on a custom condition (e.g., even keys).
7. Iterating over elements using range-based loops.
8. Serializing the container to a JSON-like format.
9. Running unit tests to validate core functionalities.

## Conclusion

The `ScientificContainer` project demonstrates effective use of modern C++ features such as templates, smart pointers, polymorphism, and custom exception handling. By designing the container with flexibility, extensibility, and safety in mind, the solution is both robust and easy to extend. The extensive use of comments, error handling, and static assertions ensures that the code is readable, maintainable, and free from common runtime issues.

The project illustrates key concepts in software design, including type safety, exception safety, and object-oriented programming, making it an ideal reference for learning advanced C++ programming techniques.

## Future Improvements

- **Parallel Computation**: Implement parallel execution for `compute_all()` to leverage multi-core processors.
- **Better Memory Management**: Consider using `std::unique_ptr` if shared ownership is not required, to reduce overhead.
- **Extended Metadata**: Add more metadata fields, such as timestamps or performance metrics, to enhance the information available for each element.

## Author

Kisalay Ghosh
