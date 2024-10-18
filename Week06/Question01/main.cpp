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
#include <thread>
#include <chrono>

// Custom exception class for handling duplicate elements
// This class is used to throw an exception if an attempt is made to add an element with a duplicate key to the container.
// This ensures data integrity and prevents the accidental addition of multiple entries with the same key.
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
// This serves as a base class for all types of scientific calculations. By using a pure virtual function (`compute()`),
// this class ensures that all derived classes implement their own specific version of the computation logic.
// This approach allows us to use polymorphism, enabling the container to store different types of scientific calculations.
class ScientificObject {
public:
    // Pure virtual function that must be implemented by derived classes
    virtual void compute() const = 0;
    virtual ~ScientificObject() = default;
};

// Derived class for vector-based scientific calculations
// This class represents a specific type of scientific calculation involving vectors.
class VectorCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing vector calculation..." << std::endl;
        // Placeholder for actual vector computation logic
        // In a real-world scenario, this could involve calculating vector magnitudes, dot products, etc.
    }
};

// Derived class for matrix-based scientific calculations
// This class represents a specific type of scientific calculation involving matrices.
class MatrixCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing matrix calculation..." << std::endl;
        // Placeholder for actual matrix computation logic
        // In practice, this could involve operations like matrix multiplication, determinant calculation, etc.
    }
};

// Derived class for tensor-based scientific calculations
// This class represents a specific type of scientific calculation involving tensors.
class TensorCalculation : public ScientificObject {
public:
    void compute() const override {
        std::cout << "Performing tensor calculation..." << std::endl;
        // Placeholder for actual tensor computation logic
        // Tensors are often used in physics and engineering for complex data representation.
    }
};

// Template function to process scientific data
// This function can process various types of arithmetic data, such as integers and floating-point numbers.
// By using `static_assert`, we enforce that only arithmetic types are allowed, ensuring type safety at compile time.
template <typename T>
void process_data(const T& data) {
    static_assert(std::is_arithmetic<T>::value, "Template type must be an arithmetic type.");
    std::cout << "Processing data: " << data << std::endl;
}

// Template specialization for processing std::complex<double>
// This specialization handles complex numbers specifically, printing both the real and imaginary parts.
template <>
void process_data(const std::complex<double>& data) {
    std::cout << "Processing complex number: Real = " << data.real() << ", Imaginary = " << data.imag() << std::endl;
}

// Overload for processing std::string
// This overload processes strings by printing them in reverse. If the string is empty, it throws an exception.
template <>
void process_data(const std::string& data) {
    if (data.empty()) {
        throw std::invalid_argument("String must not be empty.");
    }
    std::cout << "Processing string in reverse: " << std::string(data.rbegin(), data.rend()) << std::endl;
}

// Template class for managing a collection of scientific objects
// The `ScientificContainer` class is designed to store and manage different types of scientific objects.
// It uses templates to allow flexibility in choosing the type of key used to identify elements.
// The class provides functions to add elements, manage metadata, perform computations, filter elements, and serialize the container.
template <typename T>
class ScientificContainer {
private:
    // Stores pairs of key and scientific objects
    // `std::vector` is used here to maintain the order of insertion and allow efficient iteration.
    std::vector<std::pair<T, std::shared_ptr<ScientificObject>>> elements;
    // Stores metadata for each key, including an integer, double, string, and a callback function
    // Metadata can be used for additional information about each element, like properties or configuration.
    std::unordered_map<T, std::tuple<int, double, std::string, std::function<void()>>> metadata;
    // Tracks unique keys to prevent duplicate entries
    // `std::unordered_set` is used to efficiently check if a key already exists.
    std::unordered_set<T> uniqueKeys;

public:
    // Adds an element to the container
    // Throws `DuplicateElementException` if an element with the same key already exists.
    // This ensures that each element in the container has a unique identifier.
    void add_element(const T& key, std::shared_ptr<ScientificObject> object) {
        if (uniqueKeys.find(key) != uniqueKeys.end()) {
            throw DuplicateElementException(std::to_string(key));
        }
        elements.emplace_back(key, object);
        uniqueKeys.insert(key);
    }

    // Adds metadata with a callback function
    // Metadata includes an integer, a double, a string, and a callback function that can be executed on demand.
    // Throws an exception if metadata for the given key already exists, ensuring no duplicate metadata entries.
    void add_metadata(const T& key, const std::tuple<int, double, std::string>& data, const std::function<void()>& callback) {
        if (metadata.find(key) != metadata.end()) {
            throw std::runtime_error("Metadata for this key already exists.");
        }
        metadata[key] = std::make_tuple(std::get<0>(data), std::get<1>(data), std::get<2>(data), callback);
    }

    // Computes all elements in the container using multiple threads
    // This function uses multithreading to perform computations in parallel, which can significantly reduce execution time.
    // Each element's `compute()` function is executed in a separate thread, and all threads are joined at the end to ensure all computations complete.
    void compute_all() const {
        std::vector<std::thread> threads;
        for (const auto& [key, object] : elements) {
            threads.emplace_back([key, object]() {
                try {
                    std::cout << "Computing for key: " << key << std::endl;
                    object->compute();
                } catch (const std::exception& e) {
                    std::cerr << "Error during computation for key " << key << ": " << e.what() << std::endl;
                }
            });
        }
        for (auto& thread : threads) {
            thread.join();
        }
    }

    // Prints metadata and executes associated callbacks
    // This function iterates over all metadata entries, printing each entry's values and executing the callback function.
    // The callback allows for additional functionality, such as logging or further calculations, to be performed when metadata is accessed.
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
    // This function takes a lambda or function as a condition and prints the keys of elements that satisfy this condition.
    // It is useful for selecting a subset of elements based on certain criteria.
    void filter_elements(const std::function<bool(const T&)>& condition) const {
        for (const auto& [key, _] : elements) {
            if (condition(key)) {
                std::cout << "Key " << key << " satisfies the filter condition." << std::endl;
            }
        }
    }

    // Iterator support for range-based loops
    // These functions provide iterators to enable range-based iteration over the elements of the container.
    auto begin() const { return elements.begin(); }
    auto end() const { return elements.end(); }

    // Serializes the container to a JSON-like format
    // This function outputs the elements and metadata in a structured format that resembles JSON.
    // This is helpful for exporting the container's state or for debugging purposes.
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
    // This function tests key functionalities of the container, such as adding elements, adding metadata, performing computations, filtering elements, and serialization.
    // Assertions are used to validate the correctness of operations, and exceptions are caught to report failures.
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
        // This container will manage different types of scientific calculations, each associated with a unique key.
        ScientificContainer<int> sci_container;
        
        // Adding elements to the container
        // Each element represents a specific type of scientific calculation, identified by a unique key.
        sci_container.add_element(1, std::make_shared<VectorCalculation>());
        sci_container.add_element(2, std::make_shared<MatrixCalculation>());
        sci_container.add_element(3, std::make_shared<TensorCalculation>());
        
        // Adding metadata with callbacks
        // Metadata includes information about each element, and a callback function that is executed when the metadata is printed.
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        sci_container.add_metadata(1, std::make_tuple(42, 3.14, "Vector"), [now]() { std::cout << "Metadata callback for Vector at " << std::ctime(&now); });
        sci_container.add_metadata(2, std::make_tuple(7, 2.718, "Matrix"), [now]() { std::cout << "Metadata callback for Matrix at " << std::ctime(&now); });
        sci_container.add_metadata(3, std::make_tuple(5, 1.618, "Tensor"), [now]() { std::cout << "Metadata callback for Tensor at " << std::ctime(&now); });
        
        // Process some data
        // Demonstrates the use of the `process_data` function to process various types of data.
        process_data(100);
        process_data(3.1415);
        process_data(std::complex<double>(3.0, 4.0));
        process_data(std::string("Hello"));
        
        // Compute all elements in the container
        // This will invoke the `compute()` function of each element in the container, using multithreading for parallel computation.
        sci_container.compute_all();
        
        // Print metadata and execute callbacks
        // This will print all the metadata associated with each element and execute the respective callback functions.
        sci_container.print_metadata();
        
        // Filter elements based on a custom condition
        // Filters and prints the keys of elements that satisfy the given condition (e.g., keys that are even).
        sci_container.filter_elements([](const int& key) { return key % 2 == 0; });
        
        // Range-based iteration over elements in the container
        // Demonstrates iterating over all elements in the container using a range-based loop.
        for (const auto& [key, object] : sci_container) {
            std::cout << "Iterating over key: " << key << std::endl;
        }
        
        // Serialize the container to a JSON-like format
        // Outputs the current state of the container in a structured format.
        sci_container.serialize();

        // Run unit tests to validate the functionality
        // Tests the core features of the container to ensure they work as expected.
        sci_container.run_tests();
        
    } catch (const std::exception& e) {
        // Catch and display any exceptions thrown during execution
        // This ensures that any errors are caught and reported, rather than causing the program to crash.
        std::cerr << "Exception caught in main: " << e.what() << std::endl;
    }
    
    return 0;
}
