#ifndef INTEGRATION_METHODS_H
#define INTEGRATION_METHODS_H

#include "Integration.h"
#include <cmath>

// Non-Adaptive, Non-Recursive Simpson's Rule
class NonAdaptiveSimpson : public Integration {
public:
    NonAdaptiveSimpson(double a, double b) : Integration(a, b, false, false) {}

    double integrate(const std::function<double(double)>& f, double tolerance = 1e-8, int maxDepth = 12) override {
        (void)tolerance; // Indicate that tolerance is intentionally unused
        (void)maxDepth;  // Indicate that maxDepth is intentionally unused

        int n = 1000; // Fixed number of intervals
        double h = (b - a) / n;
        double sum = f(a) + f(b);
        for (int i = 1; i < n; i += 2) {
            sum += 4 * f(a + i * h);
        }
        for (int i = 2; i < n - 1; i += 2) {
            sum += 2 * f(a + i * h);
        }
        return sum * h / 3;
    }
};

// Adaptive Trapezoidal Rule
class AdaptiveTrapezoidal : public Integration {
public:
    AdaptiveTrapezoidal(double a, double b) : Integration(a, b, true, true) {}

    double integrate(const std::function<double(double)>& f, double tolerance, int maxDepth) override {
        return adaptiveTrapezoidal(f, a, b, tolerance, maxDepth, 0);
    }

private:
    double adaptiveTrapezoidal(const std::function<double(double)>& f, double a, double b, double tol, int maxDepth, int depth) {
        if (depth >= maxDepth) {
            return 0.5 * (b - a) * (f(a) + f(b));
        }
        double c = (a + b) / 2;
        double oneTrap = 0.5 * (b - a) * (f(a) + f(b));
        double twoTrap = 0.5 * (c - a) * (f(a) + f(c)) + 0.5 * (b - c) * (f(c) + f(b));
        if (std::abs(twoTrap - oneTrap) < tol) {
            return twoTrap;
        }
        return adaptiveTrapezoidal(f, a, c, tol / 2, maxDepth, depth + 1) +
               adaptiveTrapezoidal(f, c, b, tol / 2, maxDepth, depth + 1);
    }
};

#endif // INTEGRATION_METHODS_H
