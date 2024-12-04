#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>  // For std::accumulate
#include <functional>
#include <chrono>
#include "non_adaptive_integration.h"

// Utility function to calculate mean and standard deviation
template <typename T>
std::pair<double, double> calculateStats(const std::vector<T>& data) {
    if (data.empty()) return {0.0, 0.0};

    // Calculate the sum of elements
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / data.size();

    // Calculate variance
    double variance = 0.0;
    for (const auto& val : data) {
        variance += (val - mean) * (val - mean);
    }
    variance /= data.size();

    // Return mean and standard deviation
    return {mean, std::sqrt(variance)};
}

// Benchmarking function for non-adaptive integration
void nonAdaptiveBenchmark() {
    // Open CSV file to store results
    std::ofstream csv("nonadaptive_results.csv");
    if (!csv.is_open()) {
        std::cerr << "Error: Unable to create or open nonadaptive_results.csv" << std::endl;
        return;
    }

    // Write CSV header
    csv << "Method,Threads,MeanEvaluations,StdDevEvaluations,MeanTime,StdDevTime\n";

    // Define the test function
    std::function<double(double)> f1 = [](double x) { return std::sqrt(x) * std::pow(1 - x, 2); };

    // Loop over thread counts
    for (int threads : {1, 2, 4, 8, 16}) {
        std::vector<double> evaluations; // Store results for evaluations
        std::vector<double> times;      // Store execution times

        // Perform multiple runs for each configuration
        for (int i = 0; i < 5; ++i) {
            auto start = std::chrono::high_resolution_clock::now();

            // Call parallel non-adaptive integration
            double result = parallelNonAdaptiveIntegration(0, 1, 1000, threads, f1, false);
            auto end = std::chrono::high_resolution_clock::now();

            // Measure execution time
            double execTime = std::chrono::duration<double>(end - start).count();

            // Store results
            evaluations.push_back(result);
            times.push_back(execTime);

            // Debugging log (optional)
            std::cout << "Result for threads=" << threads << ": " << result << std::endl;
        }

        // Calculate statistics
        auto [meanEval, stdDevEval] = calculateStats(evaluations);
        auto [meanTime, stdDevTime] = calculateStats(times);

        // Write results to CSV
        csv << "Non-Adaptive," << threads << "," << meanEval << "," << stdDevEval << "," << meanTime << "," << stdDevTime << "\n";
        csv.flush(); // Ensure data is written to the file
    }

    csv.close(); // Close the CSV file
    std::cout << "Benchmark results saved to nonadaptive_results.csv\n";
}

int main() {
    // Run the non-adaptive integration benchmark
    nonAdaptiveBenchmark();
    return 0;
}
