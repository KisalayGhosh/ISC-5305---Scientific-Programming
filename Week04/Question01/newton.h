#ifndef NEWTON_H
#define NEWTON_H

#include "solver.h"
#include <fstream>
#include <iostream>

template <typename T>
class Newton : public Solver<T>
{
public:
    Newton(double tolerance_, int maxIterations_) : Solver<T>(tolerance_, maxIterations_) {}

    // Save root values to a file during each iteration
    T computeRoot(Function<T>& func, T x0, const std::string& filename) override {
        std::ofstream file(filename);
        file << "Iteration,Root\n";  // CSV header

        T x = x0;
        for (int i = 0; i < this->maxIterations; ++i) {
            T fx = func(x);
            T dfx = func.fp(x);
            if (abs(fx) < this->tolerance || abs(dfx) < this->tolerance) {
                std::cout << "Newton: Converged after " << i + 1 << " iterations with root: " << x << std::endl;
                file << i + 1 << "," << x << "\n";  // Write final root
                break;
            }
            x = x - fx / dfx;
            this->finalIteration = i + 1;
            file << i + 1 << "," << x << "\n";  // Write iteration and root to CSV
            std::cout << "Iteration " << i + 1 << ": Root = " << x << std::endl;  // Debugging output
        }
        file.close();
        return x;
    }

    T verify(Function<T>& func, T computed_root) const {
        T error = std::abs(func(computed_root));
        std::cout << "Newton verification error: " << error << std::endl;
        return error;
    }
};

#endif // NEWTON_H
