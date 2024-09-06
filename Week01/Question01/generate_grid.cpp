#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <sstream>  

/**
 * @brief Converts a string to an integer using stringstream.
 *
 * @param str The input string to be converted.
 * @return The integer value parsed from the string.
 */
int string_to_int(const std::string& str) {
    std::stringstream ss(str);
    int result;
    ss >> result;
    if (ss.fail()) {
        throw std::invalid_argument("Invalid integer: " + str);
    }
    return result;
}

/**
 * @brief Converts a string to a double using stringstream.
 *
 * @param str The input string to be converted.
 * @return The double value parsed from the string.
 */
double string_to_double(const std::string& str) {
    std::stringstream ss(str);
    double result;
    ss >> result;
    if (ss.fail()) {
        throw std::invalid_argument("Invalid double: " + str);
    }
    return result;
}

/**
 * @brief Generates a 1D grid with initial temperature values T(x).
 *
 * @param N The number of grid points.
 * @param T_initial The initial temperature.
 * @return A vector of pairs representing (index, T_initial) values.
 */
std::vector<std::pair<int, double>> generate_initial_grid(int N, double T_initial) {
    if (N <= 0) {
        throw std::invalid_argument("Grid size N must be a positive integer.");
    }

    std::vector<std::pair<int, double>> data;
    for (int i = 0; i < N; ++i) {
        data.push_back({i, T_initial});  
    }

    return data;
}

/**
 * @brief Writes the initial grid configuration (index, T_initial) to a CSV file.
 *
 * @param filename The output CSV file name.
 * @param data A vector of (index, T_initial) pairs.
 */
void write_to_csv(const std::string& filename, const std::vector<std::pair<int, double>>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::ios_base::failure("Error: Could not open file for writing.");
    }

    file << "index,T_initial\n";  
    for (const auto& [index, T] : data) {
        file << index << "," << std::fixed << std::setprecision(6) << T << "\n";
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <N> <T_initial> <output_file>\n";
        return 1;
    }

    try {
        int N = string_to_int(argv[1]);          // Convert string to int
        double T_initial = string_to_double(argv[2]); // Convert string to double
        std::string output_file = argv[3];     // Output CSV file name

        // Debugging statements
        std::cout << "Generating grid with " << N << " points and initial temperature " << T_initial << "\n";
        std::cout << "Writing to file: " << output_file << "\n";

        // Generate grid
        auto data = generate_initial_grid(N, T_initial);

        std::cout << "Grid generated successfully.\n";

        // Write to CSV file
        write_to_csv(output_file, data);

        std::cout << "Initial grid configuration written to " << output_file << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
