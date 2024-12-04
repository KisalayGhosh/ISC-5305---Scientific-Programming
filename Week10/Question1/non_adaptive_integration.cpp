#include "non_adaptive_integration.h"
#include "globals.h"
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>

// Parallel implementation of Non-Adaptive Integration
double parallelNonAdaptiveIntegration(double a, double b, int n, int threads, const std::function<double(double)>& f, bool /*verbose*/) {
    // Step size for subintervals
    double h = (b - a) / n;

    // Store partial sums for each thread
    std::vector<double> partialSums(threads, 0.0);

    // Mutex to protect shared resources
    std::mutex mtx;

    // Resize global vectors to track evaluations and execution times
    evaluations_per_thread.resize(threads, 0);
    execution_times_per_thread.resize(threads, 0);

    // Worker function for each thread
    auto worker = [&](int threadId) {
        // Start timer for execution time tracking
        auto start = std::chrono::high_resolution_clock::now();

        int evaluations = 0; // Number of evaluations performed by this thread

        // Calculate the range of indices for this thread
        int startIdx = threadId * (n / threads);
        int endIdx = (threadId == threads - 1) ? n : startIdx + (n / threads);

        double localSum = 0.0; // Local sum for this thread

        // Perform numerical integration on the assigned subintervals
        for (int i = startIdx; i < endIdx; ++i) {
            double x1 = a + i * h;       // Left point of the interval
            double x2 = a + (i + 1) * h; // Right point of the interval
            localSum += 0.5 * h * (f(x1) + f(x2)); // Trapezoidal rule
            evaluations += 2; // Two evaluations per interval
        }

        {
            // Protect access to shared partialSums vector
            std::lock_guard<std::mutex> lock(mtx);
            partialSums[threadId] = localSum;
        }

        // Record evaluations and execution time for this thread
        evaluations_per_thread[threadId] = evaluations;
        auto end = std::chrono::high_resolution_clock::now();
        execution_times_per_thread[threadId] = std::chrono::duration<double>(end - start).count();
    };

    // Create and launch threads
    std::vector<std::thread> workers;
    for (int i = 0; i < threads; ++i) {
        workers.emplace_back(worker, i);
    }

    // Join all threads
    for (auto& thread : workers) {
        thread.join();
    }

    // Combine partial sums from all threads
    double result = 0.0;
    for (double sum : partialSums) {
        result += sum;
    }

    return result; // Final result of the integration
}
