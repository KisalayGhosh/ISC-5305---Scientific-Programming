#ifndef SECANT_H
#define SECANT_H

#include "solver.h"
#include <fstream>
#include <iostream>

template <typename T>
class Secant : public Solver<T>
{
public:
    Secant(double tolerance_, int maxIterations_) : Solver<T>(tolerance_, maxIterations_) {}

    // Save root values to a file during each iteration
    T computeRoot(Function<T>& func, T x0, const std::string& filename) override {
        std::ofstream file(filename);
        file << "Iteration,Root\n";  // CSV header

        T x1 = x0;
        T x2 = x0 + 0.1;  // Slightly different second guess
        for (int i = 0; i < this->maxIterations; ++i) {
            T fx1 = func(x1);
            T fx2 = func(x2);
            if (abs(fx2 - fx1) < this->tolerance) {
                std::cout << "Secant: Converged after " << i + 1 << " iterations with root: " << x2 << std::endl;
                file << i + 1 << "," << x2 << "\n";  // Write final root
                break;
            }
            T x3 = x2 - fx2 * (x2 - x1) / (fx2 - fx1);
            file << i + 1 << "," << x3 << "\n";  // Write iteration and root to CSV
            std::cout << "Iteration " << i + 1 << ": Root = " << x3 << std::endl;  // Debugging output
            if (abs(func(x3)) < this->tolerance) {
                this->finalIteration = i + 1;
                file.close();
                return x3;
            }
            x1 = x2;
            x2 = x3;
        }
        file.close();
        return x2;
    }

    T verify(Function<T>& func, T computed_root) const {
        T error = std::abs(func(computed_root));
        std::cout << "Secant verification error: " << error << std::endl;
        return error;
    }
};

#endif // SECANT_H
