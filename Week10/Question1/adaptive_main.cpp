#include <iostream>
#include <fstream>
#include <cmath>
#include <numeric>  // Required for std::accumulate
#include <functional>
#include <chrono>
#include "adaptive_integration.h"

// Utility function to calculate mean and standard deviation
template <typename T>
std::pair<double, double> calculateStats(const std::vector<T>& data) {
    if (data.empty()) return {0.0, 0.0}; // Return zeroes if data is empty

    // Calculate the sum of all elements
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double mean = sum / data.size(); // Compute the mean

    // Calculate the variance
    double variance = 0.0;
    for (const auto& val : data) {
        variance += (val - mean) * (val - mean);
    }
    variance /= data.size(); // Final variance value

    return {mean, std::sqrt(variance)}; // Return mean and standard deviation
}

// Function to perform benchmark for adaptive integration
void benchmark() {
    // Open a CSV file to store the results
    std::ofstream csv("adaptive_results.csv");
    if (!csv.is_open()) {
        std::cerr << "Error: Unable to create or open adaptive_results.csv" << std::endl;
        return;
    }

    // Write the header for the CSV file
    csv << "Method,Threads,MeanEvaluations,StdDevEvaluations,MeanTime,StdDevTime\n";

    // Define the test function: f(x) = sqrt(x) * (1 - x)^2
    std::function<double(double)> f1 = [](double x) { return std::sqrt(x) * std::pow(1 - x, 2); };

    // Test for varying number of threads
    for (int threads : {1, 2, 4, 8, 16}) {
        std::vector<double> evaluations; // Store evaluations for each run
        std::vector<double> times; // Store execution times for each run

        for (int i = 0; i < 5; ++i) { // Perform 5 runs per thread configuration
            auto start = std::chrono::high_resolution_clock::now(); // Start the timer

            // Perform the adaptive integration
            double result = parallelAdaptiveIntegration(0, 1, 1e-3, threads, f1, false);

            auto end = std::chrono::high_resolution_clock::now(); // Stop the timer

            double execTime = std::chrono::duration<double>(end - start).count(); // Calculate execution time
            evaluations.push_back(result); // Store the result (number of evaluations)
            times.push_back(execTime); // Store the execution time
        }

        // Compute mean and standard deviation for evaluations and times
        auto [meanEval, stdDevEval] = calculateStats(evaluations);
        auto [meanTime, stdDevTime] = calculateStats(times);

        // Write the results to the CSV file
        csv << "Adaptive," << threads << "," << meanEval << "," << stdDevEval << "," << meanTime << "," << stdDevTime << "\n";
        csv.flush(); // Ensure data is written to the file immediately
    }

    csv.close(); // Close the CSV file
    std::cout << "Benchmark results saved to adaptive_results.csv\n"; // Notify user
}

int main() {
    benchmark(); // Call the benchmark function
    return 0; // Indicate successful execution
}
