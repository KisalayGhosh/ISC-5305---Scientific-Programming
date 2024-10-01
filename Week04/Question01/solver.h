#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include "function.h"

template <typename T>
class Solver
{
protected:
    int finalIteration;
    double tolerance;
    int maxIterations;

public:
    Solver(double tolerance_, int maxIterations_) : finalIteration(0), tolerance(tolerance_), maxIterations(maxIterations_) {}
    virtual ~Solver() {}

    // Updated to include the filename argument
    virtual T computeRoot(Function<T>& func, T x0, const std::string& filename) = 0;

    // Add verify method to base class
    virtual T verify(Function<T>& func, T computed_root) const {
        return std::abs(func(computed_root));
    }

    int getFinalIteration() const { return finalIteration; }
};

#endif // SOLVER_H
