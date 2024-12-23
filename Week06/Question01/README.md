<img width="187" alt="flow" src="https://github.com/user-attachments/assets/ee809ea7-711d-4fb4-b448-411397dafde0">
# ScientificContainer Project

## Overview

This project involves creating a `ScientificContainer` class in C++ that manages various scientific calculation objects and their associated metadata. The container can be used to add elements, filter elements, compute, manage metadata, add elements, and serialise data to a format similar to JSON. Advanced C++ features like templates, smart pointers, custom exceptions, and standard library containers are all used in this project to show off their use.

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
   - Every element in the container has the ability to have associated metadata, such as an integer, double, string, or callback function.

   - Metadata is printed and the associated callbacks are executed upon request.

5. **Serialization**
   - The container offers an organised summary of its contents by serialising itself to a format resembling JSON. This is helpful for exporting or debugging the state of the container.


6. **Exception Safety**
   - The code implements both basic and strong exception safety. Errors in one computation or callback do not affect others.

7. **Unit Testing**
   - A `run_tests()` function is provided to verify the correctness of core functionalities, including adding elements, adding metadata, performing computations, filtering elements, and serialization.

## Detailed Design Choices

### Static Assertions

- To prevent incorrect usage at compile time, the `static_assert` in `process_data()` makes sure that only arithmetic types are passed to the function.

- This choice was made to ensure that the function is used only with valid types, thus reducing runtime errors and enforcing stricter type safety.

### Exception Safety Analysis

- **`add_element()` Function**: Provides **basic exception safety** by ensuring the container is not modified if a duplicate element is added. The `DuplicateElementException` is thrown if a duplicate key is detected.
- **`add_metadata()` Function**: This function also provides **basic exception safety** by checking for existing metadata before adding new entries, preventing overwriting.
- **`compute_all()` Function**: uses try-catch blocks to implement **strong exception safety**, which makes sure that in the event of an error, each computation continues on its own without affecting others.

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
make
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

A good example of utilising contemporary C++ features like smart pointers, templates, polymorphism, and custom exception handling is the `ScientificContainer` project. The solution is both reliable and simple to expand because the container was designed with flexibility, extensibility, and safety in mind. The code is readable, maintainable, and free of common runtime problems thanks to the heavy use of comments, error handling, and static assertions.

The project serves as a great resource for learning advanced C++ programming techniques because it demonstrates important ideas in software design, such as type safety, exception safety, and object-oriented programming.


## Future Improvements

- **Parallel Computation**: Implement parallel execution for `compute_all()` to leverage multi-core processors.
- **Better Memory Management**: Consider using `std::unique_ptr` if shared ownership is not required, to reduce overhead.
- **Extended Metadata**: Add more metadata fields, such as timestamps or performance metrics, to enhance the information available for each element.

## UML Diagram
<img width="327" alt="uml" src="https://github.com/user-attachments/assets/98fd8398-d98b-4656-87d8-385a414c3c46">

## Flowchart
<img width="187" alt="flow" src="https://github.com/user-attachments/assets/319d5fd6-f906-46b5-8a5c-96bd64467e52">


## Author

Kisalay Ghosh
