#include "IntegrationMethods.h"
#include <iostream>
#include <cmath>
#include <fstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif




// Function to write data to a CSV file
void writeToCSV(const std::string& filename, const std::string& methodName, const std::string& functionName,
                double result, double exact, double error, double executionTime) {
    std::ofstream outFile;
    outFile.open(filename, std::ios::app); // Append mode
    outFile << methodName << "," << functionName << "," << result << "," << exact << ","
            << error << "," << executionTime << "\n";
    outFile.close();
}

void benchmarkMethod(Integration& method, const std::function<double(double)>& f, const std::string& methodName,
                     const std::string& functionName, double exactValue) {
    double result = method(f);
    double executionTime = method.getExecutionTime();
    double error = std::abs(result - exactValue);

    // Output to console
    std::cout << methodName << " on " << functionName << ": " << result
              << " (Time: " << executionTime << "s, Error: " << error << ")\n";

    // Write to CSV
    writeToCSV("benchmark_results.csv", methodName, functionName, result, exactValue, error, executionTime);
}

int main() {
    // Define functions to be integrated
    auto f1 = [](double x) { return std::sin(x); };
    double exactValue1 = 2.0; // Exact integral of sin(x) from 0 to π

    auto f2 = [](double x) { return std::exp(-x * x) * std::sin(1000 * x); };
    double exactValue2 = 0.0; // Approximate or known value if available

    auto f3 = [](double x) { return std::pow(x, 0.75) * std::log(1 + x * x); };
    double exactValue3 = 0.0; // Approximate or known value if available

    // Initialize integration methods
    NonAdaptiveSimpson simpson(0, M_PI);
    AdaptiveTrapezoidal trapezoidal(0, M_PI);

    // Clear the CSV file and write the header
    std::ofstream outFile("benchmark_results.csv");
    outFile << "Method,Function,Result,Exact,Error,ExecutionTime\n";
    outFile.close();

    // Benchmark each method on f1
    benchmarkMethod(simpson, f1, "Non-Adaptive Simpson", "sin(x)", exactValue1);
    benchmarkMethod(trapezoidal, f1, "Adaptive Trapezoidal", "sin(x)", exactValue1);

    // Benchmark each method on f2
    benchmarkMethod(simpson, f2, "Non-Adaptive Simpson", "exp(-x^2) * sin(1000 * x)", exactValue2);
    benchmarkMethod(trapezoidal, f2, "Adaptive Trapezoidal", "exp(-x^2) * sin(1000 * x)", exactValue2);

    // Benchmark each method on f3
    benchmarkMethod(simpson, f3, "Non-Adaptive Simpson", "x^0.75 * log(1 + x^2)", exactValue3);
    benchmarkMethod(trapezoidal, f3, "Adaptive Trapezoidal", "x^0.75 * log(1 + x^2)", exactValue3);

    return 0;
}


