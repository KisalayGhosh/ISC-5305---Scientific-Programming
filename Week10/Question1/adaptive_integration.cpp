#include "adaptive_integration.h"
#include <iostream>
#include <queue>
#include <thread>
#include <tuple>
#include <cmath>
#include <mutex>

// Thread-safe queue for managing tasks
class ThreadSafeQueue {
    std::queue<std::tuple<double, double, double>> tasks; // Queue of tasks (a, b, tolerance)
    mutable std::mutex mtx; // Mutex for thread-safe operations

public:
    // Push a task into the queue
    void push(double a, double b, double tolerance) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        tasks.emplace(a, b, tolerance); // Add the task to the queue
    }

    // Pop a task from the queue
    bool pop(std::tuple<double, double, double>& task) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        if (tasks.empty()) return false; // If the queue is empty, return false
        task = tasks.front(); // Get the task at the front
        tasks.pop(); // Remove the task from the queue
        return true; // Return true if a task was popped
    }
};

// Thread-safe accumulator for managing integration results
class ThreadSafeAccumulator {
    double result = 0.0; // Accumulated result
    mutable std::mutex mtx; // Mutex for thread-safe operations

public:
    // Add a value to the accumulated result
    void add(double value) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        result += value; // Add the value to the result
    }

    // Retrieve the accumulated result
    double getResult() const {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        return result; // Return the accumulated result
    }
};

// Worker function for adaptive integration
void adaptiveWorker(
    const std::function<double(double)>& f, // Function to integrate
    ThreadSafeQueue& taskQueue, // Queue of tasks
    ThreadSafeAccumulator& accumulator, // Accumulator for results
    bool verbose // Flag for verbose logging
) {
    const double minIntervalSize = 1e-9; // Minimum allowed interval size
    const int maxTasks = 100000; // Maximum number of tasks to prevent overloading
    static int taskCount = 0; // Global count of tasks (thread-safe access not required here)

    while (true) {
        std::tuple<double, double, double> task; // Task to process (a, b, tolerance)

        // Attempt to pop a task from the queue
        if (!taskQueue.pop(task)) {
            if (verbose) std::cout << "Worker exiting: No more tasks.\n";
            break; // Exit the loop if no more tasks are available
        }

        double a = std::get<0>(task); // Start of interval
        double b = std::get<1>(task); // End of interval
        double tolerance = std::get<2>(task); // Error tolerance

        double h = b - a; // Interval size
        if (h < minIntervalSize || taskCount >= maxTasks) {
            // If the interval is too small or task limit is reached, approximate integral
            if (verbose) std::cout << "Adding approximate result for small interval [" << a << ", " << b << "]\n";
            double fa = f(a), fb = f(b); // Evaluate the function at endpoints
            double approxIntegral = h * (fa + fb) / 2.0; // Trapezoidal rule
            accumulator.add(approxIntegral); // Add the approximate result to the accumulator
            continue;
        }

        double c = (a + b) / 2.0; // Midpoint of the interval
        double fa = f(a), fb = f(b), fc = f(c); // Evaluate the function at a, b, and c

        // Calculate integral approximations
        double integral1 = h * (fa + fb) / 2.0; // Approximation using two points
        double integral2 = (h / 2.0) * (fa + 2.0 * fc + fb); // Approximation using midpoint

        if (std::abs(integral2 - integral1) < tolerance) {
            // If the error is within tolerance, add the integral
            accumulator.add(integral2);
            if (verbose) std::cout << "Task completed: Integral=" << integral2 << std::endl;
        } else {
            // Split the interval into two tasks with reduced tolerance
            taskQueue.push(a, c, tolerance / 2.0);
            taskQueue.push(c, b, tolerance / 2.0);
            taskCount += 2; // Increment the task count
        }
    }
}

// Main function to perform parallel adaptive integration
double parallelAdaptiveIntegration(
    double a, double b, double tolerance, int threads,
    const std::function<double(double)>& f, bool verbose
) {
    ThreadSafeQueue taskQueue; // Task queue for managing intervals
    ThreadSafeAccumulator accumulator; // Accumulator for results

    taskQueue.push(a, b, tolerance); // Push the initial task to the queue
    std::vector<std::thread> workers; // Vector to store threads

    // Create worker threads
    for (int i = 0; i < threads; i++) {
        workers.emplace_back(adaptiveWorker, std::ref(f), std::ref(taskQueue), std::ref(accumulator), verbose);
    }

    // Join all threads
    for (auto& thread : workers) {
        thread.join();
    }

    return accumulator.getResult(); // Return the final accumulated result
}
