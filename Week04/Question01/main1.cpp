#include <iostream>
#include <vector>
#include <memory>
#include "sine_function.h"
#include "cubic_function.h"
#include "log_quadratic_function.h"
#include "newton.h"
#include "secant.h"

int main() {
    // Collection of functions using smart pointers with float precision
    std::vector<std::unique_ptr<Function<float>>> functions;

    // Push functions into the vector
    functions.push_back(std::make_unique<SineFunction<float>>());
    functions.push_back(std::make_unique<CubicFunction<float>>());
    functions.push_back(std::make_unique<LogQuadraticFunction<float>>());

    // Solver parameters with looser tolerance and more iterations
    struct SolverParams {
        float tolerance;
        int maxIterations;
    };
    std::vector<SolverParams> params = {
        {0.001f, 100},  // Adjusted tolerance and increased maximum iterations
    };

    // Initial guesses for different functions to allow more exploration
    std::vector<float> initial_guesses = {
        1.0f,  // Initial guess for sine function
        2.5f,  // Initial guess for cubic function
        1.8f   // Initial guess for logarithmic-quadratic function
    };

    // Iterate through each function and solve using both Newton and Secant methods
    for (size_t i = 0; i < functions.size(); ++i) {
        auto& func = functions[i];
        float initial_guess = initial_guesses[i];  // Use a different guess for each function

        std::string newton_filename = "newton_function_float_" + std::to_string(i + 1) + ".csv";
        std::string secant_filename = "secant_function_float_" + std::to_string(i + 1) + ".csv";

        std::cout << "Processing function " << i + 1 << " with initial guess: " << initial_guess << std::endl;

        for (const auto& p : params) {
            // Newton method
            auto newtonSolver = std::make_unique<Newton<float>>(p.tolerance, p.maxIterations);
            float newtonRoot = newtonSolver->computeRoot(*func, initial_guess, newton_filename);  // Pass filename
            std::cout << "Newton Root: " << newtonRoot << std::endl;
            newtonSolver->verify(*func, newtonRoot);

            // Secant method
            auto secantSolver = std::make_unique<Secant<float>>(p.tolerance, p.maxIterations);
            float secantRoot = secantSolver->computeRoot(*func, initial_guess, secant_filename);  // Pass filename
            std::cout << "Secant Root: " << secantRoot << std::endl;
            secantSolver->verify(*func, secantRoot);
        }
    }

    return 0;
}