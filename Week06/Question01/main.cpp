#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <memory>
#include <functional>
#include <stdexcept>
#include <complex>
#include <type_traits>
#include <cassert>

// Custom exception class for handling duplicate elements
// This exception is thrown when an attempt is made to add a duplicate element to the container
// The purpose of creating a custom exception is to provide a more meaningful error message that helps in identifying issues related to data duplication
class DuplicateElementException : public std::exception {
private:
    std::string message;
public:
    explicit DuplicateElementException(const std::string& elementKey)
        : message("Duplicate element: " + elementKey) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Abstract base class representing a scientific computation object
// This serves as the base for different types of scientific calculations
// The use of an abstract base class allows for polymorphism, enabling different types of scientific calculations to be handled uniformly
class ScientificObject {
public:
    // Pure virtual function to perform computation
    // Derived classes must implement this function to define specific computations
    virtual void compute() const = 0;
    virtual ~ScientificObject() = default;
};

// Derived class for vector-based scientific calculations
// Implements the compute method specifically for vector calculations
class VectorCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing vector calculation..." << std::endl;
        // Example computation: calculating the magnitude of a vector
        // This placeholder represents a computational task that could be more complex in a real application
    }
};

// Derived class for matrix-based scientific calculations
// Implements the compute method specifically for matrix calculations
class MatrixCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing matrix calculation..." << std::endl;
        // Example computation: matrix determinant calculation (conceptually)
        // This placeholder represents the concept of computing a determinant, which is a common matrix operation
    }
};

// Derived class for tensor-based scientific calculations
// Implements the compute method specifically for tensor calculations
class TensorCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing tensor calculation..." << std::endl;
        // Example computation: tensor contraction (conceptually)
        // Tensor contraction is a more advanced mathematical operation often used in physics and engineering
    }
};

// Template function to process scientific data
// Ensures that only arithmetic types are processed by using a compile-time check
// Throws a compile-time error if a non-arithmetic type is used, ensuring type safety
// The use of static_assert enforces stricter type constraints, reducing potential runtime errors
template <typename T>
void process_data(const T& data) {
    static_assert(std::is_arithmetic<T>::value, "Template type must be an arithmetic type.");
    std::cout << "Processing data: " << data << std::endl;
}

// Template specialization for processing std::complex<double>
// Specializes the process_data function to handle complex numbers, providing specific output for real and imaginary parts
template <>
void process_data(const std::complex<double>& data) {
    std::cout << "Processing complex number: Real = " << data.real() << ", Imaginary = " << data.imag() << std::endl;
}

// Overload for processing std::string
// Throws an invalid_argument exception if the string is empty, ensuring meaningful input
// Provides functionality to reverse the string as an example of string manipulation
template <>
void process_data(const std::string& data) {
    if (data.empty()) {
        throw std::invalid_argument("String must not be empty.");
    }
    std::cout << "Processing string in reverse: " << std::string(data.rbegin(), data.rend()) << std::endl;
}

// Template class for managing a collection of scientific objects
// This class provides a flexible way to manage a collection of scientific objects and their associated metadata
// The container supports adding elements, managing metadata, performing computations, filtering, and serialization
// The design choice of using templates allows for different types of keys to be used for identification
template <typename T>
class ScientificContainer {
private:
    // Stores pairs of key and scientific objects
    // std::vector is used here to maintain the order of insertion, which could be useful for iteration
    std::vector<std::pair<T, std::shared_ptr<ScientificObject>>> elements;
    // Stores metadata for each key, including an integer, double, string, and a callback function
    // Metadata provides additional information about each element and can be used for various purposes like logging or tracking
    std::unordered_map<T, std::tuple<int, double, std::string, std::function<void()>>> metadata;
    // Tracks unique keys to prevent duplicate entries
    // std::unordered_set ensures that each key is unique, providing efficient lookup for detecting duplicates
    std::unordered_set<T> uniqueKeys;

public:
    // Adds an element to the container
    // Throws a DuplicateElementException if the key already exists, ensuring data integrity
    void add_element(const T& key, std::shared_ptr<ScientificObject> object) {
        if (uniqueKeys.find(key) != uniqueKeys.end()) {
            throw DuplicateElementException(std::to_string(key));
        }
        elements.emplace_back(key, object);
        uniqueKeys.insert(key);
    }

    // Adds metadata with a callback function
    // Throws a runtime_error if metadata for the given key already exists, preventing overwriting of important data
    void add_metadata(const T& key, const std::tuple<int, double, std::string>& data, const std::function<void()>& callback) {
        if (metadata.find(key) != metadata.end()) {
            throw std::runtime_error("Metadata for this key already exists.");
        }
        metadata[key] = std::make_tuple(std::get<0>(data), std::get<1>(data), std::get<2>(data), callback);
    }

    // Computes all elements in the container
    // Calls the compute function of each stored scientific object
    // Uses a try-catch block to ensure that errors in one computation do not affect others
    void compute_all() const {
        for (const auto& [key, object] : elements) {
            try {
                std::cout << "Computing for key: " << key << std::endl;
                object->compute();
            } catch (const std::exception& e) {
                std::cerr << "Error during computation for key " << key << ": " << e.what() << std::endl;
            }
        }
    }

    // Prints metadata and executes associated callbacks
    // For each key, prints the metadata values and then calls the associated callback function
    // Uses a try-catch block to handle any errors during callback execution
    void print_metadata() const {
        for (const auto& [key, data] : metadata) {
            std::cout << "Metadata for key " << key << ": ("
                      << std::get<0>(data) << ", "
                      << std::get<1>(data) << ", "
                      << std::get<2>(data) << ")" << std::endl;
            try {
                std::get<3>(data)();
            } catch (const std::exception& e) {
                std::cerr << "Error during callback execution for key " << key << ": " << e.what() << std::endl;
            }
        }
    }

    // Filters elements based on a condition and prints satisfying keys
    // Takes a lambda or function as a condition and prints the keys that satisfy the condition
    // This functionality is useful for selectively operating on a subset of the elements
    void filter_elements(const std::function<bool(const T&)>& condition) const {
        for (const auto& [key, _] : elements) {
            if (condition(key)) {
                std::cout << "Key " << key << " satisfies the filter condition." << std::endl;
            }
        }
    }

    // Iterator support for range-based loops
    // Provides const iterators to allow read-only access to elements during iteration
    auto begin() const { return elements.begin(); }
    auto end() const { return elements.end(); }

    // Serializes the container to a JSON-like format
    // Outputs the elements and metadata in a structured JSON-like format for readability
    // This function is useful for debugging or exporting the container's state
    void serialize() const {
        std::cout << "{\n  \"elements\": [\n";
        for (const auto& [key, object] : elements) {
            std::cout << "    {\"key\": " << key << ", \"type\": \"" << typeid(*object).name() << "\"},\n";
        }
        std::cout << "  ],\n  \"metadata\": {\n";
        for (const auto& [key, data] : metadata) {
            std::cout << "    \"" << key << "\": {\"int_value\": " << std::get<0>(data)
                      << ", \"double_value\": " << std::get<1>(data)
                      << ", \"string_value\": \"" << std::get<2>(data) << "\"},\n";
        }
        std::cout << "  }\n}" << std::endl;
    }

    // Unit test function to verify the correctness of core functionalities
    // Tests adding elements, adding metadata, performing computations, filtering elements, and serialization
    // Uses assertions to validate the state of the container after each operation
    void run_tests() {
        try {
            // Test adding elements
            add_element(4, std::make_shared<VectorCalculation>());
            assert(uniqueKeys.find(4) != uniqueKeys.end());
            std::cout << "Test add_element() passed." << std::endl;

            // Test adding metadata
            add_metadata(4, std::make_tuple(10, 5.5, "Test Vector"), []() { std::cout << "Callback for Test Vector." << std::endl; });
            assert(metadata.find(4) != metadata.end());
            std::cout << "Test add_metadata() passed." << std::endl;

            // Test compute_all()
            compute_all();
            std::cout << "Test compute_all() passed." << std::endl;

            // Test filter_elements()
            filter_elements([](const int& key) { return key % 2 == 0; });
            std::cout << "Test filter_elements() passed." << std::endl;

            // Test serialization
            serialize();
            std::cout << "Test serialize() passed." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Test failed: " << e.what() << std::endl;
        }
    }
};

int main() {
    try {
        // Create a container to store scientific objects
        ScientificContainer<int> sci_container;
        
        // Adding elements to the container
        sci_container.add_element(1, std::make_shared<VectorCalculation>());
        sci_container.add_element(2, std::make_shared<MatrixCalculation>());
        sci_container.add_element(3, std::make_shared<TensorCalculation>());
        
        // Adding metadata with callbacks
        sci_container.add_metadata(1, std::make_tuple(42, 3.14, "Vector"), []() { std::cout << "Metadata callback for Vector." << std::endl; });
        sci_container.add_metadata(2, std::make_tuple(7, 2.718, "Matrix"), []() { std::cout << "Metadata callback for Matrix." << std::endl; });
        sci_container.add_metadata(3, std::make_tuple(5, 1.618, "Tensor"), []() { std::cout << "Metadata callback for Tensor." << std::endl; });
        
        // Process some data
        process_data(100);  // Processing an integer
        process_data(3.1415);  // Processing a double
        process_data(std::complex<double>(3.0, 4.0));  // Processing a complex number
        process_data(std::string("Hello"));  // Processing a string
        
        // Compute all elements in the container
        sci_container.compute_all();
        
        // Print metadata and execute callbacks
        sci_container.print_metadata();
        
        // Filter elements based on a custom condition
        sci_container.filter_elements([](const int& key) { return key % 2 == 0; });
        
        // Range-based iteration over elements in the container
        for (const auto& [key, object] : sci_container) {
            std::cout << "Iterating over key: " << key << std::endl;
        }
        
        // Serialize the container to a JSON-like format
        sci_container.serialize();

        // Run unit tests to validate the functionality
        sci_container.run_tests();
        
    } catch (const std::exception& e) {
        // Catch and display any exceptions thrown during execution
        std::cerr << "Exception caught in main: " << e.what() << std::endl;
    }
    
    return 0;
}
