#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

/**
 * @brief Reads the initial grid configuration from a CSV file.
 *
 * @param filename The input CSV file name.
 * @return A vector of grid indices.
 */
std::vector<int> read_from_csv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Error: Could not open file for reading.");
    }

    std::vector<int> indices;
    std::string line;
    std::getline(file, line);  

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        int index;
        double T_initial;
        char comma;
        ss >> index >> comma >> T_initial;
        indices.push_back(index);
    }

    return indices;
}

/**
 * @brief Computes the 1D heat distribution using the formula T(x) = 1 - x^2.
 *
 * @param indices A vector of grid indices.
 * @param a The lower bound of x.
 * @param b The upper bound of x.
 * @return A vector of pairs representing (x, T(x)) values for the heat distribution.
 */
std::vector<std::pair<double, double>> compute_heat_distribution(const std::vector<int>& indices, double a, double b) {
    std::vector<std::pair<double, double>> heat_distribution;

    int N = indices.size();
    double step = (b - a) / (N - 1);  // Calculate step size

    for (int i = 0; i < N; ++i) {
        double x = a + i * step;  // Map index to x in the range [a, b]
        double T = 1.0 - x * x;   // Compute T(x) = 1 - x^2
        heat_distribution.push_back({x, T});
    }

    return heat_distribution;
}

/**
 * @brief Writes the 1D heat distribution to a CSV file.
 *
 * @param filename The output CSV file name.
 * @param data A vector of (x, T(x)) pairs for the heat distribution.
 */
void write_heat_distribution_to_csv(const std::string& filename, const std::vector<std::pair<double, double>>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Error: Could not open file for writing.");
    }

    file << "x,T\n";  
    for (const auto& [x, T] : data) {
        file << std::fixed << std::setprecision(6) << x << "," << T << "\n";
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <a> <b> <output_file>\n";
        return 1;
    }

    try {
        std::string input_file = argv[1];      // Input CSV file
        double a = std::stod(argv[2]);         // Lower bound of x
        double b = std::stod(argv[3]);         // Upper bound of x
        std::string output_file = argv[4];     // Output CSV file for the heat distribution

        // Debugging statements
        std::cout << "Reading from file: " << input_file << "\n";
        std::cout << "Computing heat distribution for range [" << a << ", " << b << "]\n";
        std::cout << "Writing to file: " << output_file << "\n";

        // Read the grid indices from the CSV file
        auto indices = read_from_csv(input_file);

        std::cout << "Grid read successfully. Number of points: " << indices.size() << "\n";

        // Compute the 1D heat distribution
        auto heat_distribution = compute_heat_distribution(indices, a, b);

        std::cout << "Heat distribution computed successfully.\n";

        // Write the heat distribution to the output CSV file
        write_heat_distribution_to_csv(output_file, heat_distribution);

        std::cout << "Heat distribution written to " << output_file << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
