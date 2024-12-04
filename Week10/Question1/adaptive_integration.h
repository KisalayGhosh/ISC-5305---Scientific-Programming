#ifndef ADAPTIVE_INTEGRATION_H
#define ADAPTIVE_INTEGRATION_H

#include <functional>

// Declaration of parallelAdaptiveIntegration
double parallelAdaptiveIntegration(
    double a, double b, double tolerance, int threads,
    const std::function<double(double)>& f, bool verbose);

#endif // ADAPTIVE_INTEGRATION_H
