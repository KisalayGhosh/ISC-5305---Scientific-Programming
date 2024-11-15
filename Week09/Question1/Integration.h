#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <functional>  // For using std::function to represent mathematical functions
#include <chrono>      // For measuring execution time
#include <iostream>    // For debugging and output purposes

// Base class for all integration methods
class Integration {
protected:
    double a, b;               // Integration bounds: 'a' is the lower bound, 'b' is the upper bound
    bool isRecursive;          // Flag indicating whether the method is recursive
    bool isAdaptive;           // Flag indicating whether the method is adaptive
    double executionTime;      // Time taken to perform the integration in seconds

public:
    // Constructor to initialize integration bounds and flags
    Integration(double a, double b, bool isRecursive, bool isAdaptive)
        : a(a), b(b), isRecursive(isRecursive), isAdaptive(isAdaptive), executionTime(0) {}

    // Virtual destructor to allow proper cleanup in derived classes
    virtual ~Integration() = default;

    // Pure virtual function to be overridden by derived classes, performing the integration
    virtual double integrate(const std::function<double(double)>& f, double tolerance = 1e-8, int maxDepth = 12) = 0;

    // Overloaded function call operator to measure execution time and perform integration
    double operator()(const std::function<double(double)>& f, double tolerance = 1e-8, int maxDepth = 12) {
        // Start measuring time
        auto start = std::chrono::high_resolution_clock::now();

        // Perform the integration using the derived class's implementation
        double result = integrate(f, tolerance, maxDepth);

        // End measuring time
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the execution time in seconds
        executionTime = std::chrono::duration<double>(end - start).count();

        // Return the result of the integration
        return result;
    }

    // Getter function to retrieve the execution time
    double getExecutionTime() const { return executionTime; }
};

#endif // INTEGRATION_H
