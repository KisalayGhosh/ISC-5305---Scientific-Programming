#include "IntegrationMethods.h"
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    auto f = [](double x) { return std::sin(x); };
    NonAdaptiveSimpson simpson(0, M_PI);
    AdaptiveTrapezoidal trapezoidal(0, M_PI);

    double result1 = simpson(f);
    double result2 = trapezoidal(f);

    std::cout << "Non-Adaptive Simpson's Result: " << result1 << std::endl;
    std::cout << "Adaptive Trapezoidal Result: " << result2 << std::endl;

    return 0;
}
